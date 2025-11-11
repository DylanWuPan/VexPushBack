#pragma once
#include "main.h"
#include "globals.h"

// TODO: Figure out what this is for
constexpr int TURN_SPEED = 80;

namespace auton {
	// Supporting Commands
	void runIntake();
	void stopIntake();
	void runIntakeNoHopper();
	void outtake();
	void runTopScore();
	void runMiddleScore();
	void runBottomScore();
	// Auton Routes
	void autonSkills();
	void autonSAWP();
	void autonSAWP2();
	void autonLongMiddleLeft();
	void autonLongMiddleRight();
	void autonLeft7Long();
	void autonRight7Long();
} // namespace auton


// FOR SELECTING AUTON MODE BEFORE MATCH
namespace auton::autonSelect { 
	enum class autonMode {
		SKILLS,
		SAWP,
		LONG_MIDDLE_LEFT,
		LONG_MIDDLE_RIGHT,
		LEFT_7_LONG,
		RIGHT_7_LONG,
		END // for incrementation
	};

	constexpr int NUM_AUTONS = static_cast<int>(autonMode::END);

	extern autonMode mode;

	inline autonMode getAutonMode() {
		return mode;
	}

	void printAutonMode(int line);
	void incrementAutonMode();
	void decrementAutonMode();
} // namespace autonSelect