#include "field.h"
#include "custom-utilities.h"
#include <array>

Field::Field(double size)
    : halfFieldSize{size / 2.0}, fullFieldSize{size}, obstacles{} {}

// Field::Field(double size, std::vector<std::unique_ptr<CircularObstacle>> obstacles)
//     : halfFieldSize{size / 2.0}, fullFieldSize{size}, obstacles{obstacles} {}

Field::Field(double size, std::initializer_list<std::array<double, 3>> obstacleParams)
    : halfFieldSize{size / 2.0}, fullFieldSize{size}, obstacles{} {
    for (const std::array<double, 3>& params : obstacleParams) {
        obstacles.push_back(std::make_unique<CircularObstacle>(params[0], params[1], params[2]));
    }
}

std::pair<double, bool> Field::raycast(const Vector& pos, double angle) {
    double minDist = std::numeric_limits<double>::max();
    bool intersection = false;

    Vector stepVector{cos(angle), sin(angle)};

    for (std::unique_ptr<CircularObstacle>& obstacle : obstacles) {
        std::optional<double> dist = obstacle->raycast(stepVector, angle, stepVector);
        if (dist.has_value() && dist.value() < minDist) {
            intersection = true;
            minDist = dist.value();
        }
    }

    if (intersection) {
        return std::pair{minDist, true};
    }

    return std::pair{utilities::rayWallIntersectDistance(pos, angle), false};
}
