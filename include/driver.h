#pragma once
#include <cmath>

namespace driverControl {

	namespace driveCurve {
		constexpr int DEAD_ZONE = 2;
		constexpr double DRIVE_CURVE[] = {0, 0.425, 0.575, 1};
		constexpr int MIN_OUTPUT = 2;
		constexpr int SCALE_INPUT = 127;
		constexpr double SCALE_OUTPUT_LINEAR = 127.0; // max 127
		constexpr double SCALE_OUTPUT_TURN = 64.0; // max 127

		extern const double movementCoeff;

		double curve(double val);
		double driveMap(double val, double scaleOutput);
	}

	constexpr float DRIVERS_SPEED = 1;

  	extern bool matchLoaderDown;

	// Called to control the robot driving during the driver control period
    void opcontrolDrive();

	// Called to control the goal clamp during the driver control period
    void opcontrolPneumatics();

	// Called to control the robot intake during the driver control period
    void opcontrolIntake();

} // namespace driverControl