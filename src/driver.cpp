#include "driver.h"
#include "globals.h"
#include "intake.h"

using namespace devices;
using namespace intakeController;

namespace driverControl {
	
	namespace driveCurve {
		const double movementCoeff = ((SCALE_OUTPUT-MIN_OUTPUT)/SCALE_INPUT) *
			(SCALE_INPUT / ((SCALE_INPUT - DEAD_ZONE) * pow(BASE, SCALE_INPUT-DEAD_ZONE)));

		int driveMap(int val) {
			if (val > -DEAD_ZONE && val < DEAD_ZONE) {
				return 0;
			}
			double inputMag = abs(val) - DEAD_ZONE;
			return ((movementCoeff * inputMag * pow(BASE, inputMag)) + MIN_OUTPUT) * (val < 0? -1 : 1);
		}
	}

	bool matchLoaderDown = false;
	bool topAlignerDown = false;

	// Called to control the robot driving during the driver control period
    void opcontrolDrive() {
        // int leftStickVal = controller.get_analog(ANALOG_LEFT_Y);      // Gets amount forward/backward from left joystick
        // int rightStickVal = controller.get_analog(ANALOG_RIGHT_Y);    // Gets the turn left/right from right joystick
		// leftDrive.move_voltage(driveCurve::driveMap(leftStickVal));   // Sets left motor voltage
		// rightDrive.move_voltage(driveCurve::driveMap(rightStickVal)); // Sets right motor voltage
		float LeftY = DRIVERS_SPEED * controller.get_analog(ANALOG_LEFT_Y);
    	float RightY = DRIVERS_SPEED * controller.get_analog(ANALOG_RIGHT_Y);
   		chassis.arcade(LeftY, RightY);

    }

	// Called to control the pneumatics during the driver control period
    void opcontrolPneumatics() {
		// MATCH LOADER
		if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
			matchLoaderDown = !matchLoaderDown;
			matchLoader.set_value(matchLoaderDown);
		}

        // TOP ALIGNER
		if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
			topAlignerDown = !topAlignerDown;
			topAligner.set_value(topAlignerDown);
		}
    }

	// Called to control the robot intake during the driver control period
    void opcontrolIntake() {
		if (isSkipping) return;
		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) { // INTAKE
			intake.move_velocity(INTAKE_VELOCITY);
			hopper.move_velocity(HOPPER_VELOCITY);
		} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) { // OUTTAKE
			intake.move_velocity(-INTAKE_VELOCITY);
			hopper.move_velocity(-HOPPER_VELOCITY);
		} else {
			intake.move_velocity(0);
			hopper.move_velocity(0);
		}

		//MID SCORE
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			topScore.move_velocity(TOPSCORE_VELOCITY/3);
			intake.move_velocity(INTAKE_VELOCITY);
			hopper.move_velocity(-HOPPER_VELOCITY);
		} else {
			topScore.move_velocity(0);
		}

		//TOP SCORE
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			topScore.move_velocity(-TOPSCORE_VELOCITY/1.5);
			intake.move_velocity(INTAKE_VELOCITY);
			hopper.move_velocity(-HOPPER_VELOCITY);
		}
    }

} // namespace driverControl