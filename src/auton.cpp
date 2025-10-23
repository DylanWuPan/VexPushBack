#include "auton.h"
#include "intake.h"
#include "main.h"
#include "globals.h"
using namespace devices;

namespace auton {
	void runIntake() {
		intake.move_velocity(intakeController::INTAKE_VELOCITY);
		hopper.move_velocity(intakeController::HOPPER_VELOCITY);
		topScore.move_velocity(intakeController::TOPSCORE_VELOCITY/2);
	}

	void stopIntake(){
		intake.move_velocity(0);
		hopper.move_velocity(0);
		topScore.move_velocity(0);
	}

	void runIntakeNoHopper() {
		intake.move_velocity(intakeController::INTAKE_VELOCITY);
		hopper.move_velocity(0);
		topScore.move_velocity(intakeController::TOPSCORE_VELOCITY/10);
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

	// Auton Functions
	void autonSkills() {
		// intakeController::periodicTask.end();
	}

	void autonRedRight() {
		intakeController::isRedAlliance = true;

		chassis.setPose(88.5, 22, 90);

		chassis.moveToPoint(120, 22, 4000, {.maxSpeed = 80});
		pros::delay(1000);
		chassis.turnToHeading(180, 1000, {.maxSpeed = 80});
		pros::delay(500);
		matchLoader.set_value(true);
		runIntakeNoHopper();
		chassis.moveToPoint(121, 11.5, 1400, {.maxSpeed = 80});
		pros::delay(1400);
		chassis.moveToPoint(120, 24, 2000, {.forwards = false});
		pros::delay(500);
		chassis.turnToHeading(0, 1000, {.maxSpeed = 80});
		matchLoader.set_value(false);

		topAligner.set_value(true);
		chassis.moveToPoint(122, 40, 3000, {.maxSpeed = 80});
		runTopScore();

		pros::delay(50000);
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