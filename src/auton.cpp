#include "auton.h"
#include "intake.h"
#include "main.h"
#include "globals.h"
#include "custom-utilities.h"
using namespace devices;

namespace auton {
	// Supporting Commands
	void runIntake() {
		intake.move_velocity(intakeController::INTAKE_VELOCITY);
		hopper.move_velocity(intakeController::HOPPER_VELOCITY);
		topScore.move_velocity(-intakeController::TOPSCORE_VELOCITY);
	}

	void stopIntake() {
		intake.move_velocity(0);
		hopper.move_velocity(0);
		topScore.move_velocity(0);
	}

	void runIntakeNoHopper() {
		intake.move_velocity(intakeController::INTAKE_VELOCITY);
		hopper.move_velocity(intakeController::HOPPER_VELOCITY/10);
		topScore.move_velocity(intakeController::TOPSCORE_VELOCITY/20);
	}

	void runOuttake() {
		intake.move_velocity(-1 * intakeController::INTAKE_VELOCITY);
		hopper.move_velocity(-intakeController::HOPPER_VELOCITY);
		topScore.move_velocity(-intakeController::TOPSCORE_VELOCITY);
	}

	void runTopScore() {
		topScore.move_velocity(intakeController::TOPSCORE_VELOCITY);
		hopper.move_velocity(-intakeController::HOPPER_VELOCITY);
		intake.move_velocity(intakeController::INTAKE_VELOCITY);
	}

	void runMiddleScore() {
		topScore.move_velocity(-0.5 * intakeController::TOPSCORE_VELOCITY);
		hopper.move_velocity(-1 * intakeController::HOPPER_VELOCITY);
		intake.move_velocity(1 * intakeController::INTAKE_VELOCITY);
	}

	void runBottomScore() {
		topScore.move_velocity(-0.67 * intakeController::TOPSCORE_VELOCITY);
		hopper.move_velocity(-0.67 * intakeController::HOPPER_VELOCITY);
		intake.move_velocity(-0.67 * intakeController::INTAKE_VELOCITY);
	}

	// Auton Routes

	// void autonSkills() {
	// 	intakeController::periodicTask.end();

	// 	chassis.setPose(55.75, 22.75, 0);

	// 	// 3 BALLS
	// 	chassis.moveToPoint(46, 50, 4000, {.maxSpeed = 80});
	// 	runIntake();

	// 	// FIRST LOADER
	// 	chassis.moveToPoint(21, 22, 4000, {.maxSpeed = 80});
	// 	chassis.turnToHeading(180, 500, {.maxSpeed = 80});
	// 	matchLoader.set_value(true);
	// 	chassis.moveToPoint(21, 11, 3000, {.maxSpeed = 80});
	// 	pros::delay(1500);
	// 	chassis.setPose(utilities::getPoseWithDistance(true, true, false, false));
	// 	pros::delay(500);
	// 	chassis.moveToPoint(21, 9, 500, {.maxSpeed = 20});
	// 	pros::delay(500);

	// 	// FIRST LONG GOAL
	// 	chassis.moveToPoint(21, 24, 4000, {.forwards = false, .maxSpeed = 80});
	// 	chassis.turnToHeading(0, 1000, {.maxSpeed = 80});
	// 	topAligner.set_value(true);
	// 	matchLoader.set_value(false);
	// 	chassis.moveToPoint(22, 42, 2000, {.maxSpeed = 60});
	// 	pros::delay(500);
	// 	runTopScore();
	// 	pros::delay(2000);
	// 	chassis.moveToPoint(22, 45, 500, {.maxSpeed = 20});
	// 	pros::delay(500);
	// 	chassis.setPose(24, 39, chassis.getPose().theta);
	// 	pros::delay(1000);
	// 	chassis.moveToPoint(24, 42, 500, {.maxSpeed = 20});
	// 	pros::delay(500);

	// 	//SECOND LOADER
	// 	chassis.moveToPoint(24, 30, 4000, {.forwards = false, .maxSpeed = 80});
	// 	runIntake();
	// 	topAligner.set_value(false);
	// 	chassis.turnToHeading(90, 1000, {.maxSpeed = 80});

	// 	chassis.moveToPoint(124.5, 30, 5000, {.maxSpeed = 80});
	// 	chassis.turnToHeading(180, 1000, {.maxSpeed = 80});
	// 	matchLoader.set_value(true);
	// 	chassis.moveToPoint(124.5, 8, 4000, {.maxSpeed = 80});
	// 	pros::delay(1500);
	// 	chassis.setPose(utilities::getPoseWithDistance(true, false, false, true));
	// 	pros::delay(500);
	// 	chassis.moveToPoint(124.5, 6, 500, {.maxSpeed = 20});
	// 	pros::delay(500);

	// 	// SECOND LONG GOAL
	// 	chassis.moveToPoint(124, 24, 4000, {.forwards = false, .maxSpeed = 80});
	// 	chassis.turnToHeading(0, 1000, {.maxSpeed = 80});
	// 	topAligner.set_value(true);
	// 	matchLoader.set_value(false);
	// 	chassis.moveToPoint(124, 38, 2000, {.maxSpeed = 60});
	// 	pros::delay(500);
	// 	runTopScore();
	// 	pros::delay(2000);
	// 	chassis.moveToPoint(124, 42, 500, {.maxSpeed = 20});
	// 	pros::delay(500);
	// 	chassis.setPose(120, 39, chassis.getPose().theta);
	// 	pros::delay(500);
	// 	chassis.moveToPoint(120, 42, 500, {.maxSpeed = 20});
	// 	pros::delay(500);

	// 	// MIDDLE BALLS
	// 	chassis.moveToPoint(120, 24, 4000, {.forwards = false, .maxSpeed = 80});
	// 	runIntake();
	// 	chassis.moveToPoint(96, 48, 4000, {.maxSpeed = 80});
	// 	chassis.moveToPoint(96, 96, 4000, {.maxSpeed = 80});

	// 	// THIRD LOADER
	// 	chassis.moveToPoint(118, 120, 4000, {.maxSpeed = 80});
	// 	chassis.turnToHeading(0, 1000, {.maxSpeed = 80});
	// 	matchLoader.set_value(true);
	// 	topAligner.set_value(false);
	// 	chassis.moveToPoint(118, 136, 4000, {.maxSpeed = 80});
	// 	pros::delay(1500);
	// 	chassis.setPose(utilities::getPoseWithDistance(true, true, false, false));
	// 	pros::delay(500);
	// 	chassis.moveToPoint(118, 138, 500, {.maxSpeed = 20});
	// 	pros::delay(500);

	// 	//THIRD GOAL
	// 	chassis.moveToPoint(118, 120, 4000, {.forwards = false, .maxSpeed = 80});
	// 	chassis.turnToHeading(180, 1000, {.maxSpeed = 80});
	// 	topAligner.set_value(true);
	// 	matchLoader.set_value(false);
	// 	chassis.moveToPoint(118, 105, 2000, {.maxSpeed = 60});
	// 	pros::delay(500);
	// 	runTopScore();
	// 	pros::delay(1500);
	// 	chassis.moveToPoint(118, 102, 500, {.maxSpeed = 20});
	// 	pros::delay(500);
	// 	chassis.setPose(120, 105, chassis.getPose().theta);
	// 	pros::delay(500);
	// 	chassis.moveToPoint(120, 102, 500, {.maxSpeed = 20});
	// 	pros::delay(500);

	// 	// FOURTH LOADER
	// 	chassis.moveToPoint(120, 114, 4000, {.forwards = false, .maxSpeed = 80});
	// 	runIntake();
	// 	topAligner.set_value(false);
	// 	chassis.turnToHeading(-90, 1000, {.maxSpeed = 80});

	// 	chassis.moveToPoint(18, 114, 5000, {.maxSpeed = 80});
	// 	chassis.turnToHeading(0, 1000, {.maxSpeed = 80});
	// 	matchLoader.set_value(true);
	// 	chassis.moveToPoint(18, 135, 4000, {.maxSpeed = 80});
	// 	pros::delay(1500);
	// 	chassis.setPose(utilities::getPoseWithDistance(true, false, false, true));
	// 	pros::delay(500);
	// 	chassis.moveToPoint(18, 137, 500, {.maxSpeed = 20});
	// 	pros::delay(500);

	// 	// FOURTH LONG GOAL
	// 	chassis.moveToPoint(18, 120, 4000, {.forwards = false, .maxSpeed = 80});
	// 	chassis.turnToHeading(180, 1000, {.maxSpeed = 80});
	// 	topAligner.set_value(true);
	// 	matchLoader.set_value(false);
	// 	chassis.moveToPoint(18, 99, 2000, {.maxSpeed = 60});
	// 	pros::delay(500);
	// 	runTopScore();
	// 	pros::delay(2000);
	// 	chassis.moveToPoint(18, 96, 500, {.maxSpeed = 20});
	// 	pros::delay(500);
	// 	chassis.setPose(24, 102, chassis.getPose().theta);
	// 	pros::delay(500);
	// 	chassis.moveToPoint(24, 99, 500, {.maxSpeed = 20});
	// 	pros::delay(500);

	// 	chassis.moveToPoint(72, 140, 100000, {.forwards = false});

	// 	pros::delay(5000);
	// }

	void autonSkills() {
		// Didn't change points yet
		intakeController::periodicTask.end();

		chassis.setPose(55.75, 22.75, 0);

		// 3 BALLS
		chassis.moveToPoint(46, 50, 4000, {.maxSpeed = 80});
		runIntake();
		// pros::delay(650);
		// matchLoader.set_value(true);

		// FIRST LOADER
		chassis.moveToPoint(21, 22, 4000, {.maxSpeed = 80});
		chassis.turnToHeading(180, 500, {.maxSpeed = 80});
		matchLoader.set_value(true);
		chassis.moveToPoint(21, 9.5, 3000, {.maxSpeed = 80});
		pros::delay(1500);
		// chassis.setPose(25, 12.75, chassis.getPose().theta);
		pros::delay(500);
		chassis.moveToPoint(21, 8, 500, {.maxSpeed = 20});
		pros::delay(500);

		// FIRST LONG GOAL
		chassis.moveToPoint(21, 24, 4000, {.forwards = false, .maxSpeed = 80});
		chassis.turnToHeading(0, 1000, {.maxSpeed = 80});
		topAligner.set_value(true);
		matchLoader.set_value(false);
		chassis.moveToPoint(22, 42, 2000, {.maxSpeed = 60});
		pros::delay(500);
		runTopScore();
		pros::delay(2000);
		chassis.moveToPoint(22, 45, 500, {.maxSpeed = 20});
		pros::delay(500);
		chassis.setPose(24, 39, chassis.getPose().theta);
		pros::delay(1000);
		chassis.moveToPoint(24, 42, 500, {.maxSpeed = 20});
		pros::delay(500);

		// SECOND LOADER
		chassis.moveToPoint(24, 30, 4000, {.forwards = false, .maxSpeed = 80});
		runIntake();
		topAligner.set_value(false);
		chassis.turnToHeading(90, 1000, {.maxSpeed = 80});
		chassis.moveToPoint(110, 30, 5000, {.maxSpeed = 80});
		pros::delay(3000);
		chassis.setPose(utilities::getPoseWithDistance(true, true, false, false));
		pros::delay(500);
		chassis.moveToPoint(121.5, 30, 5000, {.maxSpeed = 80});
		chassis.turnToHeading(180, 1000, {.maxSpeed = 80});
		matchLoader.set_value(true);
		chassis.moveToPose(121.5, 7, 180, 4000, {.maxSpeed = 80});
		pros::delay(2000);
		chassis.moveToPoint(121.5, 5, 500, {.maxSpeed = 20});
		pros::delay(500);

		// SECOND LONG GOAL
		chassis.moveToPoint(121.5, 24, 4000, {.forwards = false, .maxSpeed = 80});
		chassis.turnToHeading(0, 1000, {.maxSpeed = 80});
		topAligner.set_value(true);
		matchLoader.set_value(false);
		chassis.moveToPose(121.5, 38, 0, 2000);
		pros::delay(500);
		runTopScore();
		pros::delay(2000);
		chassis.moveToPoint(121.5, 42, 500, {.maxSpeed = 20});
		pros::delay(500);
		chassis.setPose(120, 39, chassis.getPose().theta);
		pros::delay(500);
		chassis.moveToPoint(120, 42, 500, {.maxSpeed = 20});
		pros::delay(500);

		// MIDDLE BALLS
		chassis.moveToPoint(120, 24, 4000, {.forwards = false, .maxSpeed = 80});
		runIntake();
		chassis.moveToPoint(96, 48, 4000, {.maxSpeed = 80});
		chassis.moveToPoint(96, 96, 4000, {.maxSpeed = 80});

		// THIRD LOADER
		chassis.moveToPoint(118, 120, 4000, {.maxSpeed = 80});
		chassis.turnToHeading(0, 1000, {.maxSpeed = 80});
		matchLoader.set_value(true);
		topAligner.set_value(false);
		chassis.moveToPoint(118, 136, 4000, {.maxSpeed = 80});
		pros::delay(2500);
		chassis.moveToPoint(118, 138, 500, {.maxSpeed = 20});
		pros::delay(500);

		//THIRD GOAL
		chassis.moveToPoint(118, 120, 4000, {.forwards = false, .maxSpeed = 80});
		chassis.turnToHeading(180, 1000, {.maxSpeed = 80});
		topAligner.set_value(true);
		matchLoader.set_value(false);
		chassis.moveToPoint(118, 105, 2000, {.maxSpeed = 60});
		pros::delay(500);
		runTopScore();
		pros::delay(1500);
		chassis.moveToPoint(118, 102, 500, {.maxSpeed = 20});
		pros::delay(500);
		chassis.setPose(120, 105, chassis.getPose().theta);
		pros::delay(500);
		chassis.moveToPoint(120, 102, 500, {.maxSpeed = 20});
		pros::delay(500);

		// // FOURTH LOADER
		// chassis.moveToPoint(120, 114, 4000, {.forwards = false, .maxSpeed = 80});
		// runIntake();
		// topAligner.set_value(false);
		// chassis.turnToHeading(-90, 1000, {.maxSpeed = 80});

		// chassis.moveToPoint(18, 114, 5000, {.maxSpeed = 80});
		// chassis.turnToHeading(0, 1000, {.maxSpeed = 80});
		// matchLoader.set_value(true);
		// chassis.moveToPoint(18, 135, 4000, {.maxSpeed = 80});
		// pros::delay(2500);
		// chassis.moveToPoint(18, 137, 500, {.maxSpeed = 20});
		// pros::delay(500);

		// // FOURTH LONG GOAL
		// chassis.moveToPoint(18, 120, 4000, {.forwards = false, .maxSpeed = 80});
		// chassis.turnToHeading(180, 1000, {.maxSpeed = 80});
		// topAligner.set_value(true);
		// matchLoader.set_value(false);
		// chassis.moveToPoint(18, 99, 2000, {.maxSpeed = 60});
		// pros::delay(500);
		// runTopScore();
		// pros::delay(2000);
		// chassis.moveToPoint(18, 96, 500, {.maxSpeed = 20});
		// pros::delay(500);
		// chassis.setPose(24, 102, chassis.getPose().theta);
		// pros::delay(500);
		// chassis.moveToPoint(24, 99, 500, {.maxSpeed = 20});
		// pros::delay(500);

		// chassis.moveToPoint(72, 140, 100000, {.forwards = false});

		// pros::delay(5000);
	}

	void autonSAWP() {
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

	void autonSAWP2() {
		chassis.setPose(55.75, 22.75, 0);

		// HIGH MID
		chassis.moveToPose(56, 61.5, 50, 3000);
		runIntake();
		pros::delay(2000);
		runMiddleScore();
		pros::delay(500);
		runIntake();

		// LOW MID
		chassis.moveToPoint(48, 54, 4000, {.forwards = false, .maxSpeed = 120});
		matchLoader.set_value(false);
		chassis.moveToPose(83, 65, -45, 3000);
		pros::delay(1500);
		runOuttake();
		pros::delay(1500);
		runIntake();
		
		// MATCH LOAD
		chassis.moveToPoint(120, 24, 4000, {.forwards = false, .maxSpeed = 120});
		chassis.turnToHeading(180, 1000, {.maxSpeed = 120});
		matchLoader.set_value(true);
		chassis.moveToPoint(120, 10, 1000, {.maxSpeed = 120});
		pros::delay(1050);
		chassis.moveToPoint(120, 24, 4000, {.forwards = false, .maxSpeed = 120});
		
		// LONG GOAL
		chassis.moveToPose(122, 46, 0, 4000);
		matchLoader.set_value(false);
		topAligner.set_value(true);
		pros::delay(1000);
		runTopScore();

		pros::delay(5000);
	}

	void autonLongMiddleLeft() {
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

	void autonLongMiddleRight() {
		chassis.setPose(88.5, 22, 90);

		// Match load
		chassis.moveToPoint(121, 22, 4000, {.maxSpeed = 80});
		chassis.turnToHeading(180, 500, {.maxSpeed = 80});
		matchLoader.set_value(true);
		runIntake();
		chassis.moveToPose(122, 7, 180, 3000/*, {.minSpeed = 60}*/);
		pros::delay(1090);

		// Long goal
		chassis.moveToPoint(122, 24, 2000, {.forwards = false});
		chassis.moveToPose(122, 40.5, 1, 3000);
		pros::delay(500);
		topAligner.set_value(true);
		pros::delay(100);
		matchLoader.set_value(false);
		pros::delay(400);
		runTopScore();
		pros::delay(2000);
		chassis.moveToPoint(120, 42, 500);

		// DESCORE
		chassis.moveToPoint(124, 30, 4000, {.forwards = false, .maxSpeed = 80});
		pros::delay(200);
		topAligner.set_value(false);
		chassis.moveToPoint(124, 40.5, 2000, {.minSpeed = 120});

		// MidGoal
		chassis.moveToPoint(124, 24, 4000, {.forwards = false});
		runIntake();
		chassis.moveToPose(86.5, 64, 315, 6000, {.maxSpeed = 40});
		pros::delay(3200);
		runBottomScore();

		pros::delay(5000);

	}

	void autonLeft7Long() {
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

	void autonRight7Long() {
		chassis.setPose(88.25, 22.75, 0);

		// 3 BALLS
		chassis.moveToPoint(98, 55, 4000, {.maxSpeed = 40});
		runIntake();
		pros::delay(1400);
		matchLoader.set_value(true);

		// MATCHLOAD
		chassis.moveToPoint(122, 22, 4000, {.maxSpeed = 80});
		chassis.turnToHeading(180, 500, {.maxSpeed = 80});
		chassis.moveToPoint(123, 10, 2000, {.maxSpeed = 80});
		pros::delay(1090);

		// LONG GOAL
		chassis.moveToPoint(123, 24, 4000, {.forwards = false, .maxSpeed = 80});
		chassis.moveToPose(124, 43, 0, 4000, {.maxSpeed = 80});
		pros::delay(500);
		topAligner.set_value(true);
		pros::delay(100);
		matchLoader.set_value(false);
		pros::delay(400);
		runTopScore();
		pros::delay(3200);
		chassis.moveToPoint(124, 45, 500);

		// WINGS
		chassis.moveToPoint(113, 32, 4000, {.forwards = false, .maxSpeed = 80});
		runIntake();
		topAligner.set_value(false);
		chassis.turnToHeading(4, 500, {.maxSpeed = 80});
		chassis.moveToPoint(114, 67, 10000, {.maxSpeed = 60});

		pros::delay(5000);
	}
} // namespace auton


// FOR SELECTING AUTON MODE BEFORE MATCH
namespace auton::autonSelect {
	autonMode mode(autonMode::SKILLS);

	void printAutonMode(int line) {
		switch (mode) {
			case autonMode::SKILLS:
				pros::lcd::set_text(line, "Auton mode: Skills");
				break;
			case autonMode::SAWP:
				pros::lcd::set_text(line, "Auton mode: SAWP");
				break; 
			case autonMode::LONG_MIDDLE_LEFT:
				pros::lcd::set_text(line, "Auton mode: Long Middle Left");
				break;
			case autonMode::LONG_MIDDLE_RIGHT:
				pros::lcd::set_text(line, "Auton mode: Long Middle Right");
				break;
			case autonMode::LEFT_7_LONG:
				pros::lcd::set_text(line, "Auton mode: Left 7 Long");
				break;
			case autonMode::RIGHT_7_LONG:
				pros::lcd::set_text(line, "Auton mode: Right 7 Long");
				break;
			default:
				break;
		}
		pros::lcd::set_text(line + 1, "Alliance: " + intakeController::isRedAlliance? "RED" : "BLUE");
	}
	void incrementAutonMode() {
		mode = static_cast<autonMode>((static_cast<int>(mode) + 1) % NUM_AUTONS);
	}
	void decrementAutonMode() {
		mode = static_cast<autonMode>((static_cast<int>(mode) - 1) % NUM_AUTONS);
	}
} // namespace autonSelect