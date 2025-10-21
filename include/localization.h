// #pragma once
// #include "main.h"
// #include "vector.h"
// #include "globals.h"
// #include "custom-utilities.h"
// #include "periodic-task.h"

// // Maybe not the best way to do this, but a macro makes things more convenient
// #define x(particle) particle.pos.x
// #define y(particle) particle.pos.y

// // A namespace to hold all the code needed for localization
// namespace localization {
// 	using namespace devices;
// 	using namespace utilities;

// 	// -------------------- Variables --------------------
// 	// ---------- Tuning ----------
// 	// TODO: Tune these values
// 	constexpr double STD_DEV = 0.2; // inches
// 	constexpr double MAX_DIST_SINCE_UPDATE = 0.5; // inches
// 	constexpr int MAX_UPDATE_INTERVAL = 2000; // milliseconds

// 	// TODO: Correct these values
// 	const Vector frontLocalOffset{0,0};
// 	const Vector backLocalOffset{0,0};
// 	const Vector rightLocalOffset{0,0};
// 	const Vector leftLocalOffset{0,0};
	
// 	// ---------- Pose ----------

// 	// A position and heading for the robot
//     struct Pose {
//         Pose() = default;
//         Pose(double x, double y, double angle)
//             : pos{x, y}, angle{angle} {}
		
// 		Vector pos;
//         double angle;
//     };

// 	// ---------- Particles ----------

// 	// A weighted position for the robot
//     struct Particle {
//         Particle() = default;
//         Particle(double x, double y, double weight)
//             : pos{x, y}, weight{weight} {}
		
// 		Vector pos;
//         // double angle; Just assuming the inertial sensor is correct
//         double weight;
//     };

// 	constexpr int NUM_PARTICLES = 300;
// 	std::vector<Particle> particles;

// 	// ---------- Robot Pose ----------

// 	double robotAngle{0};
// 	Vector robotPos{};

// 	double distanceSinceUpdate;

// 	// ---------- Task ----------

//     void start(double startX, double startY, double startA);
//     void update();
//     PeriodicTask periodicTask{update, DELAY};
// 	bool first = true;

// 	double getRobotAngle();

// 	// -------------------- Function Definitions --------------------
// 	// ---------- External Interfacing Functions ----------

// 	Pose estimatePose() {
// 		double x = 0, y = 0;
// 		double angle = 0; // TODO: Odometry get angle
// 		for (const Particle& p : particles) {
// 			x += x(p) * p.weight;
// 			y += y(p) * p.weight;
// 		}
// 		return {x, y, angle};
// 	}
	
// 	// Manually set the robot's position
// 	void setPosition(Vector position) {
// 		robotPos = position;
// 	}
// 	// Manually set the robot's position
// 	void setPosition(double posX, double posY) {
// 		robotPos.x = posX;
// 		robotPos.y = posY;
// 	}

// 	// Print the robot's position and angle to the specified line
// 	void logLocalization(int line) {
// 		pros::lcd::print(line, "x: %g, y: %g, angle: %g", round(robotPos.x * 100) * 0.01, round(robotPos.y * 100) * 0.01, getRobotAngle());
// 	}

// 	// ---------- Algorithm Functions ----------

// 	// Initialize the particles to random positions on the field
//     void initParticles() {
//         // TODO: Improve by placing particles around the starting position
// 		particles.clear(); // safety
//         for (int i = 0; i < NUM_PARTICLES; ++i) {
//             Particle p;
//             x(p) = getRandomDoubleInRange(0.0, 144.0);
//             y(p) = getRandomDoubleInRange(0.0, 144.0);
//             // p.angle = getRandomDoubleInRange(0.0, 360.0);
//             p.weight = 1.0 / NUM_PARTICLES;
//             particles.push_back(p);
//         }
//     }

// 	double randomNoise() {
// 		return (rand() % 10 - 5) * 0.1;
// 	}

// 	// The update function for the localization task.
// 	// TODO: Change to just use inertial sensor for angle measurement
// 	void update() {
// 		// ---------- Move Particles With Robot ----------
// 		// NOTE: Using uniform noise instead of gaussian noise for speed
// 		// TODO: Tune noise generation
// 		Vector posDelta{0,0}; // TODO: Get somehow
// 		double angleDelta = 0; // TODO: Get somehow
// 		for (auto &p : particles) {
// 			// TODO: There might be a better way to add noise
// 			x(p) += posDelta.x + randomNoise(); // + gaussian_noise();
// 			y(p) += posDelta.y + randomNoise(); // + gaussian_noise();
// 			// p.angle += angleDelta + randomNoise(); // + gaussian_noise();
// 		}

// 		// ---------- Check if Update Necessary ----------
// 		// Won't update unless the robot has travelled a certain distance
// 		// TODO: Could make better by incorporating angular movement too
// 		distanceSinceUpdate += posDelta.magnitude();
// 		if (distanceSinceUpdate < MAX_DIST_SINCE_UPDATE && pros::millis() - time < MAX_UPDATE_INTERVAL) {
// 			return;
// 		}
		
// 		// ---------- Re-weight Particles Based on Sensor Measurements   ----------
// 		double sensorFront = frontDistance.get() * MM_TO_INCHES;
// 		double sensorBack = backDistance.get() * MM_TO_INCHES;
// 		double sensorRight = rightDistance.get() * MM_TO_INCHES;
// 		double sensorLeft = leftDistance.get() * MM_TO_INCHES;
// 		double angle = 0; // TODO: Get angle

// 		double totalWeight = 0.0;
// 		for (Particle& p : particles) {
// 			// TODO: This might be expensive, so instead could calculate the offset only once with a constant angle
// 			Vector offsetFront = rotate(frontLocalOffset, angle);
// 			Vector offsetBack = rotate(backLocalOffset, angle);
// 			Vector offsetRight = rotate(rightLocalOffset, angle);
// 			Vector offsetLeft = rotate(leftLocalOffset, angle);

// 			// TODO: raycast including field elements
// 			double expectedFront = rayWallIntersectDistance(p.pos + offsetFront, angle);
// 			double expectedBack = rayWallIntersectDistance(p.pos + offsetBack, angle + M_PI);
// 			double expectedRight = rayWallIntersectDistance(p.pos + offsetRight, angle - M_PI / 2);
// 			double expectedLeft = rayWallIntersectDistance(p.pos, angle + M_PI / 2);
// 			// same for left, right
		
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

//     double getRobotAngle() {
//         return robotAngle;
//     }

//     // Sets up and starts the localization task
// 	void start(double startX, double startY, double startA) {
// 		robotAngle = startA;
// 		// angleOffset = startA;
// 		setPosition(startX, startY);

// 		vertTracker.reset();
// 		latTracker.reset();
// 		inertial.tare();

//         initParticles();

// 		periodicTask.start();
// 	}

// } // namespace localization