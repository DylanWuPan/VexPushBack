#pragma once
#include "custom-utilities.h"
#include "distance-sensor.h"
#include "field.h"
#include "globals.h"
#include "main.h"
#include "obstacle.h"
#include "periodic-task.h"
#include "position.h"
#include "vector.h"
#include <memory>

// A namespace to hold all the code needed for localization
namespace localization {
    // -------------------- Constants --------------------

    // TODO: Tune these values
    constexpr double MAX_DIST_SINCE_UPDATE = 1.0; // inches
    constexpr int MAX_UPDATE_INTERVAL = 2000;   // milliseconds
                                                // TODO: edit this
    constexpr double START_POS_STD_DEV = 3;     // inches

    constexpr double DRIVE_NOISE = 0.05; // i.e. 5% (TODO: Change to 25% of velocity?)
    constexpr double ANGLE_NOISE = 3.0 * utilities::DEG_TO_RAD;

    // TODO: double check offset directions
    constexpr double vertTrackerOffset = -0.125;      // TODO inches
    constexpr double latTrackerOffset = -1.75;        // TODO inches
    constexpr double vertTrackerWheelRad = 2.0 / 2.0; // inches
    constexpr double latTrackerWheelRad = 2.0 / 2.0;  // inches

    // TODO: Correct these values
    // offset according to bot facing east
    constexpr Vector frontLocalOffset{7.0, -5.875};   // inches
    constexpr Vector backLocalOffset{-7.5, -4.25};    // inches
    constexpr Vector rightLocalOffset{-2.1875, -6.5}; // inches
    constexpr Vector leftLocalOffset{-2.1875, 6.5};   // inches

    constexpr double frontTuningConst = 1.0;
    constexpr double backTuningConst = 0.98;
    constexpr double rightTuningConst = 0.98;
    constexpr double leftTuningConst = 0.99;

    constexpr size_t NUM_PARTICLES = 250;

    constexpr int DELAY = 10;

    // -------------------- Variables --------------------

    // Distributions (to avoid recreating them every loop)
    // Not const because they can't be for the function call operator
    extern std::uniform_real_distribution<float> magDistribution;
    extern std::uniform_real_distribution<float> angleDistribution;
    // extern std::normal_distribution<float> magDistribution;
    // extern std::normal_distribution<float> angleDistribution;
    extern std::uniform_real_distribution<float> fieldDistribution;

    extern std::array<Particle, NUM_PARTICLES> particles;

    extern bool firstFrame;

    extern double distanceSinceUpdate;
    extern int lastUpdateTime;

    extern double initialAngle;

    // For Odometry
    extern double prevAngle;       // bc of inertial
    extern int prevVertTrackerVal; // I think
    extern int prevLatTrackerVal;  // I think

    extern DistanceSensor sensorRight;
    extern DistanceSensor sensorLeft;
    extern DistanceSensor sensorFront;
    extern DistanceSensor sensorBack;

    extern const std::vector<DistanceSensor*> distanceSensors;

    extern Field field;

    // The predicted pose in lemlib coordinates
    extern Pose predictedPose;

    extern PeriodicTask periodicTask;

    // -------------------- Function Definitions --------------------
    // ---------- External Interfacing Functions ----------

    void start(double startX, double startY, double startA);

    lemlib::Pose getPrediction();

    // Print the robot's position and angle to the specified line
    void logLocalization(int line);

    // ---------- Algorithm Functions ----------

    // The update function for the localization task.
    void update();

    // Get the position delta since the last frame using odometry
    Vector getOdomPositionDelta();

    // Initialize the particles on the field
    void initParticles(double startX, double startY);

} // namespace localization