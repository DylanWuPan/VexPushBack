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
	void autonSkills() {
		intakeController::isColorSorting = false;

		chassis.setPose(58, 22, -90);

		// FIRST LOADER
		chassis.moveToPoint(24, 22, 4000, {.maxSpeed = 80});
		chassis.turnToHeading(180, 500, {.maxSpeed = 80});
		runIntake();
		matchLoader.set_value(true);
		chassis.moveToPoint(24, 7.5, 2500, {.maxSpeed = 80});
		pros::delay(2500);

		// FIRST LONG GOAL
		chassis.moveToPoint(24, 22, 4000, {.forwards = false, .maxSpeed = 80});
		chassis.turnToHeading(0, 1000, {.maxSpeed = 80});
		topAligner.set_value(true);
		matchLoader.set_value(false);
		pros::delay(1100);
		chassis.setPose(utilities::getPoseWithDistance(false, false, false, true));
		// pros::delay(100);
		chassis.moveToPose(23, 41.5, 0, 2000);
		pros::delay(300);
		runTopScore();
		pros::delay(3000);
		chassis.setPose(24, 39, chassis.getPose().theta);
		pros::delay(1000);

		// SECOND LOADER
		runIntake();
		chassis.moveToPoint(24, 28, 4000, {.forwards = false, .maxSpeed = 80});
		topAligner.set_value(false);
		chassis.turnToHeading(90, 1000, {.maxSpeed = 80});
		// chassis.moveToPoint(110, 28, 5000, {.maxSpeed = 80});
		chassis.moveToPoint(121.5, 28, 5000, {.maxSpeed = 80});
		pros::delay(1500);
		chassis.setPose(utilities::getPoseWithDistance(true, true, false, false));
		// pros::delay(100);
		// chassis.moveToPoint(121.5, 28, 5000, {.maxSpeed = 80});
		chassis.turnToHeading(180, 1000, {.maxSpeed = 80});
		matchLoader.set_value(true);
		chassis.moveToPoint(121.5, 4.5, 2000, {.maxSpeed = 80});
		pros::delay(2000);
		chassis.moveToPoint(121.5, 3, 500, {.maxSpeed = 20});
		pros::delay(500);

		// SECOND LONG GOAL
		chassis.moveToPoint(121.5, 20, 4000, {.forwards = false, .maxSpeed = 80});
		chassis.turnToHeading(0, 1000, {.maxSpeed = 80});
		topAligner.set_value(true);
		matchLoader.set_value(false);
		pros::delay(1200);
		chassis.setPose(utilities::getPoseWithDistance(false, true, false, false));
		// pros::delay(100);
		chassis.moveToPose(119.5, 44, 0, 2000);
		pros::delay(500);
		runTopScore();
		pros::delay(2500);
		chassis.moveToPoint(119.5, 45, 400, {.maxSpeed = 20});
		pros::delay(500);
		chassis.setPose(120, 39, chassis.getPose().theta);
		pros::delay(500);

		// ALLEY
		runIntake();
		topAligner.set_value(false);
		chassis.moveToPoint(120, 25, 4000, {.forwards = false, .maxSpeed = 80});
		chassis.moveToPose(133, 52, 0, 4000);
		pros::delay(2000);
		chassis.setPose(utilities::getPoseWithDistance(false, true, false, false));
		// pros::delay(100);
		chassis.moveToPoint(131, 105, 4000, {.maxSpeed = 80});
		pros::delay(1500);
		chassis.setPose(utilities::getPoseWithDistance(true, true, false, false));
		pros::delay(100);

		// THIRD LOADER
		chassis.moveToPoint(116.5, 120, 4000, {.maxSpeed = 80});
		chassis.turnToHeading(0, 1000, {.maxSpeed = 80});
		matchLoader.set_value(true);
		topAligner.set_value(false);
		chassis.moveToPoint(116.5, 137, 2000, {.maxSpeed = 80});
		pros::delay(2000);
		chassis.moveToPoint(116.5, 140, 500, {.maxSpeed = 20});
		pros::delay(500);

		// THIRD GOAL
		chassis.moveToPoint(117, 124, 4000, {.forwards = false, .maxSpeed = 80});
		chassis.turnToHeading(179, 1000, {.maxSpeed = 80});
		topAligner.set_value(true);
		matchLoader.set_value(false);
		pros::delay(1100);
		chassis.setPose(utilities::getPoseWithDistance(false, false, false, true));
		// pros::delay(100);
		chassis.moveToPose(120.5, 102, 180, 4000);
		pros::delay(500);
		runTopScore();
		pros::delay(1500);
		chassis.moveToPoint(120.5, 100, 500, {.maxSpeed = 20});
		pros::delay(500);
		chassis.setPose(120, 105, chassis.getPose().theta);
		pros::delay(500);

		// FOURTH LOADER
		runIntake();
		chassis.moveToPoint(120, 112, 4000, {.forwards = false, .maxSpeed = 80});
		topAligner.set_value(false);
		chassis.turnToHeading(-90, 1000, {.maxSpeed = 80});
		chassis.moveToPoint(21.5, 112, 5000, {.maxSpeed = 80});
		pros::delay(1500);
		chassis.setPose(utilities::getPoseWithDistance(true, true, false, false));
		// pros::delay(100);
		chassis.turnToHeading(0, 1000, {.maxSpeed = 80});
		matchLoader.set_value(true);
		chassis.moveToPoint(21.5, 141, 2000, {.maxSpeed = 80});
		pros::delay(2000);
		chassis.moveToPoint(21.5, 144, 1000, {.maxSpeed = 20});
		pros::delay(1000);

		// FOURTH LONG GOAL
		chassis.moveToPoint(21.5, 120, 4000, {.forwards = false, .maxSpeed = 80});
		chassis.turnToHeading(180, 1000, {.maxSpeed = 80});
		topAligner.set_value(true);
		matchLoader.set_value(false);
		pros::delay(1100);
		chassis.setPose(utilities::getPoseWithDistance(false, true, false, false));
		// pros::delay(100);
		chassis.moveToPose(25, 98, 180, 2000);
		pros::delay(500);
		runTopScore();
		pros::delay(2500);
		chassis.moveToPoint(25, 97, 400, {.maxSpeed = 20});
		pros::delay(1000);
		chassis.setPose(24, 105, chassis.getPose().theta);
		pros::delay(500);

		//PARK
		chassis.moveToPoint(24, 120, 4000, {.forwards = false, .maxSpeed = 80});
		// chassis.moveToPose(72, 140, 90, 100000, {.forwards = false, .minSpeed = 100});
		chassis.moveToPose(72, 120, 0, 4000, {.maxSpeed = 80});
		chassis.moveToPoint(72, 140, 100000, {.minSpeed = 100});
		pros::delay(2000);
		matchLoader.set_value(true);

		pros::delay(5000);
	}

	void autonSAWP() {
		chassis.setPose(55.75, 22.75, 0);

		if (!intakeController::isRedAlliance) {
			intakeController::isColorSorting = false;
		}

		intakeController::isAntiJamming = false;
		hopper.move_voltage(10000);
		pros::delay(20);
		hopper.brake();
		intakeController::isAntiJamming = true;

		// 3 BALLS
		chassis.moveToPoint(46, 55, 1000, {.maxSpeed = 80});
		// hopper.brake();
		runIntake();
		// intakeController::isAntiJamming = true;
		pros::delay(600);
		matchLoader.set_value(true);

		// HIGH MID
		chassis.moveToPose(56.5, 62.5, 55, 2000);
		runIntake();
		pros::delay(1100);
		runMiddleScore();
		pros::delay(1400);

		// LOW MID
		chassis.moveToPoint(48, 54, 4000, {.forwards = false, .maxSpeed = 120});
		runIntake();
		matchLoader.set_value(false);
		chassis.moveToPose(81, 65, -30, 3000);
		pros::delay(1300);
		runOuttake();
		pros::delay(1700);
		
		// MATCH LOAD
		chassis.moveToPoint(122, 24, 4000, {.forwards = false, .maxSpeed = 120});
		runIntake();
		chassis.turnToHeading(180, 1000, {.maxSpeed = 120});
		matchLoader.set_value(true);
		chassis.moveToPoint(122, 9, 1100, {.maxSpeed = 120});
		pros::delay(1200);
		chassis.moveToPoint(122, 24, 4000, {.forwards = false, .maxSpeed = 120});
		
		// LONG GOAL
		chassis.moveToPose(122.5, 46, 0, 4000);
		topAligner.set_value(true);
		pros::delay(500);
		matchLoader.set_value(false);
		pros::delay(500);
		runTopScore();
		pros::delay(70);
		runTopScore();

		pros::delay(5000);
	}

	void autonLongMiddleLeft() {
		chassis.setPose(55.5, 22, 270);

		if (!intakeController::isRedAlliance) {
			intakeController::isColorSorting = false;
		}

		intakeController::isAntiJamming = false;
		hopper.move_voltage(10000);
		pros::delay(20);
		hopper.brake();
		intakeController::isAntiJamming = true;

		// hopper.move_relative(20, 50);

		// Match load
		chassis.moveToPoint(24, 22, 4000, {.maxSpeed = 80});
		chassis.turnToHeading(180, 550, {.maxSpeed = 80});
		matchLoader.set_value(true);
		// hopper.brake();
		runIntake();
		// intakeController::isAntiJamming = true;
		chassis.moveToPoint(22, 3, 1200, {.minSpeed = 120});
		pros::delay(1200);

		// Long goal
		chassis.moveToPoint(22, 24, 2000, {.forwards = false});
		chassis.moveToPose(20, 40.5, 1, 3000);
		pros::delay(500);
		topAligner.set_value(true);
		pros::delay(100);
		matchLoader.set_value(false);
		pros::delay(400);
		runTopScore();
		pros::delay(2200);
		chassis.moveToPoint(20, 42, 500);

		// // DESCORE
		// chassis.moveToPoint(20, 30, 4000, {.forwards = false, .minSpeed = 80, .earlyExitRange = 2});
		// pros::delay(200);
		topAligner.set_value(false);
		// chassis.moveToPoint(20, 40.5, 2000, {.minSpeed = 120});

		// MidGoal
		chassis.moveToPoint(20, 24, 4000, {.forwards = false});
		runIntake();
		topAligner.set_value(false);
		chassis.moveToPose(54.5, 62, 47, 6000, {.maxSpeed = 50});
		pros::delay(2500);
		runMiddleScore();

		pros::delay(5000);
	}

	void autonLongMiddleRight() {
		chassis.setPose(88.5, 22, 90);

		if (!intakeController::isRedAlliance) {
			intakeController::isColorSorting = false;
		}

		intakeController::isAntiJamming = false;
		hopper.move_voltage(10000);
		pros::delay(20);
		hopper.brake();
		intakeController::isAntiJamming = true;

		// Match load
		chassis.moveToPoint(121, 22, 4000, {.maxSpeed = 80});
		chassis.turnToHeading(180, 500, {.maxSpeed = 80});
		matchLoader.set_value(true);
		// hopper.brake();
		runIntake();
		// intakeController::isAntiJamming = true;
		chassis.moveToPoint(122, 3, 1200/*, {.minSpeed = 60}*/);
		pros::delay(1200);

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
		// chassis.moveToPoint(124, 30, 4000, {.forwards = false, .maxSpeed = 80});
		// pros::delay(200);
		// topAligner.set_value(false);
		// chassis.moveToPoint(124, 40.5, 2000, {.minSpeed = 120});

		// MidGoal
		chassis.moveToPoint(124, 24, 4000, {.forwards = false});
		runIntake();
		topAligner.set_value(false);
		chassis.moveToPose(84, 62, -43, 6000, {.maxSpeed = 40});
		pros::delay(2500);
		runBottomScore();

		pros::delay(5000);

	}

	void autonLeft7Long() {
		chassis.setPose(55.75, 22.75, 0);

		if (!intakeController::isRedAlliance) {
			intakeController::isColorSorting = false;
		}

		intakeController::isAntiJamming = false;
		hopper.move_voltage(10000);
		pros::delay(20);
		hopper.brake();
		intakeController::isAntiJamming = true;

		// 3 BALLS
		chassis.moveToPoint(46, 55, 4000, {.maxSpeed = 40});
		// hopper.brake();
		runIntake();
		// intakeController::isAntiJamming = true;
		pros::delay(1500);
		matchLoader.set_value(true);

		// MATCHLOAD
		chassis.moveToPoint(22, 22, 4000, {.maxSpeed = 80});
		chassis.turnToHeading(180, 500, {.maxSpeed = 80});
		chassis.moveToPoint(21, 8, 1100, {.maxSpeed = 120});
		pros::delay(1100);

		// LONG GOAL
		chassis.moveToPoint(21, 24, 4000, {.forwards = false, .maxSpeed = 80});
		chassis.moveToPose(20, 43, 0, 4000, {.maxSpeed = 80});
		pros::delay(500);
		topAligner.set_value(true);
		pros::delay(100);
		matchLoader.set_value(false);
		pros::delay(400);
		runTopScore();
		pros::delay(3700);
		chassis.moveToPoint(20, 45, 500);

		// WINGS
		chassis.moveToPoint(32.75, 32, 4000, {.forwards = false, .maxSpeed = 80});
		runIntake();
		topAligner.set_value(false);
		chassis.turnToHeading(-5, 500, {.maxSpeed = 80});
		chassis.moveToPoint(31.5, 67, 10000, {.maxSpeed = 60});

		pros::delay(5000);
	}

	void autonRight7Long() {
		chassis.setPose(88.25, 22.75, 0);

		if (!intakeController::isRedAlliance) {
			intakeController::isColorSorting = false;
		}

		intakeController::isAntiJamming = false;
		hopper.move_voltage(10000);
		pros::delay(20);
		hopper.brake();
		intakeController::isAntiJamming = true;

		// 3 BALLS
		chassis.moveToPoint(98, 55, 4000, {.maxSpeed = 40});
		// hopper.brake();
		runIntake();
		// intakeController::isAntiJamming = true;
		pros::delay(1500);
		matchLoader.set_value(true);

		// MATCHLOAD
		chassis.moveToPoint(123, 22, 4000, {.maxSpeed = 80});
		chassis.turnToHeading(180, 500, {.maxSpeed = 80});
		chassis.moveToPoint(124.5, 10, 1100, {.maxSpeed = 120});
		pros::delay(1100);

		// LONG GOAL
		chassis.moveToPoint(123.5, 24, 4000, {.forwards = false, .maxSpeed = 80});
		chassis.moveToPose(124.5, 43, 0, 4000, {.maxSpeed = 80});
		pros::delay(500);
		topAligner.set_value(true);
		pros::delay(100);
		matchLoader.set_value(false);
		pros::delay(400);
		runTopScore();
		pros::delay(3700);
		chassis.moveToPoint(124, 45, 500);

		// WINGS
		chassis.moveToPoint(113, 32, 4000, {.forwards = false, .maxSpeed = 80});
		runIntake();
		topAligner.set_value(false);
		chassis.turnToHeading(4, 500, {.maxSpeed = 80});
		chassis.moveToPoint(114, 66, 10000, {.maxSpeed = 60});

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