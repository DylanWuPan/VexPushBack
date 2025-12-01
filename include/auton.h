#pragma once
#include "globals.h"
#include "main.h"

namespace auton {
	void autonTest();
    void autonSkills();
    void autonSAWP();
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
} // namespace auton::autonSelect