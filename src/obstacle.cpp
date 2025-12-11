#include "obstacle.h"
#include "custom-utilities.h"

CircularObstacle::CircularObstacle(double x, double y, double rad)
    : pos{x, y}, radSquared{rad * rad} {}
CircularObstacle::CircularObstacle(Vector pos, double rad)
    : pos{pos}, radSquared{rad * rad} {}

std::optional<double> CircularObstacle::raycast(const Vector& rayPos, double angle, const Vector& stepVector) {
    Vector posRelative = pos - rayPos;
    if (((stepVector.x < 0) == (posRelative.x < 0) &&
         (stepVector.y < 0) == (posRelative.y < 0)) ||
        posRelative.magnitudeSquared() <= radSquared) {

        double proj = utilities::dot(posRelative, stepVector);
        double perpDistSquared = posRelative.magnitudeSquared() - proj * proj;

        if (perpDistSquared <= radSquared) {
            return proj - sqrt(radSquared - perpDistSquared);
        }
    }
    return std::nullopt;
}
