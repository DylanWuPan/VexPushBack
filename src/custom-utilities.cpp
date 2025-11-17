#include <cmath>
#include "custom-utilities.h"
#include "globals.h"

namespace utilities {

    // ---------- Distance Sensors ----------

    // Gets a pose calibrated with measurements from distance sensors.
    // Front will override back and right will override left.
    lemlib::Pose getPoseWithDistance(bool front, bool right, bool back, bool left) {
        lemlib::Pose pose = devices::chassis.getPose();
        direction dir;
        double angleDifference;
        char* text;
        
        double boundedAngle = angleRangeZeroTo360(pose.theta);

        if (fabs(pose.theta) < resetAngleThreshold) {
            dir = direction::North;
            text = "North";
            angleDifference = boundedAngle * DEG_TO_RAD;
        } else if (fabs(boundedAngle - 90) < resetAngleThreshold) {
            dir = direction::East;
            text = "East";
            angleDifference = (boundedAngle - 90) * DEG_TO_RAD;
        } else if (fabs(boundedAngle - 180) < resetAngleThreshold) {
            dir = direction::South;
            text = "South";
            angleDifference = (boundedAngle - 180) * DEG_TO_RAD;
        } else if (fabs(boundedAngle - 270) < resetAngleThreshold) {
            dir = direction::West;
            text = "West";
            angleDifference = (boundedAngle - 270) * DEG_TO_RAD;
        } else {
            pros::lcd::print(1, "None");
            return pose; // at an odd angle, unable to determine position
        }
        pros::lcd::print(1, text);

        pros::lcd::print(0, "angle delta: %g", angleDifference);

        if (front) {
            double measurement = getDistance(distanceSensor::Front) * std::cos(angleDifference);
            pros::lcd::print(2, "front: %g", measurement);
            switch (dir) {
                case direction::North:
                    pose.y = 144 - measurement;
                    break;
                case direction::East:
                    pose.x = 144 - measurement;
                    break;
                case direction::South:
                    pose.y = measurement;
                    break;
                case direction::West:
                    pose.x = measurement;
                    break;
            }
        } else if (back) {
            double measurement = getDistance(distanceSensor::Back) * std::cos(angleDifference);
            switch (dir) {
                case direction::North:
                    pose.y = measurement;
                    break;
                case direction::East:
                    pose.x = measurement;
                    break;
                case direction::South:
                    pose.y = 144 - measurement;
                    break;
                case direction::West:
                    pose.x = 144 - measurement;
                    break;
            }
        }
        if (right) {
            double measurement = getDistance(distanceSensor::Right) * std::cos(angleDifference);
            pros::lcd::print(3, "right: %g", measurement);
            switch (dir) {
                case direction::North:
                    pose.x = 144 - measurement;
                    break;
                case direction::East:
                    pose.y = measurement;
                    break;
                case direction::South:
                    pose.x = measurement;
                    break;
                case direction::West:
                    pose.y = 144 - measurement;
                    break;
            }
        } else if (left) {
            double measurement = getDistance(distanceSensor::Left) * std::cos(angleDifference);
            switch (dir) {
                case direction::North:
                    pose.x = measurement;
                    break;
                case direction::East:
                    pose.y = 144 - measurement;
                    break;
                case direction::South:
                    pose.x = 144 - measurement;
                    break;
                case direction::West:
                    pose.y = measurement;
                    break;
            }
        }
        pros::lcd::print(4, "Angle: %g, X: %f, Y: %f", pose.theta, pose.x, pose.y);
        return pose;
    }

    double getDistance(distanceSensor sensor) { 
        pros::Distance* activeSensor = nullptr;
        double offset;

        switch (sensor) {
            case distanceSensor::Front:
                activeSensor = &devices::distanceFront;
                offset = 7.0;
                break;
            case distanceSensor::Right:
                activeSensor = &devices::distanceRight;
                offset = 6.5;
                break;
            case distanceSensor::Back:
                activeSensor = &devices::distanceBack;
                offset = 7.5;
                break;
            case distanceSensor::Left:
                activeSensor = &devices::distanceLeft;
                offset = 6.5;
                break;
        }

        double sum{0.0};
        for (int i = 0; i < 50; ++i) {
            sum += activeSensor->get_distance();
        }

        return offset + sum / 50 * MM_TO_INCHES;
    }

    // ---------- Math ----------
    // ----- Quadratics -----
    
    // Get the roots of a quadratic
    std::pair<double, double> solveQuadratic(double a, double b, double c) {
        return std::pair{
            (-b + std::sqrt(b * b - 4 * a * c)) / (2 * a),
            (-b - std::sqrt(b * b - 4 * a * c)) / (2 * a)
        };
    } // does this work with the pointers?
    // Check if the roots of a quadratic are real numbers
    bool quadraticError(double a, double b, double c) {
        return (b * b - 4 * a * c < 0);
    }

    // ----- Clamping / Range setting -----
    
    // Bound an angle to [-pi, pi)
    double angleRangePNPi(double angle) {
        return angle - std::floor((angle + M_PI) / (TWO_PI)) * (TWO_PI);
    }
    // Bound an angle to [0, 2pi)
    double angleRangeZeroToTwoPi(double angle) {
        return angle - std::floor(angle / (TWO_PI)) * (TWO_PI);
    }
    // Bound an angle to [-180, 180)
    double angleRangePN180(double angle) {
        return angle - std::floor((angle + 180.0) / (360.0)) * (360.0);
    }
    // Bound an angle to [0, 360)
    double angleRangeZeroTo360(double angle) {
        return angle - std::floor(angle / (360)) * (360);
    }

    // ----- Vectors -----

    // Gives the distance between two Vectors
    double dist(Vector p1, Vector p2) {
        return std::sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
    }

    // Gives the angle from p1 to p2 (e.g. the angle from (0,0) to (2, sqrt(3)) is pi/6)
    double angleTo(Vector p1, Vector p2) {
        return std::atan2(
            p2.y - p1.y,
            p2.x - p1.x
        );
    }

    // Rotates a Vector around (0,0) by a specified angle in radians
    Vector rotate(Vector vec, double angle) {
        double cos = std::cos(angle);
        double sin = std::sin(angle);

        return Vector{vec.x * cos - vec.y * sin, vec.x * sin + vec.y * cos};
    }

    // ----- Intersections -----

    // Find the intersection points of a circle and a line
    std::pair<Vector, Vector> boundedCircleLineIntersect(Vector p1, Vector p2, Vector pc, double r, std::pair<bool, bool>& errorFlags) {
        if (p1.x == p2.x) {
            std::pair yInts{
              pc.y + sqrt(r*r - (p1.x-pc.x)*(p1.x-pc.x)),
              pc.y - sqrt(r*r - (p1.x-pc.x)*(p1.x-pc.x))
            };
            std::pair result{
                Vector{p1.x, yInts.first },
                Vector{p1.x, yInts.second },
            };
            double greaterY = std::max(p1.y, p2.y);
            double lesserY = std::min(p1.y, p2.y);
            if (yInts.first < lesserY || yInts.first > greaterY) { errorFlags.first = true; }
            if (yInts.second < lesserY || yInts.second > greaterY) { errorFlags.second = true; }
            return result;
        } else {
            double slope = (p2.y - p1.y) / (p2.x - p1.x);
            double a = slope * slope + 1;
            double b = -(
                2 * slope * slope * p1.x +
                2 * slope * pc.y -
                2 * slope * p1.y +
                2 * pc.x
            );
            double c =
                slope * slope * p1.x * p1.x +
                p1.y * p1.y +
                pc.y * pc.y -
                2 * slope * p1.y * p1.x +
                2 * slope * pc.y * p1.x -
                2 * p1.y * pc.y +
                pc.x * pc.x -
                r * r;
            std::pair xInts = solveQuadratic(a, b, c);
            if (quadraticError(a, b, c)) {
                errorFlags.first = true;
                errorFlags.second = true;
                return std::pair{Vector(), Vector()}; // return anything
            }
            double greaterX = std::max(p1.x, p2.x);
            double lesserX = std::min(p1.x, p2.x);
            std::pair yInts{
                slope * (xInts.first - p1.x) + p1.y,
                slope * (xInts.second - p1.x) + p1.y
            };
            if (xInts.first < lesserX || xInts.first > greaterX) { errorFlags.first = true; }
            if (xInts.second < lesserX || xInts.second > greaterX) { errorFlags.second = true; }
            std::pair result{
                Vector(xInts.first, yInts.first), // will this work? (destroyed after function exit??)
                Vector(xInts.second, yInts.second)
            };
            return result;
        }
    }

    // TODO: Test and Optimize
    // Find the distance from a position within a square to the edge on a ray defined by an angle
    double raySquareIntersectDistance(double x, double y, double angle, double squareSize) {
        // Get coefficients for a parametric line
        double dx = std::cos(angle);
        double dy = std::sin(angle);

        if (dx == 0) {
            // TODO: Handle
            return 0;
        } else if (dy == 0) {
            // TODO: Handle
            return 0;
        }

        double tMin = std::numeric_limits<double>::max();
        double t;

        // Left edge (x=0)
        t = -x / dx;
        if (t >= 0 && t < tMin) tMin = t;

        // Right edge (x=width)
        t = (squareSize - x) / dx;
        if (t >= 0 && t < tMin) tMin = t;

        // Bottom edge (y=0)
        t = -y / dy;
        if (t >= 0 && t < tMin) tMin = t;

        // Top edge (y=height)
        t = (squareSize - y) / dy;
        if (t >= 0 && t < tMin) tMin = t;

        // tMin is the distance, since dx^2 + dy^2 = cos^2 + sin^2 = 1
        return tMin;
    }
    // Find the distance from a position within a square to the edge on a ray defined by an angle
    double raySquareIntersectDistance(Vector startPos, double angle, double squareSize) {
        return raySquareIntersectDistance(startPos.x, startPos.y, angle, squareSize);
    }

    // TODO: Test and Optimize
    // Find the distance from a position within a square to the edge on a ray defined by an angle
    double rayWallIntersectDistance(double x, double y, double angle) {
        // Get coefficients for a parametric line
        double dx = std::cos(angle);
        double dy = std::sin(angle);

        if (dx == 0) {
            // TODO: Handle
            return 0;
        } else if (dy == 0) {
            // TODO: Handle
            return 0;
        }

        double tMin = std::numeric_limits<double>::max();
        double t;

        // Left edge (x=0)
        t = -x / dx;
        if (t >= 0 && t < tMin) tMin = t;

        // Right edge (x=width)
        t = (FIELD_SIZE - x) / dx;
        if (t >= 0 && t < tMin) tMin = t;

        // Bottom edge (y=0)
        t = -y / dy;
        if (t >= 0 && t < tMin) tMin = t;

        // Top edge (y=height)
        t = (FIELD_SIZE - y) / dy;
        if (t >= 0 && t < tMin) tMin = t;


        // tMin is the distance, since dx^2 + dy^2 = cos^2 + sin^2 = 1
        return tMin;
    }
    // Find the distance from a position within a square to the edge on a ray defined by an angle
    double rayWallIntersectDistance(Vector startPos, double angle) {
        return rayWallIntersectDistance(startPos.x, startPos.y, angle);
    }
    
    // ---------- Randomness + Probability ----------
    
    // Shared random number generator
    std::mt19937& getGenerator() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    }
    
    // Generates a random number from [0, 1) using a uniform distribution
    double getRandomZeroOne() {
        static std::uniform_real_distribution<> dis(0.0, 1.0);
        return dis(getGenerator());
    }
    
    // Generates a random number from [min, max) using a uniform distribution
    double getRandomDoubleInRange(double min, double max) {
        std::uniform_real_distribution<> dis(min, max);
        return dis(getGenerator());
    }
    
    // Generates a random number with a gaussian distribution and the specified mean/standard deviation
    double getRandomGaussian(double mean, double stddev) {
        std::normal_distribution<> dis{mean, stddev};
        return dis(getGenerator());
    }

    // Computes the value of the Gaussian (normal) distribution at x
    double gaussianWithMean(double x, double mean, double stddev) {
        double exponent = -((x - mean) * (x - mean)) / (2 * stddev * stddev);
        double denominator = stddev * std::sqrt(TWO_PI);
        return std::exp(exponent) / denominator;
    }

    // TODO: 2654e uses a cheaper version of this
    // Computes the value of the Gaussian (normal) distribution at x
    double gaussian(double x, double stddev) {
        double exponent = -(x * x) / (2 * stddev * stddev);
        double denominator = stddev * std::sqrt(TWO_PI);
        return std::exp(exponent) / denominator;
    }
    // ---------- Device Interfacing ----------
    
    // Get the average position of all the drive motors
    double getAverageMotorPos() {
        // std::vector<double> leftPositions = devices::leftDrive.get_position_all();
        // std::vector<double> rightPositions = devices::rightDrive.get_position_all();
        // double sum = 0;
        // for (double pos : leftPositions) {
        //     sum += pos;
        // }
        // for (double pos : rightPositions) {
        //     sum += pos;
        // }
        // return sum / (leftPositions.size() + rightPositions.size());

        // Instead, just brute forcing it for speed
        return (
            devices::leftDrive.get_position(0)
            + devices::leftDrive.get_position(1)
            + devices::leftDrive.get_position(2)
            + devices::rightDrive.get_position(0)
            + devices::rightDrive.get_position(1)
            + devices::rightDrive.get_position(2)
        ) / 6;
    }    
} // namespace utilities