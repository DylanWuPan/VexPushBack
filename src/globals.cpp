<<<<<<< HEAD
#include "main.h"

pros::MotorGroup left_drivetrain({-1, -2, -3}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::MotorGroup right_drivetrain({ 8, 9, 10}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

pros::Rotation vertical_tracking(20);
pros::Rotation horizontal_tracking(19);
pros::Imu inertial(21);
pros::Optical colorsensor(18);

pros::Motor intake(-11, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor hopper(-21, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
pros::Motor topscore(13, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
pros::Motor hopper2(-20, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);

pros::Controller controller(CONTROLLER_MASTER);

pros::ADIDigitalOut matchloader('H', false);
pros::ADIDigitalOut topaligner('G', false);
=======
#include "globals.h"
#include "main.h"

namespace devices {
	pros::Imu inertial{20}; // Inertial Sensor
	pros::Rotation latTracker{13};
	pros::Rotation vertTracker{-17};

	pros::Controller controller{pros::E_CONTROLLER_MASTER};

	// TODO: Check port order
	pros::MotorGroup leftDrive({-1, -2, -3}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees); // Left Motors, declared back-middle-front
	pros::MotorGroup rightDrive({8, 9, 10}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);  // Right Motors, declared back-middle-front

	pros::Motor intake(-11, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
	pros::Motor hopper(-21, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
	pros::Motor topScore(13, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);

	pros::adi::DigitalOut matchLoader{'H', false};
	pros::adi::DigitalOut topAligner('G', false);

	pros::Optical colorSensor(18);

	// TODO: Ports
	// pros::Distance frontDistance{0};
	// pros::Distance rightDistance{0};
	// pros::Distance leftDistance{0};
	// pros::Distance backDistance{0};

	// -------------------- LEMLIB --------------------
	lemlib::Drivetrain drivetrain(
		&leftDrive, // left motor group
		&rightDrive, // right motor group
		10.625, // track width
		lemlib::Omniwheel::NEW_325, //wheels
		450, //drivetrain rpm
		2 // horizontal drift
	);
	lemlib::TrackingWheel horizontalTrackingWheel(&latTracker, lemlib::Omniwheel::NEW_2, -2.25);
	lemlib::TrackingWheel verticalTrackingWheel(&vertTracker, lemlib::Omniwheel::NEW_2, 0.25);

	lemlib::OdomSensors sensors(
		&verticalTrackingWheel, // vertical tracking wheel 1, set to null
		nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
		&horizontalTrackingWheel, // horizontal tracking wheel 1
		nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
		&inertial // inertial sensor
	);

	lemlib::ControllerSettings lateralController(
		10, // proportional gain (kP)
		0, // integral gain (kI)
		35, // derivative gain (kD)
		3, // anti windup
		1, // small error range, in inches
		100, // small error range timeout, in milliseconds
		3, // large error range, in inches
		500, // large error range timeout, in milliseconds
		20 // maximum acceleration (slew)
	);

	lemlib::ControllerSettings angularController(
		4, // proportional gain (kP)
		0, // integral gain (kI)
		25, // derivative gain (kD)
		3, // anti windup
		1, // small error range, in degrees
		100, // small error range timeout, in milliseconds
		3, // large error range, in degrees
		500, // large error range timeout, in milliseconds
		0 // maximum acceleration (slew)
	);

	lemlib::Chassis chassis(
		drivetrain, // drivetrain settings
		lateralController, // lateral PID settings
		angularController, // angular PID settings
		sensors // odometry sensors
	);

} // namespace devices
>>>>>>> 5bf8ef0 (reorganized tasks)
