#pragma once
#include <cmath>
#include <random>
#include "vector.h"

namespace utilities {
    // ---------- Constants ----------
    // Conversions
    
    // NOTE: will change with different drive configurations
    constexpr double INCHES_TO_TICKS = 300 * 48 / 36 / M_PI / 2.75;
    // NOTE: will change with different drive configurations
    constexpr double TICKS_TO_INCHES = 2.75 * M_PI / 300 * 36 / 48;
    constexpr double MM_TO_INCHES = 0.0393700787;
    constexpr double DEG_TO_RAD = M_PI / 180;
    constexpr double RAD_TO_DEG = 180 / M_PI;
    
    constexpr double TWO_PI = 2 * M_PI;

    constexpr double FIELD_SIZE = 144.0;

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

    constexpr double resetAngleThreshold = 10;
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
    std::mt19937& getGenerator();
    
    // Generates a random number from [0, 1) using a uniform distribution
    double getRandomZeroOne();
    
    // Generates a random number from [min, max) using a uniform distribution
    double getRandomDoubleInRange(double min, double max);
    
    // Computes the value of the Gaussian (normal) distribution at x
    double gaussianWithMean(double x, double mean, double stddev);

    // TODO: 2654e uses a cheaper version of this
    // Computes the value of the Gaussian (normal) distribution at x
    double gaussian(double x, double stddev);
    // ---------- Device Interfacing ----------
    
    // Get the average position of all the drive motors
    double getAverageMotorPos();
} // namespace utilities