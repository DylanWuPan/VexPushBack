#include "auton.h"
#include "intake.h"

namespace auton {
	// Auton Functions
	void autonSkills() {
		// intakeController::periodicTask.end();
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