
#include "localization.h"
#include "custom-utilities.h"

using namespace devices;
using namespace utilities;

// A namespace to hold all the code needed for localization
namespace localization {
    // -------------------- Variables --------------------

    // Distributions (to avoid recreating them every loop)
    // Not const because they can't be for the function call operator
    std::uniform_real_distribution<float> magDistribution(1 - DRIVE_NOISE, 1 + DRIVE_NOISE);
    std::uniform_real_distribution<float> angleDistribution(-ANGLE_NOISE, ANGLE_NOISE);
    // std::normal_distribution<float> magDistribution(1, 2.0 * DRIVE_NOISE / sqrt(12.0));
    // std::normal_distribution<float> angleDistribution(0, 2.0 * ANGLE_NOISE / sqrt(12.0));
    std::uniform_real_distribution<float> fieldDistribution(-HALF_FIELD_SIZE, HALF_FIELD_SIZE);

    std::array<Particle, NUM_PARTICLES> particles;

    double distanceSinceUpdate{0};
    int lastUpdateTime{0};

    bool firstFrame = true;

    // For odometry
    double prevAngle{0};
    int prevVertTrackerVal{0};
    int prevLatTrackerVal{0};

    DistanceSensor sensorRight{rightLocalOffset, -HALF_PI, rightTuningConst, distanceRight};
    DistanceSensor sensorLeft{leftLocalOffset, HALF_PI, leftTuningConst, distanceLeft};
    DistanceSensor sensorFront{frontLocalOffset, 0, frontTuningConst, distanceFront};
    DistanceSensor sensorBack{backLocalOffset, M_PI, backTuningConst, distanceBack};

    const std::vector<DistanceSensor*> distanceSensors{&sensorFront, &sensorRight, &sensorBack, &sensorLeft};

    Field field(HALF_FIELD_SIZE, {
                                     {-47, -65.7, 4.5}, // Matchloaders
                                     {47, -65.7, 4.5},
                                     {-47, 65.7, 4.5},
                                     {47, 65.7, 4.5},
                                     {-48, -23, 3}, // Long Goals
                                     {48, -23, 3},
                                     {-48, 23, 3},
                                     {48, 23, 3},
                                     {0, 0, 5},
                                 });

                                //  {HALF_FIELD_SIZE - 5, HALF_FIELD_SIZE - 5, 5},
                                //   {-(HALF_FIELD_SIZE - 5), HALF_FIELD_SIZE - 5, 5},
                                //   {HALF_FIELD_SIZE - 5, -(HALF_FIELD_SIZE - 5), 5},
                                //   {-(HALF_FIELD_SIZE - 5), -(HALF_FIELD_SIZE - 5), 5}
    // The predicted pose in lemlib coordinates
    Pose predictedPose;

    PeriodicTask periodicTask{update, DELAY, "Localization Task"};

    // -------------------- Functions --------------------
    // ---------- External Interfacing Functions ----------

    // Sets up and starts the localization task with x-y position in inches
    // and angle in cw degrees, north=0
    void start(double startX, double startY, double startA) {
        vertTracker.reset();
        latTracker.reset();
        inertial.tare();
        // TODO
        // pros::delay(100);
        // pros::lcd::print(0, "1: %g, 2: %g, 3: %g", startA, startA + 270, angleRangeZeroTo360(startA + 270));
        inertial.set_heading(angleRangeZeroTo360(startA + 270)); // cw degrees, east=0

        initParticles(startX, startY);

        periodicTask.start();
    }

    lemlib::Pose getPrediction() {
        return lemlib::Pose{
            static_cast<float>(predictedPose.pos.x),
            static_cast<float>(predictedPose.pos.y),
            static_cast<float>(predictedPose.angle)};
    }

    // Print the robot's position and angle to the specified line
    void logLocalization(int line) {
        lemlib::Pose pose = getPrediction();

        double sumDistSquared = 0.0;
        double minDistSquared = std::numeric_limits<double>::max();
        double maxDistSquared = 0.0;
        for (Particle p : particles) {
            double distSquared = (p.pos - predictedPose.pos).magnitudeSquared();
            sumDistSquared += distSquared;
            if (distSquared > maxDistSquared) maxDistSquared = distSquared;
            if (distSquared < minDistSquared) minDistSquared = distSquared;
        }
        double stdDev = sqrt(sumDistSquared / static_cast<double>(NUM_PARTICLES));

        pros::lcd::print(
            line,
            "x: %g, y: %g, a: %g",
            round(pose.x * 100) * 0.01,
            round(pose.y * 100) * 0.01,
            round(pose.theta * 100) * 0.01);
        pros::lcd::print(
            line + 1,
            "stdev: %g, min: %g, max: %g",
            round(stdDev * 100) * 0.01,
            round(sqrt(minDistSquared) * 100) * 0.01,
            round(sqrt(maxDistSquared) * 100) * 0.01);
    }

    // ---------- Algorithm Functions ----------

    // Initialize the particles to random positions on the field
    void initParticles(double startX, double startY) {
        std::normal_distribution xDistribution{startX, START_POS_STD_DEV};
        std::normal_distribution yDistribution{startY, START_POS_STD_DEV};
        // Vector sumPos{};
        for (size_t i = 0; i < NUM_PARTICLES; ++i) {
            Particle p{};
            // TODO: Would probably be better to do this in polar coordinates
            p.pos.x = std::clamp(xDistribution(utilities::getGenerator()), -HALF_FIELD_SIZE, HALF_FIELD_SIZE);
            p.pos.y = std::clamp(yDistribution(utilities::getGenerator()), -HALF_FIELD_SIZE, HALF_FIELD_SIZE);
            p.weight = 1.0 / NUM_PARTICLES; // TODO: unnecessary
            // sumPos += p.pos;
            particles[i] = p;
        }
        // sumPos /= static_cast<double>(NUM_PARTICLES);
        // pros::lcd::print(0, "x: %g, y: %g", sumPos.x, sumPos.y);
    }

    Vector getOdomPositionDelta() {
        const double angleVal = 360.0 - inertial.get_heading();                            // ccw degrees, east=0
        double angleDelta = utilities::lazyBoundPNPi((angleVal - prevAngle) * DEG_TO_RAD); // ccw radians, east=0 (relative)

        const int vertTrackerVal = vertTracker.get_angle();
        int vertTrackerDelta = vertTrackerVal - prevVertTrackerVal; // might have to adjust for wraparound
        if (vertTrackerDelta > 18000) vertTrackerDelta -= 36000;
        if (vertTrackerDelta < -18000) vertTrackerDelta += 36000;
        const double vertTrackerDeltaDist = vertTrackerDelta * 0.01 * DEG_TO_RAD * vertTrackerWheelRad;

        const int latTrackerVal = latTracker.get_angle();
        int latTrackerDelta = latTrackerVal - prevLatTrackerVal; // might have to adjust for wraparound
        if (latTrackerDelta > 18000) latTrackerDelta -= 36000;
        if (latTrackerDelta < -18000) latTrackerDelta += 36000;
        const double latTrackerDeltaDist = latTrackerDelta * 0.01 * DEG_TO_RAD * vertTrackerWheelRad;

        Vector localDelta;

        if (angleDelta == 0) {
            localDelta.x = vertTrackerDeltaDist;
            localDelta.y = latTrackerDeltaDist;
        } else {
            localDelta.x = 2 * sin(angleDelta * 0.5) * (vertTrackerDeltaDist / angleDelta - vertTrackerOffset); // double check
            // turn radius is latTrackerDeltaDist / angleDelta - latTrackerOffset
            localDelta.y = 2 * sin(angleDelta * 0.5) * (latTrackerDeltaDist / angleDelta - latTrackerOffset);
        }

        // TODO: is this the angle we want to rotate by???
        const double avrgAngle = ((prevAngle + angleVal) * 0.5) * DEG_TO_RAD; // ccw radians, east=0
        Vector globalDelta = utilities::rotate(localDelta, avrgAngle);
        // const double globalDeltaX = localDelta.x * cos(avrgAngle) - localDelta.y * sin(avrgAngle);
        // const double globalDeltaY = localDelta.y * cos(avrgAngle) + localDelta.x * sin(avrgAngle);

        prevAngle = angleVal;
        prevVertTrackerVal = vertTrackerVal;
        prevLatTrackerVal = latTrackerVal;

        // return Vector{globalDeltaX, globalDeltaY};
        return globalDelta;
        // Could probably return the local delta and then rotate later
        // return Vector{localDeltaX, localDeltaY};
    }

    // The update function for the localization task.
    void update() {
        // ---------- Move Particles With Robot ----------
        double inertialMeasurement = inertial.get_heading(); // cw degrees, east=0
        Vector posDelta = getOdomPositionDelta();

        if (firstFrame) {
            firstFrame = false;
            return;
        }

        for (Particle& p : particles) {
            // NOTE: Using uniform noise instead of gaussian noise for speed
            Vector posDeltaCartesianNoisy =
                rotate(posDelta, angleDistribution(utilities::getGenerator())) * magDistribution(utilities::getGenerator());
            p.pos += posDeltaCartesianNoisy;
        }

        // ---------- Check if Update Necessary ----------
        // Won't update unless the robot has travelled a certain distance
        // TODO: Could make better by incorporating angular movement too
        distanceSinceUpdate += posDelta.magnitude(); // Not super accurate, but easy

        int time = pros::millis();
        if (distanceSinceUpdate < MAX_DIST_SINCE_UPDATE && time - lastUpdateTime < MAX_UPDATE_INTERVAL) {
            // Re-estimate pose
            Vector sumPos;

            for (Particle& p : particles) {
                sumPos += p.pos;
            }

            predictedPose = Pose{
                sumPos.x / static_cast<double>(NUM_PARTICLES),
                sumPos.y / static_cast<double>(NUM_PARTICLES),
                // angleRangeZeroTo360(90.0 + inertialMeasurement) // cw degrees, north=0
                inertialMeasurement < 270.0 ? inertialMeasurement + 90.0 : inertialMeasurement - 270.0 // cw degrees, north=0
            };
            chassis.setPose(getPrediction());

            return;
        }

        distanceSinceUpdate = 0;
        lastUpdateTime = time;

        // ---------- Re-weight Particles Based on Sensor Measurements   ----------
        for (DistanceSensor* sensor : distanceSensors) {
            sensor->update();
        }

        // TODO: might not be necessary to keep this in [0, 2pi) range
        double angle = (360.0 - inertialMeasurement) * DEG_TO_RAD; // ccw radians, east=0

        bool first = true;

        double totalWeight = 0.0;
        for (Particle& p : particles) {
            if (p.pos.x < -HALF_FIELD_SIZE || p.pos.x > HALF_FIELD_SIZE || p.pos.y < -HALF_FIELD_SIZE || p.pos.y > HALF_FIELD_SIZE) {
                p.pos.x = fieldDistribution(utilities::getGenerator());
                p.pos.y = fieldDistribution(utilities::getGenerator());
            }

            // TODO: add case for if no sensor gets a valid measurement?
            p.weight = 1.0; // TODO: increase for precision
            for (DistanceSensor* sensor : distanceSensors) {
                // TODO: avoid recalculating the offset in probability function (because constant angle)
                std::optional<double> probability = sensor->probability(p, angle, field, first);
                first = false;
                if (probability.has_value()) {
                    p.weight *= probability.value();
                }
            }
            totalWeight += p.weight;
        }

        // ---------- Resample Particles ----------
        std::array<Particle, NUM_PARTICLES> oldParticles = particles;

        double avgWeight = totalWeight / static_cast<double>(NUM_PARTICLES);
        const double randWeight = utilities::getRandomDoubleInRange(0.0, avgWeight);

        size_t j = 0;
        double cumulativeWeight = 0.0;

        Vector sumPos;

        for (size_t i = 0; i < NUM_PARTICLES; ++i) {
            const double weight = static_cast<double>(i) * avgWeight + randWeight;

            while (cumulativeWeight < weight) {
                if (j >= NUM_PARTICLES)
                    break;
                cumulativeWeight += particles[j++].weight;
            }

            particles[i].pos = oldParticles[j - 1].pos;

            sumPos += particles[i].pos;
        }

        predictedPose = Pose{
            sumPos.x / static_cast<double>(NUM_PARTICLES),
            sumPos.y / static_cast<double>(NUM_PARTICLES),
            // angleRangeZeroTo360(90.0 + inertialMeasurement) // cw degrees, north=0
            inertialMeasurement < 270.0 ? inertialMeasurement + 90.0 : inertialMeasurement - 270.0 // cw degrees, north=0
        };
        chassis.setPose(getPrediction());
    }
} // namespace localization