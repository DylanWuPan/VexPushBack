#pragma once
#include "vector.h"
#include <optional>

// Obstacle class for use in particle filter

// A position and heading for the robot
class CircularObstacle {
public:
    CircularObstacle() = default;
    CircularObstacle(double x, double y, double rad);
    CircularObstacle(Vector pos, double rad);

    // returns a distance if the specified ray hits the obstacle
    std::optional<double> raycast(const Vector& rayPos, double angle, const Vector& stepVector);

    Vector pos;
    double radSquared;
};
