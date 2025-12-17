
#include "localization.h"
#include "custom-utilities.h"

using namespace devices;
using namespace utilities;

// A namespace to hold all the code needed for localization
namespace localization {
    // -------------------- Variables --------------------

    // Distributions (to avoid recreating them every loop)
    // Not const because they can't be for the function call operator
    // std::uniform_real_distribution<float> magDistribution(1 - DRIVE_NOISE, 1 + DRIVE_NOISE);
    // std::uniform_real_distribution<float> angleDistribution(-ANGLE_NOISE, ANGLE_NOISE);
    std::normal_distribution<float> magDistribution(1, 2.0 * DRIVE_NOISE / sqrt(12.0));
    std::normal_distribution<float> angleDistribution(0, 2.0 * ANGLE_NOISE / sqrt(12.0));
    std::uniform_real_distribution<float> fieldDistribution(-HALF_FIELD_SIZE, HALF_FIELD_SIZE);

    std::array<Particle, NUM_PARTICLES> particles;
    std::array<Vector, NUM_PARTICLES> oldParticleLocations; // doesn't need to hold weights

    double angleChangeSinceUpdate{0};
    double distanceSinceUpdate{0};
    int lastUpdateTime{0};
    bool isResampling = true;

    bool firstFrame = true;

    // int count{0};

    // For odometry
    double prevAngle{0};
    int prevVertTrackerVal{0};
    int prevLatTrackerVal{0};

    DistanceSensor sensorRight{rightLocalOffset, -HALF_PI, rightTuningConst, distanceRight};
    DistanceSensor sensorLeft{leftLocalOffset, HALF_PI, leftTuningConst, distanceLeft};
    DistanceSensor sensorFront{frontLocalOffset, 0, frontTuningConst, distanceFront};
    DistanceSensor sensorBack{backLocalOffset, M_PI, backTuningConst, distanceBack};

    const std::vector<DistanceSensor*> distanceSensors{&sensorFront, &sensorRight, &sensorBack, &sensorLeft};

    Field field(HALF_FIELD_SIZE, {                  /*{-47, -67.95, 2.25}, // Matchloaders
                                                    {47, -67.95, 2.25},
                                                    {-47, 67.95, 2.25},
                                                    {47, 67.95, 2.25}, */
                                  {-48, -23, 2.25}, // Long Goals
                                  {48, -23, 2.25},
                                  {-48, 23, 2.25},
                                  {48, 23, 2.25},
                                  {0, 0, 4}});

    // Field field(FULL_FIELD_SIZE);

    // The predicted pose in lemlib coordinates
    Pose predictedPose;
    lemlib::Pose lemlibPredictedPose{0, 0, 0};

    PeriodicTask periodicTask{update, DELAY, "Localization Task"};

    // -------------------- Functions --------------------
    // ---------- External Interfacing Functions ----------

    // Sets up and starts the localization task with x-y position in inches
    // and angle in cw degrees, north=0
    void start(double startX, double startY, double startA) {
        vertTracker.reset();
        latTracker.reset();
        // inertial.reset(true);
        inertial.tare();
        inertial.set_heading(angleRangeZeroTo360(startA + 270)); // cw degrees, east=0

        initParticles(startX, startY);

        periodicTask.start();
    }

    lemlib::Pose getPrediction() {
        return lemlibPredictedPose;
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
        for (size_t i = 0; i < NUM_PARTICLES; ++i) {
            Particle p{};
            // TODO: Would probably be better to do this in polar coordinates
            p.pos.x = std::clamp(xDistribution(utilities::getGenerator()), -HALF_FIELD_SIZE, HALF_FIELD_SIZE);
            p.pos.y = std::clamp(yDistribution(utilities::getGenerator()), -HALF_FIELD_SIZE, HALF_FIELD_SIZE);
            p.weight = 1.0 / NUM_PARTICLES; // TODO: unnecessary
            particles[i] = p;
        }
    }

    Vector getOdomPositionDelta(double currentAngleDeg) {
        // currentAngleDeg is in ccw degrees, east=0
        double angleDelta = utilities::lazyBoundPNPi((currentAngleDeg - prevAngle) * DEG_TO_RAD); // ccw radians, east=0 (relative)

        // TODO
        angleChangeSinceUpdate += angleDelta;

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

        const double avrgAngle = ((prevAngle + currentAngleDeg) * 0.5) * DEG_TO_RAD; // ccw radians, east=0
        Vector globalDelta = utilities::rotate(localDelta, avrgAngle);

        prevAngle = currentAngleDeg;
        prevVertTrackerVal = vertTrackerVal;
        prevLatTrackerVal = latTrackerVal;

        return globalDelta;
        // TODO: Could probably return the local delta and then rotate later
    }

    // The update function for the localization task.
    void update() {
        // ---------- Move Particles With Robot ----------
        double inertialMeasurement = inertial.get_heading(); // cw degrees, east=0
        double angleDeg = 360.0 - inertialMeasurement;       // ccw degrees, east=0
        Vector posDelta = getOdomPositionDelta(angleDeg);

        double angle = angleDeg * DEG_TO_RAD; // ccw radians, east=0

        // TODO: Remove need to skip first frame
        // Odom reading will be inaccurate the first time
        if (firstFrame) {
            firstFrame = false;
            return;
        }

        for (Particle& p : particles) {
            Vector posDeltaCartesianNoisy =
                rotate(posDelta, angleDistribution(utilities::getGenerator())) * magDistribution(utilities::getGenerator());
            p.pos += posDeltaCartesianNoisy;
            // p.pos.x = std::clamp(p.pos.x + posDeltaCartesianNoisy.x, -HALF_FIELD_SIZE, HALF_FIELD_SIZE);
            // p.pos.y = std::clamp(p.pos.y + posDeltaCartesianNoisy.y, -HALF_FIELD_SIZE, HALF_FIELD_SIZE);
        }

        // ---------- Check if Update Necessary ----------
        // Won't update unless the robot has travelled a certain distance
        // TODO: Could improve by incorporating angular movement too
        distanceSinceUpdate += posDelta.magnitude(); // Not super accurate, but easy

        int time = pros::millis();
        if ((distanceSinceUpdate < MAX_DIST_SINCE_UPDATE &&
             time - lastUpdateTime < MAX_UPDATE_INTERVAL &&
             angleChangeSinceUpdate < MAX_ANGLE_CHANGE_SINCE_UPDATE) &&
            isResampling) {
            // Re-estimate pose
            Vector sumPos;

            for (Particle& p : particles) {
                sumPos += p.pos;
            }

            predictedPose = Pose{
                sumPos.x / static_cast<double>(NUM_PARTICLES),
                sumPos.y / static_cast<double>(NUM_PARTICLES),
                angle};
            lemlibPredictedPose = lemlib::Pose{
                static_cast<float>(predictedPose.pos.x),
                static_cast<float>(predictedPose.pos.y),
                static_cast<float>(inertialMeasurement < 270.0 ? inertialMeasurement + 90.0 : inertialMeasurement - 270.0)}; // cw degrees, north=0
            chassis.setPose(lemlibPredictedPose);

            return;
        }

        distanceSinceUpdate = 0;
        angleChangeSinceUpdate = 0;
        lastUpdateTime = time;

        // ---------- Re-weight Particles Based on Sensor Measurements   ----------
        for (DistanceSensor* sensor : distanceSensors) {
            sensor->update(predictedPose, field);
        }

        double totalWeight = 0.0;
        for (Particle& p : particles) {
            if (p.pos.x < -HALF_FIELD_SIZE || p.pos.x > HALF_FIELD_SIZE || p.pos.y < -HALF_FIELD_SIZE || p.pos.y > HALF_FIELD_SIZE) {
                // p.pos.x = fieldDistribution(utilities::getGenerator());
                // p.pos.y = fieldDistribution(utilities::getGenerator());
                std::normal_distribution xDistribution{predictedPose.pos.x, START_POS_STD_DEV};
                std::normal_distribution yDistribution{predictedPose.pos.y, START_POS_STD_DEV};
                p.pos.x = std::clamp(xDistribution(utilities::getGenerator()), -HALF_FIELD_SIZE, HALF_FIELD_SIZE);
                p.pos.y = std::clamp(yDistribution(utilities::getGenerator()), -HALF_FIELD_SIZE, HALF_FIELD_SIZE);
                // p.pos.x = std::clamp(p.pos.x, -HALF_FIELD_SIZE, HALF_FIELD_SIZE);
                // p.pos.y = std::clamp(p.pos.y, -HALF_FIELD_SIZE, HALF_FIELD_SIZE);
            }

            // TODO: add case for if no sensor gets a valid measurement?
            p.weight = 1.0;
            for (DistanceSensor* sensor : distanceSensors) {
                // TODO: avoid recalculating the offset in probability function (because constant angle)
                std::optional<double> probability = sensor->probability(p, angle, field);
                if (probability.has_value()) {
                    p.weight *= probability.value();
                }
            }
            totalWeight += p.weight;
        }

        // ---------- Resample Particles ----------
        for (size_t i = 0; i < particles.size(); i++) {
            oldParticleLocations[i] = particles[i].pos;
        }

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

            particles[i].pos = oldParticleLocations[j - 1];

            sumPos += particles[i].pos;
        }

        predictedPose = Pose{
            sumPos.x / static_cast<double>(NUM_PARTICLES),
            sumPos.y / static_cast<double>(NUM_PARTICLES),
            angle};
        lemlibPredictedPose = lemlib::Pose{
            static_cast<float>(predictedPose.pos.x),
            static_cast<float>(predictedPose.pos.y),
            static_cast<float>(inertialMeasurement < 270.0 ? inertialMeasurement + 90.0 : inertialMeasurement - 270.0)}; // cw degrees, north=0
        chassis.setPose(lemlibPredictedPose);
    }
} // namespace localization