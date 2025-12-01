// #pragma once
// #include "custom-utilities.h"
// #include "distance-sensor.h"
// #include "globals.h"
// #include "main.h"
// #include "periodic-task.h"
// #include "position.h"
// #include "vector.h"

// // A namespace to hold all the code needed for localization
// namespace localization {
//     // -------------------- Constants --------------------

//     // TODO: Tune these values
//     // constexpr double STD_DEV = 0.2;             // inches
//     constexpr double MAX_DIST_SINCE_UPDATE = 2; // inches
//     constexpr int MAX_UPDATE_INTERVAL = 2000;   // milliseconds
//                                                 // TODO: edit this
//     constexpr double START_POS_STD_DEV = 5;     // inches

//     constexpr double DRIVE_NOISE = 0.05; // i.e. 5% (TODO: Change to 25% of velocity?)
//     constexpr double ANGLE_NOISE = 3.0 * utilities::DEG_TO_RAD;

//     // TODO: double check offset directions
//     constexpr double vertTrackerOffset = -0.125;   // TODO inches
//     constexpr double latTrackerOffset = -1.75;     // TODO inches
//     constexpr double vertTrackerWheelDiameter = 2; // inches
//     constexpr double latTrackerWheelDiameter = 2;  // inches

//     // TODO: Correct these values
//     // offset according to bot facing east
//     constexpr Vector frontLocalOffset{7.0, -5.875};   // inches
//     constexpr Vector backLocalOffset{-7.5, -4.25};    // inches
//     constexpr Vector rightLocalOffset{-2.1875, -6.5}; // inches
//     constexpr Vector leftLocalOffset{-2.1875, 6.5};   // inches

//     constexpr double frontTuningConst = 1.0;
//     constexpr double backTuningConst = 1.0;
//     constexpr double rightTuningConst = 1.0;
//     constexpr double leftTuningConst = 1.0;

//     constexpr size_t NUM_PARTICLES = 100;

//     constexpr int DELAY = 10;

//     // -------------------- Variables --------------------

//     // Distributions (to avoid recreating them every loop)
//     // Not const because they can't be for the function call operator
//     extern std::uniform_real_distribution<float> magDistribution;
//     extern std::uniform_real_distribution<float> angleDistribution;
//     extern std::uniform_real_distribution<float> fieldDistribution;

//     extern std::array<Particle, NUM_PARTICLES> particles;

//     extern double distanceSinceUpdate;
//     extern int lastUpdateTime;

//     extern double initialAngle;

//     // For Odometry
//     extern double prevAngle;       // bc of inertial
//     extern int prevVertTrackerVal; // I think
//     extern int prevLatTrackerVal;  // I think

//     extern DistanceSensor sensorRight;
//     extern DistanceSensor sensorLeft;
//     extern DistanceSensor sensorFront;
//     extern DistanceSensor sensorBack;

//     extern std::vector<DistanceSensor*> distanceSensors;

//     // The predicted pose in lemlib coordinates
//     extern Pose predictedPose;

//     extern PeriodicTask periodicTask;

//     // -------------------- Function Definitions --------------------
//     // ---------- External Interfacing Functions ----------

//     void start(double startX, double startY, double startA);

//     lemlib::Pose getPrediction();

//     // Print the robot's position and angle to the specified line
//     void logLocalization(int line);

//     // ---------- Algorithm Functions ----------

//     // The update function for the localization task.
//     void update();

//     // Get the position delta since the last frame using odometry
//     Vector getOdomPositionDelta();

//     // Initialize the particles on the field
//     void initParticles(double startX, double startY);

// } // namespace localization