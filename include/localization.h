// #pragma once
// #include "main.h"
// #include "vector.h"
// #include "globals.h"
// #include "custom-utilities.h"
// #include "periodic-task.h"

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
//     constexpr double START_POS_STD_DEV = 7.5;

//     constexpr double DRIVE_NOISE = 0; // TODO: Change
//     constexpr double ANGLE_NOISE = 0; // TODO: Change

// 	// TODO: double check offset directions
// 	constexpr double vertTrackerOffset = -0.4; // TODO // Offset is positive to left
// 	constexpr double latTrackerOffset = -1.5; // TODO // TODO: find offset direction
// 	constexpr double vertTrackerWheelDiameter = 2;
// 	constexpr double latTrackerWheelDiameter = 2;

// 	// TODO: Correct these values
// 	constexpr Vector frontLocalOffset{0,0};
// 	constexpr Vector backLocalOffset{0,0};
// 	constexpr Vector rightLocalOffset{0,0};
// 	constexpr Vector leftLocalOffset{0,0};
	
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
// 	extern std::vector<Particle> particles;

// 	// ---------- Robot Pose ----------

// 	// extern double robotAngle;
//     double initialAngle{0};
// 	// extern Vector robotPos;

// 	extern double distanceSinceUpdate;

//     // ---------- Odometry ----------

// 	extern double prevAngle; // bc of inertial
// 	extern int prevVertTrackerVal; // I think
// 	extern int prevLatTrackerVal; // I think

// 	// ---------- Task ----------

//     void start(double startX, double startY, double startA);
//     void update();
//     constexpr int DELAY = 10;
//     extern PeriodicTask periodicTask;
// 	extern bool first;

// 	// double getRobotAngle();

// 	// -------------------- Function Definitions --------------------
// 	// ---------- External Interfacing Functions ----------

// 	Pose estimatePose();
	
// 	// Manually set the robot's position
// 	// void setPosition(Vector position);
// 	// Manually set the robot's position
// 	// void setPosition(double posX, double posY);

// 	// Print the robot's position and angle to the specified line
// 	void logLocalization(int line);

// 	// ---------- Algorithm Functions ----------
//     // Get positiond delta since last frame
//     Vector getOdomPositionDelta();

// 	// Initialize the particles to random positions on the field
//     void initParticles();

// 	double randomNoise();

// 	// The update function for the localization task.
// 	// TODO: Change to just use inertial sensor for angle measurement
// 	void update();

//     double getRobotAngle();

//     // Sets up and starts the localization task
// 	void start(double startX, double startY, double startA);

// } // namespace localization