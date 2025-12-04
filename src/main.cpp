#include "main.h"
#include "auton.h"
#include "driver.h"
#include "globals.h"
#include "intake.h"
#include "localization.h"
#include "screen.h"

using namespace devices;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    chassis.calibrate();

    screenController::start();
    intakeController::start();
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
    auton::autonLeft7Long();
    // auton::autonTest();
    // switch (auton::autonSelect::getAutonMode()) {
    // 	case auton::autonSelect::autonMode::LONG_MIDDLE_LEFT:
    // 		auton::autonLongMiddleLeft();
    // 		break;
    // 	case auton::autonSelect::autonMode::LONG_MIDDLE_RIGHT:
    // 		auton::autonLongMiddleRight();
    // 		break;
    // 	case auton::autonSelect::autonMode::LEFT_7_LONG:
    // 		auton::autonLeft7Long();
    // 		break;
    // 	case auton::autonSelect::autonMode::RIGHT_7_LONG:
    // 		auton::autonRight7Long();
    // 		break;
    // 	case auton::autonSelect::autonMode::SKILLS:
    // 		auton::autonSkills();
    // 		break;
    // }
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
	// localization::start(55.75, 22.75, 0); // like SAWP Auton (for testing)
    intakeController::isColorSorting = false;

    while (true) {
        if (controller.get_digital_new_press(DIGITAL_Y)) {
            screenController::onCenterButton(); // Prints
        }

        driverControl::opcontrolPneumatics();
        driverControl::opcontrolIntake();
        driverControl::opcontrolDrive();
        pros::delay(20);
    }
}