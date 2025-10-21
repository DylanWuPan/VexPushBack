<<<<<<< HEAD
#include "main.h"

using namespace pros;
using namespace pros::v5;
#ifndef GLOBALS
#define GLOBALS

extern pros::MotorGroup left_drivetrain;
extern pros::MotorGroup right_drivetrain;
extern pros::Rotation vertical_tracking;
extern pros::Rotation horizontal_tracking;
extern pros::Controller controller;
extern pros::IMU inertial; 
extern pros::Optical colorsensor;
extern lemlib::Chassis chassis;
extern pros::Motor intake;
extern pros::Motor hopper;
extern pros::Motor hopper2;
extern pros::Motor topscore;
extern pros::ADIDigitalOut matchloader;
extern pros::ADIDigitalOut topaligner;

#endif
=======
#pragma once
#include "main.h"

namespace devices {
	extern pros::Imu inertial; // Inertial Sensor
	extern pros::Rotation latTracker;
	extern pros::Rotation vertTracker;

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

	// TODO: Ports
	// pros::Distance frontDistance;
	// pros::Distance rightDistance;
	// pros::Distance leftDistance;
	// pros::Distance backDistance;

	// -------------------- LEMLIB --------------------
	extern lemlib::Drivetrain drivetrain;
	extern lemlib::TrackingWheel horizontalTrackingWheel;
	extern lemlib::TrackingWheel verticalTrackingWheel;

	extern lemlib::OdomSensors sensors;

	extern lemlib::ControllerSettings lateralController;

	extern lemlib::ControllerSettings angularController;

	extern lemlib::Chassis chassis;

} // namespace devices
>>>>>>> 5bf8ef0 (reorganized tasks)
