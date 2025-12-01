// #pragma once
// #include "custom-utilities.h"
// #include "main.h"
// #include "position.h"
// #include "vector.h"

// class DistanceSensor {
//   private:
//     Vector posOffset;
//     double angleOffset;
//     double tuningConst;
//     pros::Distance& sensor;

//     double measurement;
//     bool exit;
//     double stdDev;

//   public:
//     // angleOffset in ccw radians, east=0, posOffset according to robot facing east
//     DistanceSensor(Vector posOffset, double angleOffset, double tuningConst, pros::Distance& sensor);

//     void update();

//     // gets the probability of getting the measurement given position and angle (in ccw radians, east=0)
//     std::optional<double> probability(const Particle& particle, double angle);

//     ~DistanceSensor() = default;
// };