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
		topScore.move_velocity(-0.67 * intakeController::TOPSCORE_VELOCITY);
		hopper.move_velocity(-0.67 * intakeController::HOPPER_VELOCITY);
		intake.move_velocity(0.67 * intakeController::INTAKE_VELOCITY);
	}

	// Auton Functions
	void autonSkills() {
		intakeController::periodicTask.end();

		chassis.setPose(55.75, 22.75, 0);

		// 3 BALLS
		chassis.moveToPoint(46, 50, 4000, {.maxSpeed = 80});
		runIntake();

		// FIRST LOADER
		chassis.moveToPoint(21, 22, 4000, {.maxSpeed = 80});
		chassis.turnToHeading(180, 500, {.maxSpeed = 80});
		matchLoader.set_value(true);
		chassis.moveToPoint(21, 12, 3000, {.maxSpeed = 80});
		pros::delay(1500);
		// chassis.setPose(25, 12.75, chassis.getPose().theta);
		pros::delay(500);
		chassis.moveToPoint(21, 10, 500, {.maxSpeed = 80});

		// LONG GOAL
		chassis.moveToPoint(21, 24, 4000, {.forwards = false, .maxSpeed = 80});
		chassis.turnToHeading(0, 1000, {.maxSpeed = 80});
		topAligner.set_value(true);
		matchLoader.set_value(false);
		chassis.moveToPoint(22, 42, 4000, {.maxSpeed = 80});
		pros::delay(500);
		runTopScore();
		pros::delay(3500);
		chassis.setPose(24, 39, 0);
		pros::delay(500);
		chassis.moveToPoint(24, 42, 500);

		//SECOND LOADER
		chassis.moveToPoint(24, 30, 4000, {.forwards = false, .maxSpeed = 80});
		runIntake();
		topAligner.set_value(false);
		chassis.turnToHeading(90, 1000, {.maxSpeed = 80});

		chassis.moveToPoint(126, 30, 5000, {.maxSpeed = 80});
		chassis.turnToHeading(180, 1000, {.maxSpeed = 80});
		matchLoader.set_value(true);
		chassis.moveToPoint(126, 12, 4000, {.maxSpeed = 80});
		pros::delay(2000);
		// chassis.setPose(120, 12.75, 180);
		pros::delay(500);
		chassis.moveToPoint(126, 10, 500, {.maxSpeed = 80});

		// SECOND LONG GOAL
		chassis.moveToPoint(126, 24, 4000, {.forwards = false, .maxSpeed = 80});
		chassis.turnToHeading(0, 1000, {.maxSpeed = 80});
		topAligner.set_value(true);
		matchLoader.set_value(false);
		chassis.moveToPoint(126, 42, 4000, {.maxSpeed = 80});
		pros::delay(500);
		runTopScore();
		pros::delay(2000);
		chassis.setPose(120, 39, 0);
		pros::delay(500);
		chassis.moveToPoint(120, 42, 500);

		// MIDDLE BALLS
		chassis.moveToPoint(120, 24, 4000, {.forwards = false, .maxSpeed = 80});
		runIntake();
		chassis.moveToPoint(96, 48, 4000, {.maxSpeed = 80});
		chassis.moveToPoint(96, 96, 4000, {.maxSpeed = 80});

		// THIRD LOADER
		chassis.moveToPoint(118, 120, 4000, {.maxSpeed = 80});
		chassis.turnToHeading(0, 1000, {.maxSpeed = 80});
		matchLoader.set_value(true);
		chassis.moveToPoint(118, 136, 4000, {.maxSpeed = 80});
		pros::delay(2000);
		// chassis.setPose(120, 131.25, 0);
		pros::delay(500);
		chassis.moveToPoint(118, 134, 1000, {.maxSpeed = 80});

		//THIRD GOAL
		chassis.moveToPoint(118, 120, 4000, {.forwards = false, .maxSpeed = 80});
		chassis.turnToHeading(180, 1000, {.maxSpeed = 80});
		topAligner.set_value(true);
		matchLoader.set_value(false);
		chassis.moveToPoint(116, 98, 4000, {.maxSpeed = 80});
		pros::delay(500);
		runTopScore();
		pros::delay(2000);
		chassis.setPose(120, 101, 180);
		pros::delay(500);
		chassis.moveToPoint(120, 98, 500);

		pros::delay(5000);
	}

	void autonSAWP(){
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
		chassis.turnToHeading(180, 500, {.maxSpeed = 80});
		matchLoader.set_value(true);
		runIntake();
		chassis.moveToPose(22, 8, 180, 3000, {.minSpeed = 60});
		pros::delay(1000);

		// Long goal
		chassis.moveToPoint(22, 24, 2000, {.forwards = false});
		chassis.moveToPose(19.5, 40.5, 1, 3000);
		pros::delay(500);
		topAligner.set_value(true);
		matchLoader.set_value(false);
		pros::delay(200);
		runTopScore();
		pros::delay(2000);
		runIntake();

		// MidGoal
		chassis.moveToPoint(19.5, 24, 4000, {.forwards = false});
		chassis.moveToPose(54.5, 62.5, 46, 3000, {.maxSpeed = 80});
		topAligner.set_value(false);
		pros::delay(800);
		matchLoader.set_value(true);
		runMiddleScore();
		pros::delay(500);
		runIntake();

		chassis.moveToPoint(48, 48, 4000, {.forwards = false, .minSpeed = 60, .earlyExitRange = 5});
		matchLoader.set_value(false);

		chassis.moveToPoint(96, 54, 4000, {.minSpeed = 40, .earlyExitRange = 5});
		pros::delay(1000);
		matchLoader.set_value(true);

		//SECOND LONG GOAL
		chassis.moveToPoint(120, 36, 4000, {.minSpeed = 40, .earlyExitRange = 5});
		matchLoader.set_value(false);
		chassis.moveToPose(122, 45, 0, 5000, {.maxSpeed = 80});
		pros::delay(500);
		topAligner.set_value(true);
		pros::delay(500);
		runTopScore();
		
		pros::delay(5000);
	}

	void autonLongMiddleLeft(){
		intakeController::isRedAlliance = true;

		chassis.setPose(55.5, 22, 270);

		// Match load
		chassis.moveToPoint(23, 22, 4000, {.maxSpeed = 80});
		chassis.turnToHeading(180, 500, {.maxSpeed = 80});
		matchLoader.set_value(true);
		runIntake();
		chassis.moveToPose(22, 8, 180, 3000, {.minSpeed = 60});
		pros::delay(1090);

		// Long goal
		chassis.moveToPoint(22, 24, 2000, {.forwards = false});
		chassis.moveToPose(20, 40.5, 1, 3000);
		pros::delay(500);
		topAligner.set_value(true);
		pros::delay(100);
		matchLoader.set_value(false);
		pros::delay(400);
		runTopScore();
		pros::delay(2000);
		chassis.moveToPoint(20, 42, 500);

		// DESCORE
		chassis.moveToPoint(20, 30, 4000, {.forwards = false, .maxSpeed = 80});
		pros::delay(200);
		topAligner.set_value(false);
		chassis.moveToPoint(20, 40.5, 2000, {.minSpeed = 120});

		// MidGoal
		chassis.moveToPoint(20, 24, 4000, {.forwards = false});
		runIntake();
		chassis.moveToPose(54, 60.5, 45, 6000, {.maxSpeed = 40});
		pros::delay(3200);
		runMiddleScore();

		pros::delay(5000);
	}

	void autonLeft7Long(){
		intakeController::isRedAlliance = true;

		chassis.setPose(55.75, 22.75, 0);

		// 3 BALLS
		chassis.moveToPoint(46, 55, 4000, {.maxSpeed = 40});
		runIntake();
		pros::delay(1400);
		matchLoader.set_value(true);

		// MATCHLOAD
		chassis.moveToPoint(22, 22, 4000, {.maxSpeed = 80});
		chassis.turnToHeading(180, 500, {.maxSpeed = 80});
		chassis.moveToPoint(21, 12, 2000, {.maxSpeed = 80});
		pros::delay(1090);

		// LONG GOAL
		chassis.moveToPoint(21, 24, 4000, {.forwards = false, .maxSpeed = 80});
		chassis.moveToPose(20, 43, 0, 4000, {.maxSpeed = 80});
		pros::delay(500);
		topAligner.set_value(true);
		pros::delay(100);
		matchLoader.set_value(false);
		pros::delay(400);
		runTopScore();
		pros::delay(3200);
		chassis.moveToPoint(20, 45, 500);

		// WINGS
		chassis.moveToPoint(34, 32, 4000, {.forwards = false, .maxSpeed = 80});
		runIntake();
		topAligner.set_value(false);
		chassis.turnToHeading(-5, 500, {.maxSpeed = 80});
		chassis.moveToPoint(32.5, 67, 10000, {.maxSpeed = 60});

		pros::delay(5000);
	}

	void autonRedRight() {
		intakeController::isRedAlliance = true;
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