#pragma once
#include "vector.h"

// Position Structs for use in particle filter

// Maybe not the best way to do this, but a macro makes things more convenient
// #define x(particle) particle.pos.x
// #define y(particle) particle.pos.y

// A position and heading for the robot
struct Pose {
    Pose() = default;
    Pose(double x, double y, double angle)
        : pos{x, y}, angle{angle} {}
    Pose(Vector pos, double angle)
        : pos{pos}, angle{angle} {}

    Vector pos;
    double angle;
};

// A weighted position for the robot
struct Particle {
    Particle() = default;
    Particle(double x, double y, double weight)
        : pos{x, y}, weight{weight} {}
    Particle(Vector pos, double weight)
        : pos{pos}, weight{weight} {}

    Vector pos;
    // double angle; Just assuming the inertial sensor is correct
    double weight;
};