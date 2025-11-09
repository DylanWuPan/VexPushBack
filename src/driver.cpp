#include "driver.h"
#include "globals.h"
#include "intake.h"

using namespace devices;
using namespace intakeController;

namespace driverControl {
	
	namespace driveCurve {
		int curve(int val) {
			int valSquared = val*val;
			int valCubed = valSquared*val;
			return DRIVE_CURVE[1] * (1 - 3*val + 3*valSquared - valCubed) +
				DRIVE_CURVE[2] * (3*val - 6*valSquared + 3*valCubed) +
				DRIVE_CURVE[3] * (3*valSquared - 3*valCubed) +
				DRIVE_CURVE[4] * valCubed;
		}

		int driveMap(int val) {
			if (val > -DEAD_ZONE && val < DEAD_ZONE) {
				return 0;
			}
			return MIN_OUTPUT + (SCALE_OUTPUT - MIN_OUTPUT) * ((val - DEAD_ZONE) / (SCALE_INPUT - DEAD_ZONE));
		}
	}

	bool matchLoaderDown = false;
	bool topAlignerDown = true;
	bool isAutoIntaking = true;

	// Called to control the robot driving during the driver control period
    void opcontrolDrive() {
        // int leftStickVal = controller.get_analog(ANALOG_LEFT_Y);      // Gets amount forward/backward from left joystick
        // int rightStickVal = controller.get_analog(ANALOG_RIGHT_Y);    // Gets the turn left/right from right joystick
		// leftDrive.move_voltage(driveCurve::driveMap(leftStickVal));   // Sets left motor voltage
		// rightDrive.move_voltage(driveCurve::driveMap(rightStickVal)); // Sets right motor voltage
		float LeftY = driveCurve::driveMap(controller.get_analog(ANALOG_LEFT_Y));
    	float RightX = driveCurve::driveMap(controller.get_analog(ANALOG_RIGHT_X));
   		chassis.arcade(LeftY, RightX);
    }

	// Called to control the pneumatics during the driver control period
    void opcontrolPneumatics() {
			if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
				topAligner.set_value(false);
				matchLoader.set_value(false);
				topAlignerDown = true;
				matchLoaderDown = false;
			}

			if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
				topAlignerDown = !topAlignerDown;
				matchLoaderDown = !matchLoaderDown;
				matchLoader.set_value(matchLoaderDown);
				topAligner.set_value(topAlignerDown);
			}
    }

	// Called to control the robot intake during the driver control period
    void opcontrolIntake() {
			if (isSkipping || isJamming) return;
			//INTAKE
			if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
				isAutoIntaking = !isAutoIntaking;
			}

			if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
				intake.move_velocity(INTAKE_VELOCITY);
				hopper.move_velocity(HOPPER_VELOCITY);
				topScore.move_velocity(-TOPSCORE_VELOCITY);
			} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
				intake.move_velocity(-INTAKE_VELOCITY/3);
				hopper.move_velocity(-HOPPER_VELOCITY);
			} else {
				if (isAutoIntaking) {
					intake.move_velocity(INTAKE_VELOCITY);
					hopper.move_velocity(HOPPER_VELOCITY);
					topScore.move_velocity(-TOPSCORE_VELOCITY);
				} else {
					intake.move_velocity(0);
					hopper.move_velocity(0);
					topScore.move_velocity(0);
				}
			}

			//MID SCORE
			if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
				topScore.move_velocity(-TOPSCORE_VELOCITY/3);
				intake.move_velocity(INTAKE_VELOCITY);
				hopper.move_velocity(-HOPPER_VELOCITY);
			} 

			//TOP SCORE
			if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
				topScore.move_velocity(TOPSCORE_VELOCITY/2);
				intake.move_velocity(INTAKE_VELOCITY);
				hopper.move_velocity(-HOPPER_VELOCITY);
			}
    }

} // namespace driverControl