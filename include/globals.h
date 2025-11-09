#pragma once
#include "main.h"

namespace devices {
	extern pros::Imu inertial; // Inertial Sensor
	extern pros::Rotation latTracker;
	extern pros::Rotation vertTracker;

	extern pros::Distance distanceRight;
	extern pros::Distance distanceLeft;
	extern pros::Distance distanceFront;
	extern pros::Distance distanceBack;

	extern pros::Controller controller;

	// TODO: Check port order
	extern pros::MotorGroup leftDrive;
	extern pros::MotorGroup rightDrive;

	extern pros::Motor intake;
	extern pros::Motor hopper;
	extern pros::Motor topScore;

	extern pros::adi::DigitalOut matchLoader;
	extern pros::adi::DigitalOut topAligner;

	extern pros::Optical colorSensor;

	// -------------------- LEMLIB --------------------
	extern lemlib::Drivetrain drivetrain;
	extern lemlib::TrackingWheel horizontalTrackingWheel;
	extern lemlib::TrackingWheel verticalTrackingWheel;

	extern lemlib::OdomSensors sensors;

	extern lemlib::ControllerSettings lateralController;

	extern lemlib::ControllerSettings angularController;

	extern lemlib::Chassis chassis;

} // namespace devices
