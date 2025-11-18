
// #include "localization.h"

// // Maybe not the best way to do this, but a macro makes things more convenient
// #define x(particle) particle.pos.x
// #define y(particle) particle.pos.y

// // A namespace to hold all the code needed for localization
// namespace localization {
// 	using namespace devices;
// 	using namespace utilities;

// 	// -------------------- Variables --------------------
	
// 	// ---------- Particles ----------

// 	std::vector<Particle> particles;

// 	// ---------- Robot Pose ----------

// 	// double robotAngle{0};
//     // double initialAngle{0};
// 	// Vector robotPos{};

// 	double distanceSinceUpdate{0};

//     // ---------- Odometry ----------

// 	double prevAngle = 0; // bc of inertial
// 	int prevVertTrackerVal = 0; // I think
// 	int prevLatTrackerVal = 0; // I think

// 	// ---------- Task ----------

//     PeriodicTask periodicTask{update, DELAY, "Localization Task"};
// 	bool first = true;

// 	double getRobotAngle();

// 	// -------------------- Function Definitions --------------------
// 	// ---------- External Interfacing Functions ----------

// 	Pose estimatePose() {
// 		double x = 0;
//         double y = 0;
//         // NOTE: Different than other angle calc because of Lemlib
// 		double angle = -inertial.get_heading(); // TODO: Odometry get angle + Check this
// 		for (const Particle& p : particles) {
// 			x += x(p) * p.weight;
// 			y += y(p) * p.weight;
// 		}
// 		return Pose{x, y, angle};
// 	}
	
// 	// // Manually set the robot's position
// 	// void setPosition(Vector position) {
// 	// 	robotPos = position;
// 	// }
// 	// // Manually set the robot's position
// 	// void setPosition(double posX, double posY) {
// 	// 	robotPos.x = posX;
// 	// 	robotPos.y = posY;
// 	// }

// 	// Print the robot's position and angle to the specified line
// 	void logLocalization(int line) {
//         Pose pose = estimatePose();
// 		pros::lcd::print(line, "x: %g, y: %g, angle: %g", round(x(pose) * 100) * 0.01, round(y(pose) * 100) * 0.01, pose.angle);
// 	}

// 	// ---------- Algorithm Functions ----------

// 	// Initialize the particles to random positions on the field
//     void initParticles(double startX, double startY) {
// 		particles.clear(); // safety
//         for (int i = 0; i < NUM_PARTICLES; ++i) {
//             Particle p;
//             x(p) = std::clamp(getRandomGaussian(startX, START_POS_STD_DEV), 0.0, 144.0);
//             y(p) = std::clamp(getRandomGaussian(startY, START_POS_STD_DEV), 0.0, 144.0);;
//             // p.angle = getRandomDoubleInRange(0.0, 360.0);
//             p.weight = 1.0 / NUM_PARTICLES;
//             particles.push_back(p);
//         }
//     }

// 	double randomNoise() {
// 		return (rand() % 10 - 5) * 0.1;
// 	}

//     Vector getOdomPositionDelta() {
//         // Odometry
//         // TODO: Adjust if there is no prev value for trackers and stuff???
//         const double angleVal = 360 - inertial.get_heading(); // TODO: might have to adjust for wraparound
//         double angleDelta = (angleVal - prevAngle) * DEG_TO_RAD;
//         if (angleDelta > 180) angleDelta -= 360; // possibly unnecesary
//         if (angleDelta < -180) angleDelta += 360;

//         const int vertTrackerVal = vertTracker.get_angle();
//         int vertTrackerDelta = vertTrackerVal - prevVertTrackerVal; // might have to adjust for wraparound
//         if (vertTrackerDelta > 18000) vertTrackerDelta -= 36000;
//         if (vertTrackerDelta < -18000) vertTrackerDelta += 36000;
//         const double vertTrackerDeltaDist = vertTrackerDelta * 0.01 * DEG_TO_RAD * vertTrackerWheelDiameter * 0.5;

//         const int latTrackerVal = latTracker.get_angle();
//         int latTrackerDelta = latTrackerVal - prevLatTrackerVal; // might have to adjust for wraparound
//         if (latTrackerDelta > 18000) latTrackerDelta -= 36000;
//         if (latTrackerDelta < -18000) latTrackerDelta += 36000;
//         const double latTrackerDeltaDist = latTrackerDelta * 0.01 * DEG_TO_RAD * latTrackerWheelDiameter * 0.5;

//         double localDeltaX;
//         double localDeltaY;
//         // TODO: no angle change case (infinite radius, divide by zero)
//         if (angleDelta == 0) { // will this work??
//             localDeltaX = vertTrackerDeltaDist;
//             localDeltaY = latTrackerDeltaDist;
//         } else {
//             localDeltaX = 2 * sin(angleDelta/2) * (vertTrackerDeltaDist / angleDelta - vertTrackerOffset); // double check
//             // turn radius is latTrackerDeltaDist / angleDelta - latTrackerOffset
//             localDeltaY = 2 * sin(angleDelta/2) * (latTrackerDeltaDist / angleDelta - latTrackerOffset);
//         }

//         const double avrgAngle = ((prevAngle + angleVal) * 0.5) * DEG_TO_RAD; // TODO: is this the angle we want to rotate by???
//         const double globalDeltaX = localDeltaX * cos(avrgAngle) - localDeltaY * sin(avrgAngle);
//         const double globalDeltaY = localDeltaY * cos(avrgAngle) + localDeltaX * sin(avrgAngle);

//         prevAngle = angleVal;
//         prevVertTrackerVal = vertTrackerVal;
//         prevLatTrackerVal = latTrackerVal;

//         return Vector{globalDeltaX, globalDeltaY};
//     }

// 	// The update function for the localization task.
// 	// TODO: Change to just use inertial sensor for angle measurement
// 	void update() {
// 		// ---------- Move Particles With Robot ----------
// 		// NOTE: Using uniform noise instead of gaussian noise for speed
// 		// TODO: Tune noise generation
// 		Vector posDelta = getOdomPositionDelta(); // TODO: Get somehow - odometry
// 		// double angleDelta = 0; // TODO: Get somehow - odometry
// 		for (auto &p : particles) {
// 			// TODO: There might be a better way to add noise
// 			x(p) += posDelta.x + randomNoise(); // + gaussian_noise();
// 			y(p) += posDelta.y + randomNoise(); // + gaussian_noise();
// 			// p.angle += angleDelta + randomNoise(); // + gaussian_noise();
// 		}

// 		// ---------- Check if Update Necessary ----------
// 		// Won't update unless the robot has travelled a certain distance
// 		// TODO: Could make better by incorporating angular movement too
// 		distanceSinceUpdate += posDelta.magnitude(); // Not super accurate, but easy
// 		if (distanceSinceUpdate < MAX_DIST_SINCE_UPDATE && periodicTask.getTimeSinceLastUpdate() < MAX_UPDATE_INTERVAL) {
// 			return;
// 		}
		
// 		// ---------- Re-weight Particles Based on Sensor Measurements   ----------
// 		double sensorFront = distanceFront.get() * MM_TO_INCHES;
// 		double sensorBack = distanceBack.get() * MM_TO_INCHES;
// 		double sensorRight = distanceRight.get() * MM_TO_INCHES;
// 		double sensorLeft = distanceLeft.get() * MM_TO_INCHES;
//         // TODO: Check if inertial increases CW or CCW
// 		double angle = -inertial.get_heading() * DEG_TO_RAD; // TODO: Get angle

//         // TODO: This might be expensive, so instead could calculate the offset only once with a constant angle
//         Vector offsetFront = rotate(frontLocalOffset, angle);
//         Vector offsetBack = rotate(backLocalOffset, angle);
//         Vector offsetRight = rotate(rightLocalOffset, angle);
//         Vector offsetLeft = rotate(leftLocalOffset, angle);

// 		double totalWeight = 0.0;
// 		for (Particle& p : particles) {
// 			// TODO: raycast including field elements
// 			double expectedFront = rayWallIntersectDistance(p.pos + offsetFront, angle);
// 			double expectedBack = rayWallIntersectDistance(p.pos + offsetBack, angle + M_PI);
// 			double expectedRight = rayWallIntersectDistance(p.pos + offsetRight, angle - M_PI / 2);
// 			double expectedLeft = rayWallIntersectDistance(p.pos + offsetLeft, angle + M_PI / 2);
		
// 			// TODO: Could instead compute a different standard deviation based off the distance measurement
// 			// The VEX specs say that the measurement will be within 5% error
// 			// TODO: 2654e uses a cheaper version of the gaussian distribution
// 			// TODO: Utilize the getConfidence method on the sensors to improve probability
// 			double probFront = gaussian(sensorFront - expectedFront, STD_DEV);
// 			double probBack = gaussian(sensorBack - expectedBack, STD_DEV);
// 			double probRight = gaussian(sensorFront - expectedFront, STD_DEV);
// 			double probLeft = gaussian(sensorBack - expectedBack, STD_DEV);
// 			// TODO: Is multiplying the probabilities the best way to do this?
// 			p.weight = probFront * probBack * probRight * probLeft;
// 			totalWeight += p.weight;
// 		}

// 		// ---------- Normalize Particle Weights ----------
// 		for (Particle& p : particles) {
// 			p.weight /= totalWeight;
// 		}

// 		// ---------- Resample Particles ----------
// 		// TODO: 2654e uses a different sampling method to help preserve variety
// 		std::vector<Particle> newParticles;
// 		double index = rand() % NUM_PARTICLES;
// 		double beta = 0.0;
// 		double maxWeight = 0.0;
// 		for (const Particle& p : particles) {
// 			if (p.weight > maxWeight) maxWeight = p.weight;
// 		}
	
// 		for (int i = 0; i < NUM_PARTICLES; i++) {
// 			beta += (rand() / RAND_MAX) * 2.0 * maxWeight;
// 			while (beta > particles[static_cast<int>(index)].weight) {
// 				beta -= particles[static_cast<int>(index)].weight;
// 				index = fmod((index + 1), NUM_PARTICLES);
// 			}
// 			newParticles.push_back(particles[static_cast<int>(index)]);
// 		}
// 		particles = newParticles;
// 	}

//     // Sets up and starts the localization task with x-y position in inches and angle in radians
// 	void start(double startX, double startY, double startA) {
// 		vertTracker.reset();
// 		latTracker.reset();
// 		inertial.tare();
//         inertial.set_heading(startA); // TODO: Check

//         initParticles(startX, startY);

// 		periodicTask.start();
// 	}

// } // namespace localization