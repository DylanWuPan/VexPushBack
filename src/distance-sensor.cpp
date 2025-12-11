#include "distance-sensor.h"
#include "obstacle.h"
#include <cmath>

// angleOffset in ccw radians, east=0, posOffset according to robot facing east
DistanceSensor::DistanceSensor(Vector posOffset, double angleOffset, const double tuningConst, pros::Distance& sensor)
    : posOffset(posOffset), angleOffset{angleOffset}, tuningConst{tuningConst}, sensor{sensor}, measurement{0.0}, exit{false}, stdDev{0.0} {}

void DistanceSensor::update() {
    // const int rawMeasurement = sensor.get();

    // exit = rawMeasurement >= 9999;

    // measurement = tuningConst * static_cast<double>(rawMeasurement) * utilities::MM_TO_INCHES;
    measurement = tuningConst * static_cast<double>(sensor.get()) * utilities::MM_TO_INCHES;

    exit = measurement >= utilities::FULL_FIELD_SIZE;

    // 1/64 = 0.015625
    stdDev = 0.2 * measurement / std::sqrt(static_cast<double>(sensor.get_confidence()) * 0.015625);
}

// gets the probability of getting the measurement given position and angle (in ccw radians, east=0)
std::optional<double> DistanceSensor::probability(const Particle& particle, double angle, Field& field, bool print) {
    if (exit) {
        return std::nullopt;
    }

    double sensorAngle = angle + angleOffset; // ccw radians, east=0

    // TODO: avoid recalculating offset every time
    Vector pos = particle.pos + utilities::rotate(posOffset, angle);

    // double predicted = utilities::rayWallIntersectDistance(pos, sensorAngle);
    std::pair<double, bool> predicted = field.raycast(pos, sensorAngle);
    // if (print)
    //     pros::lcd::print(3, "x: %g, y: %g, a: %g, l: %g",
    //                      round(pos.x * 100) * 0.01,
    //                      round(pos.y * 100) * 0.01,
    //                      round(sensorAngle * utilities::RAD_TO_DEG * 100) * 0.01,
    //                      round(predicted * 100) * 0.01);

    // TODO: not great
    return utilities::approxNormPDF((predicted.first - measurement) / stdDev);
    // return utilities::gaussian((predicted - measurement), stdDev);
}