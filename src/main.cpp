#include "main.h"
#include "globals.h"
#include "auton.h"

// Constants -------------------------------------------------------------------
float DRIVERS_SPEED = 1;
  
//LEMLIB ----------------------------------------------------------------
lemlib::Drivetrain drivetrain(&left_drivetrain, // left motor group
                              &right_drivetrain, // right motor group
                              10.625, // track width
                              lemlib::Omniwheel::NEW_325, //wheels
                              450, //drivetrain rpm
                              2 // horizontal drift
);
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_tracking, lemlib::Omniwheel::NEW_2, -2.25);
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_tracking, lemlib::Omniwheel::NEW_2, 0.25);

lemlib::OdomSensors sensors(&vertical_tracking_wheel, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            &horizontal_tracking_wheel, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &inertial // inertial sensor
);

lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              35, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP)
//                                               0, // integral gain (kI)
//                                               35, // derivative gain (kD)
//                                               0, // anti windup
//                                               0, // small error range, in inches
//                                               0, // small error range timeout, in milliseconds
//                                               0, // large error range, in inches
//                                               0, // large error range timeout, in milliseconds
//                                               0 // maximum acceleration (slew)
// );

lemlib::ControllerSettings angular_controller(4, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              25, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// lemlib::ControllerSettings angular_controller(2, // proportional gain (kP)
//                                               0, // integral gain (kI)
//                                               10, // derivative gain (kD)
//                                               0, // anti windup
//                                               0, // small error range, in inches
//                                               0, // small error range timeout, in milliseconds
//                                               0, // large error range, in inches
//                                               0, // large error range timeout, in milliseconds
//                                               0 // maximum acceleration (slew)
// );

lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);


// Helper Functions ------------------------------------------------------------

// Main Functions --------------------------------------------------------------
void initialize() {
  pros::lcd::initialize();
  chassis.calibrate();
  chassis.setPose(0, 0, 0);

  // Brain Screen Readouts
  pros::Task screen_task([] {
    while (true) {
      lemlib::Pose robotPos = chassis.getPose();
      pros::lcd::print(0, "X: %f", robotPos.x);
      pros::lcd::print(1, "Y: %f", robotPos.y);
      pros::delay(20);
    }
  });
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
  // sampleAuto1()
  sampleAuto2();
}

void opcontrol() {
  while (true) {
    // DRIVE ----------------------------------------------------------------
    float LeftY = DRIVERS_SPEED * controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
    float RightY = DRIVERS_SPEED * controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
    chassis.tank(LeftY, RightY);

    //INTAKE
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
      intake.move_velocity(200);
      hopper.move_velocity(200);
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
      intake.move_velocity(-200);
      hopper.move_velocity(-200);
    } else {
      intake.move_velocity(0);
      hopper.move_velocity(0);
    }

    //TOP SCORE
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
      topscore.move_velocity(200);
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
      topscore.move_velocity(-200);
    } else {
      topscore.move_velocity(0);
    }

    pros::delay(20);
  }
}