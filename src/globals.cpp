#include "globals.h"
#include "main.h"

namespace devices {
	pros::Imu inertial{21}; // Inertial Sensor
	pros::Rotation latTracker{4};
	pros::Rotation vertTracker{-19};

	pros::Distance distanceRight{16};
	pros::Distance distanceLeft{12};
	pros::Distance distanceFront{7};
	pros::Distance distanceBack{18};


	pros::Controller controller{pros::E_CONTROLLER_MASTER};

	// TODO: Check port order
	pros::MotorGroup leftDrive({-3, -2, 1}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees); // Left Motors, declared back-middle-front
	pros::MotorGroup rightDrive({10, 9, 8}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);  // Right Motors, declared back-middle-front

	pros::Motor intake(-11, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
	pros::Motor hopper(-20, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
	pros::Motor topScore(-13, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);

	pros::adi::DigitalOut matchLoader{'H', false};
	pros::adi::DigitalOut topAligner('G', false);

	pros::Optical colorSensor(17);

	// TODO: Ports
	// pros::Distance frontDistance{0};
	// pros::Distance rightDistance{0};
	// pros::Distance leftDistance{0};
	// pros::Distance backDistance{0};

	// -------------------- LEMLIB --------------------
	lemlib::Drivetrain drivetrain(
		&leftDrive, // left motor group
		&rightDrive, // right motor group
		12, // track width
		lemlib::Omniwheel::NEW_325, //wheels
		450, //drivetrain rpm
		2 // horizontal drift
	);
	lemlib::TrackingWheel horizontalTrackingWheel(&latTracker, lemlib::Omniwheel::NEW_2, -1.75);
	lemlib::TrackingWheel verticalTrackingWheel(&vertTracker, lemlib::Omniwheel::NEW_2, -0.125);

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
