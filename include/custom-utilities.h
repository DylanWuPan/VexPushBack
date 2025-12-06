#pragma once
#include "lemlib/pose.hpp"
#include "vector.h"
#include <cmath>
#include <random>

namespace utilities {
    // ---------- Constants ----------

    // Conversions
    constexpr double MM_TO_INCHES = 0.0393700787;
    constexpr double DEG_TO_RAD = M_PI / 180;
    constexpr double RAD_TO_DEG = 180 / M_PI;

    constexpr double TWO_PI = 2 * M_PI;
    constexpr double HALF_PI = 0.5 * M_PI;

    constexpr double HALF_FIELD_SIZE = 70.205;

    // ---------- Distance Sensors ----------
    enum class direction {
        North,
        East,
        South,
        West
    };

    enum class distanceSensor {
        Front,
        Right,
        Back,
        Left
    };

    constexpr double RESET_ANGLE_THRESHOLD = 45.0;
    lemlib::Pose getPoseWithDistance(bool front, bool right, bool back, bool left);
    double getDistance(distanceSensor sensor);

    // ---------- Math ----------
    // ----- Quadratics -----

    // Get the roots of a quadratic
    std::pair<double, double> solveQuadratic(double a, double b, double c);
    // Check if the roots of a quadratic are real numbers
    bool quadraticError(double a, double b, double c);

    // ----- Angles -----

    // Bound an angle to [-pi, pi)
    double angleRangePNPi(double angle);
    // Bound an angle to [0, 2pi)
    double angleRangeZeroToTwoPi(double angle);
    // Bound an angle to [-180, 180)
    double angleRangePN180(double angle);
    // Bound an angle to [0, 360)
    double angleRangeZeroTo360(double angle);

    // ----- Vectors -----

    // Gives the distance between two Vectors
    double dist(Vector p1, Vector p2);

    // Gives the angle from p1 to p2 (e.g. the angle from (0,0) to (2, sqrt(3)) is pi/6)
    double angleTo(Vector p1, Vector p2);

    // Rotates a Vector around (0,0) by a specified angle in radians
    Vector rotate(Vector vec, double angle);

    // Converts a Vector to polar coordinates
    std::pair<double, double> toPolar(Vector vec);

    // Converts polar coordinates to a cartesian Vector
    Vector toCartesian(std::pair<double, double> coords);

    // ----- Intersections -----

    // Find the intersection points of a circle and a line
    std::pair<Vector, Vector> boundedCircleLineIntersect(Vector p1, Vector p2, Vector pc, double r, std::pair<bool, bool>& errorFlags);

    // TODO: Test and Optimize
    // Find the distance from a position within a square to the edge on a ray defined by an angle
    double raySquareIntersectDistance(double x, double y, double angle, double squareSize);
    // Find the distance from a position within a square to the edge on a ray defined by an angle
    double raySquareIntersectDistance(Vector startPos, double angle, double squareSize);

    // TODO: Test and Optimize
    // Find the distance from a position within a square to the edge on a ray defined by an angle
    double rayWallIntersectDistance(double x, double y, double angle);
    // Find the distance from a position within a square to the edge on a ray defined by an angle
    double rayWallIntersectDistance(Vector startPos, double angle);

    // ---------- Randomness + Probability ----------

    // Shared random number generator
    std::ranlux24_base& getGenerator();

    // Generates a random number from [0, 1) using a uniform distribution
    double getRandomZeroOne();

    // Generates a random number from [min, max) using a uniform distribution
    double getRandomDoubleInRange(double min, double max);

    // Generates a random number with a gaussian distribution and the specified mean/standard deviation
    double getRandomGaussian(double mean, double stddev);

    // Computes the value of the Gaussian (normal) distribution at x
    double gaussianWithMean(double x, double mean, double stddev);

    // Computes the value of the Gaussian (normal) distribution at x
    double gaussian(double x, double stddev);

    // Approximation of the standard normal PDF
    double approxNormPDF(const double x);

    // ---------- Device Interfacing ----------

    // Get the average position of all the drive motors
    double getAverageMotorPos();
} // namespace utilities