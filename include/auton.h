#pragma once
#include "main.h"
#include "globals.h"

// TODO: Figure out what this is for
constexpr int TURN_SPEED = 80;

namespace auton {
	// Auton Functions
	void autonSkills();
	void autonSAWP();
	void autonLongMiddleLeft();
	void autonBlueRight();
	void autonBlueLeft();
	void autonRedRight();
	void autonRedLeft();
} // namespace auton


// FOR SELECTING AUTON MODE BEFORE MATCH
namespace auton::autonSelect { 
	enum class autonMode {
		SKILLS,
		BLUE_RIGHT,
		BLUE_LEFT,
		RED_RIGHT,
		RED_LEFT,
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