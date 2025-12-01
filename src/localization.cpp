
// #include "localization.h"

// using namespace devices;
// using namespace utilities;

// // A namespace to hold all the code needed for localization
// namespace localization {
//     // -------------------- Variables --------------------

//     // Distributions (to avoid recreating them every loop)
//     // Not const because they can't be for the function call operator
//     std::uniform_real_distribution<float> magDistribution(1 - DRIVE_NOISE, 1 + DRIVE_NOISE);
//     std::uniform_real_distribution<float> angleDistribution(-ANGLE_NOISE, ANGLE_NOISE);
//     std::uniform_real_distribution<float> fieldDistribution(-HALF_FIELD_SIZE, HALF_FIELD_SIZE);

//     std::array<Particle, NUM_PARTICLES> particles;

//     double distanceSinceUpdate{0};
//     int lastUpdateTime{0};

//     // For odometry
//     double prevAngle{0};
//     int prevVertTrackerVal{0};
//     int prevLatTrackerVal{0};

//     DistanceSensor sensorRight{rightLocalOffset, -HALF_PI, rightTuningConst, distanceRight};
//     DistanceSensor sensorLeft{leftLocalOffset, HALF_PI, leftTuningConst, distanceLeft};
//     DistanceSensor sensorFront{frontLocalOffset, 0, frontTuningConst, distanceRight};
//     DistanceSensor sensorBack{backLocalOffset, M_PI, backTuningConst, distanceBack};

//     std::vector<DistanceSensor*> distanceSensors{&sensorRight, &sensorLeft, &sensorFront, &sensorBack};

//     // The predicted pose in lemlib coordinates
//     Pose predictedPose;

//     PeriodicTask periodicTask{update, DELAY, "Localization Task"};

//     // -------------------- Functions --------------------
//     // ---------- External Interfacing Functions ----------

//     // Sets up and starts the localization task with x-y position in inches
//     // and angle in cw degrees, north=0
//     void start(double startX, double startY, double startA) {
//         vertTracker.reset();
//         latTracker.reset();
//         inertial.tare();
//         inertial.set_heading(angleRangeZeroTo360(startA - 90)); // cw degrees, east=0

//         initParticles(startX - 72, startY - 72);

//         periodicTask.start();
//     }

//     lemlib::Pose getPrediction() {
//         return lemlib::Pose{
//             static_cast<float>(predictedPose.pos.x),
//             static_cast<float>(predictedPose.pos.y),
//             static_cast<float>(predictedPose.angle)};
//     }

//     // Print the robot's position and angle to the specified line
//     void logLocalization(int line) {
//         lemlib::Pose pose = getPrediction();
//         pros::lcd::print(
//             line,
//             "x: %g, y: %g, angle: %g",
//             round(pose.x * 100) * 0.01,
//             round(pose.y * 100) * 0.01,
//             round(pose.theta * 100) * 0.01);
//     }

//     // ---------- Algorithm Functions ----------

//     // Initialize the particles to random positions on the field
//     void initParticles(double startX, double startY) {
//         std::normal_distribution xDistribution{startX, START_POS_STD_DEV};
//         std::normal_distribution yDistribution{startY, START_POS_STD_DEV};
//         for (size_t i = 0; i < NUM_PARTICLES; ++i) {
//             Particle p{};
//             // TODO: Would probably be better to do this in polar coordinates
//             p.pos.x = std::clamp(xDistribution(utilities::getGenerator()), -HALF_FIELD_SIZE, HALF_FIELD_SIZE);
//             p.pos.y = std::clamp(yDistribution(utilities::getGenerator()), -HALF_FIELD_SIZE, HALF_FIELD_SIZE);
//             p.weight = 1.0 / NUM_PARTICLES;
//             particles[i] = p;
//         }
//     }

//     // Get the position delta since the last frame using odometry
//     Vector getOdomPositionDelta() {
//         const double angleVal = 360.0 - inertial.get_heading();  // ccw degrees, east=0
//         double angleDelta = (angleVal - prevAngle) * DEG_TO_RAD; // ccw radians, east=0 (relative)
//         // shortcut because the robot is unlikely to turn >360 degrees in a frame
//         if (angleDelta > M_PI)
//             angleDelta -= TWO_PI;
//         if (angleDelta < -M_PI)
//             angleDelta += TWO_PI;

//         const int vertTrackerVal = vertTracker.get_angle();
//         int vertTrackerDelta = vertTrackerVal - prevVertTrackerVal; // might have to adjust for wraparound
//         if (vertTrackerDelta > 18000)
//             vertTrackerDelta -= 36000;
//         if (vertTrackerDelta < -18000)
//             vertTrackerDelta += 36000;
//         const double vertTrackerDeltaDist = vertTrackerDelta * 0.01 * DEG_TO_RAD * vertTrackerWheelDiameter * 0.5;

//         const int latTrackerVal = latTracker.get_angle();
//         int latTrackerDelta = latTrackerVal - prevLatTrackerVal; // might have to adjust for wraparound
//         if (latTrackerDelta > 18000)
//             latTrackerDelta -= 36000;
//         if (latTrackerDelta < -18000)
//             latTrackerDelta += 36000;
//         const double latTrackerDeltaDist = latTrackerDelta * 0.01 * DEG_TO_RAD * latTrackerWheelDiameter * 0.5;

//         double localDeltaX;
//         double localDeltaY;

//         if (angleDelta == 0) {
//             localDeltaX = vertTrackerDeltaDist;
//             localDeltaY = latTrackerDeltaDist;
//         } else {
//             localDeltaX = 2 * sin(angleDelta * 0.5) * (vertTrackerDeltaDist / angleDelta - vertTrackerOffset); // double check
//             // turn radius is latTrackerDeltaDist / angleDelta - latTrackerOffset
//             localDeltaY = 2 * sin(angleDelta * 0.5) * (latTrackerDeltaDist / angleDelta - latTrackerOffset);
//         }

//         // TODO: is this the angle we want to rotate by???
//         const double avrgAngle = ((prevAngle + angleVal) * 0.5) * DEG_TO_RAD; // ccw radians, east=0
//         const double globalDeltaX = localDeltaX * cos(avrgAngle) - localDeltaY * sin(avrgAngle);
//         const double globalDeltaY = localDeltaY * cos(avrgAngle) + localDeltaX * sin(avrgAngle);

//         prevAngle = angleVal;
//         prevVertTrackerVal = vertTrackerVal;
//         prevLatTrackerVal = latTrackerVal;

//         return Vector{globalDeltaX, globalDeltaY};
//         // Could probably return the local delta and then rotate later
//         // return Vector{localDeltaX, localDeltaY};
//     }

//     // The update function for the localization task.
//     void update() {
//         // ---------- Move Particles With Robot ----------
//         double inertialMeasurement = inertial.get_heading(); // cw degrees, east=0
//         Vector posDelta = getOdomPositionDelta();
//         double posDeltaMagnitude = posDelta.magnitude();

//         for (Particle& p : particles) {
//             // NOTE: Using uniform noise instead of gaussian noise for speed
//             Vector posDeltaCartesianNoisy =
//                 rotate(posDelta, angleDistribution(utilities::getGenerator())) * magDistribution(utilities::getGenerator());
//             // TODO: unnecessary
// 			p.pos.x += posDeltaCartesianNoisy.x;
//             p.pos.y += posDeltaCartesianNoisy.y;
//         }

//         // ---------- Check if Update Necessary ----------
//         // Won't update unless the robot has travelled a certain distance
//         // TODO: Could make better by incorporating angular movement too
//         distanceSinceUpdate += posDeltaMagnitude; // Not super accurate, but easy

//         int time = pros::millis();
// 		// pros::lcd::print(3, "dist: %g, time: %i", distanceSinceUpdate, periodicTask.getTimeSinceLastUpdate());
//         if (distanceSinceUpdate < MAX_DIST_SINCE_UPDATE && time - lastUpdateTime < MAX_UPDATE_INTERVAL) {
//             // Re-estimate pose
//             double xSum = 0.0, ySum = 0.0; // TODO: could use vector here

//             for (Particle& p : particles) {
//                 xSum += p.pos.x;
//                 ySum += p.pos.y;
//             }
// 			// pros::lcd::print(1, "x: %g, y: %g", xSum, ySum);
// 			// pros::lcd::print(2, "x: %g, y: %g", xSum / NUM_PARTICLES, ySum / NUM_PARTICLES);

//             predictedPose = Pose{
//                 72.0 + (xSum / static_cast<double>(NUM_PARTICLES)),
//                 72.0 + (ySum / static_cast<double>(NUM_PARTICLES)),
//                 angleRangeZeroTo360(90.0 + inertialMeasurement) // cw degrees, north=0
//             };
//             chassis.setPose(getPrediction());

//             return;
//         }

//         distanceSinceUpdate = 0;
//         lastUpdateTime = time;

//         // ---------- Re-weight Particles Based on Sensor Measurements   ----------
//         for (DistanceSensor* sensor : distanceSensors) {
//             sensor->update();
//         }
// 		// for (auto it = distanceSensors.begin(); it != distanceSensors.end(); ++it) {
// 		// 	(*(*it)).update();
// 		// }

//         // TODO: might not be necessary to keep this in [0, 2pi) range
//         double angle = (360.0 - inertialMeasurement) * DEG_TO_RAD; // ccw radians, east=0

//         double totalWeight = 0.0;
//         for (Particle& p : particles) {
//             if (p.pos.x < -HALF_FIELD_SIZE || p.pos.x > HALF_FIELD_SIZE || p.pos.y < -HALF_FIELD_SIZE || p.pos.y > HALF_FIELD_SIZE) {
//                 p.pos.x = fieldDistribution(utilities::getGenerator());
//                 p.pos.y = fieldDistribution(utilities::getGenerator());
//             }

//             // TODO: add case for if no sensor gets a valid measurement?
//             p.weight = 1.0; // TODO: increase for precision
//             for (int i = 0; i < distanceSensors.size(); ++i) {
// 				DistanceSensor* sensor = distanceSensors[i];
//                 // TODO: avoid recalculating the offset in probability function (because constant angle)
//                 std::optional<double> probability = sensor->probability(p, angle);
//                 if (probability.has_value()) {
// 					if (p.pos.x == particles[0].pos.x && p.pos.y == particles[0].pos.y && i == 3) {
// 						pros::lcd::print(2, "val: %g", probability.value());
// 					}
//                     p.weight *= probability.value();
//                 }
//             }
// 			if (p.pos.x == particles[0].pos.x && p.pos.y == particles[0].pos.y) {
// 				pros::lcd::print(1, "weight: %g", p.weight);
// 			}
//             totalWeight += p.weight;
//         }

//         // ---------- Resample Particles ----------
//         std::array<Particle, NUM_PARTICLES> oldParticles = particles;

//         double avgWeight = totalWeight / static_cast<double>(NUM_PARTICLES);
//         const double randWeight = utilities::getRandomDoubleInRange(0.0, avgWeight);

//         size_t j = 0;
//         double cumulativeWeight = 0.0;

//         double xSum = 0.0, ySum = 0.0; // TODO: could use vector here

//         for (size_t i = 0; i < NUM_PARTICLES; ++i) {
//             const double weight = static_cast<double>(i) * avgWeight + randWeight;

//             while (cumulativeWeight < weight) {
//                 if (j >= NUM_PARTICLES)
//                     break;
//                 cumulativeWeight += particles[j++].weight;
//             }

//             particles[i].pos = oldParticles[j - 1].pos;

//             xSum += particles[i].pos.x;
//             ySum += particles[i].pos.y;
//         }

//         predictedPose = Pose{
//             72.0 + (xSum / static_cast<double>(NUM_PARTICLES)),
//             72.0 + (ySum / static_cast<double>(NUM_PARTICLES)),
//             angleRangeZeroTo360(90.0 + inertialMeasurement) // cw degrees, north=0
//         };
//         chassis.setPose(getPrediction());
//     }
// } // namespace localization