#pragma once
#include <cmath>

namespace driverControl {

	namespace driveCurve {
		constexpr int DEAD_ZONE = 2;
		constexpr double BASE = 1; // 0.995;
		constexpr int MIN_OUTPUT = 1500;
		constexpr int SCALE_INPUT = 127;
		constexpr int SCALE_OUTPUT = 12000;

		extern const double movementCoeff;

		int driveMap(int val);
	}

	// constexpr float DRIVERS_SPEED = 1;

  	extern bool matchLoaderDown;

	// Called to control the robot driving during the driver control period
    void opcontrolDrive();

	// Called to control the goal clamp during the driver control period
    void opcontrolPneumatics();

	// Called to control the robot intake during the driver control period
    void opcontrolIntake();

} // namespace driverControl