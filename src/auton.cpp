#include "auton.h"
#include "intake.h"
#include "main.h"
#include "globals.h"
using namespace devices;

namespace auton {
	void runIntake() {
		intake.move_velocity(intakeController::INTAKE_VELOCITY);
		hopper.move_velocity(intakeController::HOPPER_VELOCITY);
		topScore.move_velocity(-intakeController::TOPSCORE_VELOCITY);
	}

	void stopIntake(){
		intake.move_velocity(0);
		hopper.move_velocity(0);
		topScore.move_velocity(0);
	}

	void runIntakeNoHopper() {
		intake.move_velocity(intakeController::INTAKE_VELOCITY);
		hopper.move_velocity(intakeController::HOPPER_VELOCITY/10);
		topScore.move_velocity(intakeController::TOPSCORE_VELOCITY/20);
	}

	void outtake(){
		intake.move_velocity(-intakeController::INTAKE_VELOCITY);
		hopper.move_velocity(-intakeController::HOPPER_VELOCITY);
		topScore.move_velocity(-intakeController::TOPSCORE_VELOCITY);
	}

	void runTopScore(){
		topScore.move_velocity(intakeController::TOPSCORE_VELOCITY);
		hopper.move_velocity(-intakeController::HOPPER_VELOCITY);
		intake.move_velocity(intakeController::INTAKE_VELOCITY);
	}

	void runMiddleScore(){
		topScore.move_velocity(-intakeController::TOPSCORE_VELOCITY/2);
		hopper.move_velocity(-intakeController::HOPPER_VELOCITY);
		intake.move_velocity(intakeController::INTAKE_VELOCITY/2);
	}

	// Auton Functions
	void autonSkills() {
		// intakeController::periodicTask.end();
	}

	void autonRedRight() {
		intakeController::isRedAlliance = true;

		// chassis.setPose(88.5, 22, 90);
		
		// // Match load
		// chassis.moveToPoint(120, 22, 4000, {.maxSpeed = 80});
		// pros::delay(1000);
		// chassis.turnToHeading(180, 500, {.maxSpeed = 80});
		// matchLoader.set_value(true);
		// runIntake();
		// chassis.moveToPose(121, 11, 180, 2000, {.maxSpeed = 50});
		// pros::delay(1700);

		// // // Long goal
		// chassis.moveToPoint(122, 24, 2000, {.forwards = false});
		// chassis.moveToPose(122, 40.5, 0, 3000, {.maxSpeed = 80});
		// pros::delay(500);
		// topAligner.set_value(true);
		// pros::delay(300);
		// matchLoader.set_value(false);
		// pros::delay(100);
		// runTopScore();
		// pros::delay(2000);

		// // Three balls
		// chassis.moveToPoint(123, 24, 2000, {.forwards = false});
		// chassis.turnToHeading(-47, 500, {.maxSpeed = 80});
		// runIntake();
		// chassis.moveToPoint(102, 42.5, 3000, {.maxSpeed = 80});
		// chassis.moveToPoint(86.5, 62.5, 3000, {.maxSpeed = 30});
		// pros::delay(2000);
		// outtake();
		// pros::delay(2000);
		// chassis.moveToPoint(102, 42.5, 3000, {.forwards = false, .maxSpeed = 80});

		chassis.setPose(55.5, 22, 270);

		// Match load
		chassis.moveToPoint(23, 22, 4000, {.maxSpeed = 80});
		pros::delay(1000);
		chassis.turnToHeading(180, 500, {.maxSpeed = 80});
		matchLoader.set_value(true);
		runIntake();
		chassis.moveToPose(22, 10.75, 180, 2000, {.maxSpeed = 30});
		pros::delay(1500);

		// Long goal
		chassis.moveToPoint(22, 24, 2000, {.forwards = false});
		chassis.moveToPose(23, 40.5, 360, 3000, {.maxSpeed = 80});
		pros::delay(500);
		topAligner.set_value(true);
		pros::delay(300);
		matchLoader.set_value(false);
		pros::delay(100);
		runTopScore();
		pros::delay(2000);

		// MidGoal
		chassis.moveToPoint(21, 24, 2000, {.forwards = false});
		chassis.turnToHeading(407, 500, {.maxSpeed = 80});
		topAligner.set_value(false);
		runIntake();
		chassis.moveToPoint(42, 42.5, 3000, {.maxSpeed = 80});
		chassis.moveToPose(57.5, 57, 46, 3000, {.maxSpeed = 30});
		pros::delay(2000);
		runMiddleScore();
		pros::delay(2000);
		runIntake();

		chassis.moveToPoint(48, 48.5, 3000, {.forwards = false, .maxSpeed = 80});
		chassis.moveToPose(81, 47, 90, 4000, {.maxSpeed = 80});
		chassis.moveToPoint(96, 47, 3000, {.maxSpeed = 30});
		pros::delay(10000);
		
	}

	void autonRedLeft() {
		intakeController::isRedAlliance = true;
	}

	void autonBlueRight() {
		intakeController::isRedAlliance = false;
	}

	void autonBlueLeft() {
		intakeController::isRedAlliance = false;
	}
} // namespace auton


// FOR SELECTING AUTON MODE BEFORE MATCH
namespace auton::autonSelect {
	extern autonMode mode(autonMode::SKILLS);

	void printAutonMode(int line) {
		switch (mode) {
			case autonMode::BLUE_RIGHT:
				pros::lcd::set_text(line, "Auton mode: Blue Right");
				break;
			case autonMode::BLUE_LEFT:
				pros::lcd::set_text(line, "Auton mode: Blue Left");
				break; 
			case autonMode::RED_RIGHT:
				pros::lcd::set_text(line, "Auton mode: Red Right");
				break;
			case autonMode::RED_LEFT:
				pros::lcd::set_text(line, "Auton mode: Red Left");
				break;
			case autonMode::SKILLS:
				pros::lcd::set_text(line, "Auton mode: Skills");
				break;
		}
	}
	void incrementAutonMode() {
		mode = static_cast<autonMode>((static_cast<int>(mode) + 1) % NUM_AUTONS);
	}
	void decrementAutonMode() {
		mode = static_cast<autonMode>((static_cast<int>(mode) - 1) % NUM_AUTONS);
	}
} // namespace autonSelect