#include "distance-sensor.h"
#include "custom-utilities.h"
#include "obstacle.h"
#include <cmath>

// angleOffset in ccw radians, east=0, posOffset according to robot facing east
DistanceSensor::DistanceSensor(Vector posOffset, double angleOffset, const double tuningConst, pros::Distance& sensor)
    : posOffset(posOffset), angleOffset{angleOffset}, tuningConst{tuningConst}, sensor{sensor}, measurement{0.0}, exit{false}, stdDev{0.0} {}

void DistanceSensor::update(const Pose& pose, const Field& field) {
    // bool invalid = false;

    // for (const Vector& corner : field.corners) {
    //     Vector posRelative = corner - pose.pos; // TODO: check
    //     Vector edgeA{cos(pose.angle - ANGLE_THRESHOLD), sin(pose.angle - ANGLE_THRESHOLD)};
    //     Vector edgeB{cos(pose.angle + ANGLE_THRESHOLD), sin(pose.angle + ANGLE_THRESHOLD)};
    //     if ((utilities::cross(edgeA, posRelative) < 0 && utilities::cross(posRelative, edgeB) < 0) ||
    //         (utilities::cross(edgeA, posRelative) > 0 && utilities::cross(posRelative, edgeB) > 0)) {
    //         invalid = true;
    //         break;
    //     }
    // }

    // const int rawMeasurement = sensor.get();

    // exit = rawMeasurement >= 9999;

    // measurement = tuningConst * static_cast<double>(rawMeasurement) * utilities::MM_TO_INCHES;
    measurement = tuningConst * static_cast<double>(sensor.get()) * utilities::MM_TO_INCHES;

    exit = (measurement >= utilities::FULL_FIELD_DIAGONAL);// || invalid;

    // 1/64 = 0.015625, 0.05 is a tuned constant
    stdDev = 0.05 * measurement / std::sqrt(static_cast<double>(sensor.get_confidence()) * 0.015625);
}

// gets the probability of getting the measurement given position and angle (in ccw radians, east=0)
std::optional<double> DistanceSensor::probability(const Particle& particle, double angle, Field& field) {
    if (exit) {
        return std::nullopt;
    }

    double sensorAngle = angle + angleOffset; // ccw radians, east=0

    // TODO: avoid recalculating offset every time
    Vector pos = particle.pos + utilities::rotate(posOffset, angle);

    // double predicted = utilities::rayWallIntersectDistance(pos, sensorAngle);
    double predicted = field.raycast(pos, sensorAngle);

    return utilities::approxNormPDF((predicted - measurement) / stdDev);
    // return utilities::gaussian((predicted - measurement), stdDev);
}