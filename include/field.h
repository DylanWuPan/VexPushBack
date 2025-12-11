#pragma once
#include "obstacle.h"
#include <memory>
#include <vector>

class Field {
  public:
    Field(double size);
    // Field(double size, std::vector<std::unique_ptr<CircularObstacle>> obstacles);
    Field(double size, std::initializer_list<std::array<double, 3>> obstacleParams);

    std::pair<double, bool> raycast(const Vector& pos, double angle);

  private:
    const double halfFieldSize;
    const double fullFieldSize;
    // Obstacles (match loaders here)
    std::vector<std::unique_ptr<CircularObstacle>> obstacles;
    // std::make_unique<CircularObstacle>(-47, -65.7, 4.5),
    // std::make_unique<CircularObstacle>(47, -65.7, 4.5),
    // std::make_unique<CircularObstacle>(-47, 65.7, 4.5),
    // std::make_unique<CircularObstacle>(47, 65.7, 4.5),
};