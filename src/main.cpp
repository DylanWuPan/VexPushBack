#include "main.h"
#include "globals.h"
#include "driver.h"
#include "screen.h"
#include "auton.h"
#include "intake.h"

using namespace devices;

<<<<<<< HEAD
bool IS_SKIPPING = false;
bool ROGUE_BALL = false;

Alliance ALLIANCE = RED;
// int DEFAULT_HUE = 340;
int BLUE_HUE = 230;
int RED_HUE = 350;
  
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
void colorSort() {
  switch(ALLIANCE) {
    case RED: ROGUE_BALL = abs(colorsensor.get_hue() - BLUE_HUE) < 20; break;
    case BLUE: ROGUE_BALL = abs(colorsensor.get_hue() - RED_HUE) < 20; break;
  }
  if(ROGUE_BALL && intake.get_voltage() > 0){
    discardBall();
  }
}

void discardBall() {
  if(!IS_SKIPPING){
    IS_SKIPPING = true;
    hopper.move_velocity(-HOPPER_VELOCITY);
    // topscore.move_velocity(TOPSCORE_VELOCITY);
    pros::delay(70);
    hopper.move_velocity(HOPPER_VELOCITY);

    ROGUE_BALL = false;
    IS_SKIPPING = false;
  }
}

// Main Functions --------------------------------------------------------------
void initialize() {
  pros::lcd::initialize();
  chassis.calibrate();
  chassis.setPose(0, 0, 0);
  colorsensor.set_led_pwm(100);

  // Brain Screen Readouts
  pros::Task screen_task([] {
    while (true) {
      lemlib::Pose robotPos = chassis.getPose();
      pros::lcd::print(0, "X: %f", robotPos.x);
      pros::lcd::print(1, "Y: %f", robotPos.y);
      pros::lcd::print(2, "COLOR SENSOR: %f", colorsensor.get_hue());
      pros::lcd::print(3, "ROGUE BALL: %s", ROGUE_BALL ? "TRUE" : "FALSE");
      pros::delay(20);
    }
  });

  // Color Sort Task
  pros::Task ColorSortTask([] {
    while (true) {
      colorSort();
      pros::delay(5);
    }
  });
=======
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	inertial.reset(true);
	
	chassis.calibrate();
	chassis.setPose(0, 0, 0);

	// pros::lcd::initialize();
	
	screenController::start();
	intakeController::start();
>>>>>>> 5bf8ef0 (reorganized tasks)
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
<<<<<<< HEAD
  // sampleAuto1()
  // sampleAuto2();
=======
	switch (auton::autonSelect::getAutonMode()) {
		case auton::autonSelect::autonMode::BLUE_LEFT:
			auton::autonBlueLeft();
			break;
		case auton::autonSelect::autonMode::BLUE_RIGHT:
			auton::autonBlueRight();
			break; 
		case auton::autonSelect::autonMode::RED_LEFT:
			auton::autonRedLeft();
			break;
		case auton::autonSelect::autonMode::RED_RIGHT:
			auton::autonRedRight();
			break;
		case auton::autonSelect::autonMode::SKILLS:
			auton::autonSkills();
			break;
	}
>>>>>>> 5bf8ef0 (reorganized tasks)
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	while (true) {
		if (controller.get_digital_new_press(DIGITAL_Y)) {
			screenController::onCenterButton();
		}

<<<<<<< HEAD
  bool MATCHLOADER_STATE = false;
  bool TOPALIGNER_STATE = false;

  while (true) {
    // DRIVE ----------------------------------------------------------------
    float LeftY = DRIVERS_SPEED * controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
    float RightY = DRIVERS_SPEED * controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);
    chassis.arcade(LeftY, RightY);

    if(!IS_SKIPPING) {
    
      //INTAKE
      if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        intake.move_velocity(INTAKE_VELOCITY);
        hopper.move_velocity(HOPPER_VELOCITY);
        hopper2.move_velocity(HOPPER_VELOCITY);
        topscore.move_velocity(TOPSCORE_VELOCITY);
      } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        intake.move_velocity(-INTAKE_VELOCITY);
        hopper.move_velocity(-HOPPER_VELOCITY);
        hopper2.move_velocity(-HOPPER_VELOCITY);
      } else {
        intake.move_velocity(0);
        hopper.move_velocity(0);
        hopper2.move_velocity(0);
        topscore.move_velocity(0);
      }

      //MID SCORE
      if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        topscore.move_velocity(TOPSCORE_VELOCITY);
        intake.move_velocity(INTAKE_VELOCITY);
        hopper.move_velocity(-HOPPER_VELOCITY);
        hopper2.move_velocity(-HOPPER_VELOCITY);
      }

      //TOP SCORE
      if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        topscore.move_velocity(-TOPSCORE_VELOCITY/2);
        intake.move_velocity(INTAKE_VELOCITY);
        hopper.move_velocity(-HOPPER_VELOCITY);
        hopper2.move_velocity(-HOPPER_VELOCITY);
      }

      //MATCH LOADER
      if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
        MATCHLOADER_STATE = !MATCHLOADER_STATE;
        matchloader.set_value(MATCHLOADER_STATE);
      }

      //TOP ALIGNER
      if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
        TOPALIGNER_STATE = !TOPALIGNER_STATE;
        topaligner.set_value(TOPALIGNER_STATE);
      }
    }


    pros::delay(20);
  }
=======
		driverControl::opcontrolPneumatics();
		driverControl::opcontrolIntake();
		driverControl::opcontrolDrive();
		pros::delay(20);
	}
>>>>>>> 5bf8ef0 (reorganized tasks)
}