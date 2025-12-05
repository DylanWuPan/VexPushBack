// #include "distance-sensor.h"
// #include <cmath>

// // angleOffset in ccw radians, east=0, posOffset according to robot facing east
// DistanceSensor::DistanceSensor(Vector posOffset, double angleOffset, const double tuningConst, pros::Distance& sensor)
//     : posOffset(posOffset), angleOffset{angleOffset}, tuningConst{tuningConst}, sensor{sensor}, measurement{0.0}, exit{false}, stdDev{0.0} {}

// void DistanceSensor::update() {
//     const int rawMeasurement = sensor.get();

//     exit = rawMeasurement >= 9999;

//     measurement = tuningConst * static_cast<double>(rawMeasurement) * utilities::MM_TO_INCHES;

//     // 1/64 = 0.015625
//     stdDev = 0.2 * measurement / std::sqrt(static_cast<double>(sensor.get_confidence()) * 0.015625);
// }

// // gets the probability of getting the measurement given position and angle (in ccw radians, east=0)
// std::optional<double> DistanceSensor::probability(const Particle& particle, double angle) {
//     if (exit)
//         return std::nullopt;

//     double sensorAngle = angle + angleOffset; // ccw radians, east=0

//     // TODO: avoid recalculating offset every time
//     Vector pos = particle.pos + utilities::rotate(posOffset, angle);

//     double predicted = utilities::rayWallIntersectDistance(pos, sensorAngle);

//     return utilities::approxNormPDF((predicted - measurement) / stdDev);
// }