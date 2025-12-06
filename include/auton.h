#pragma once
#include "globals.h"
#include "main.h"

namespace auton {
	// void autonTest();
    void autonSkills();
    void autonSkillsLeft();
    void autonSkills2();
    void autonSAWP();
    void autonSAWP2();
    void autonLongMiddleLeft();
    void autonLongMiddleRight();
    void autonMiddleLongLeft();
    void autonMiddleLongRight();
    void autonLeft7Long();
    void autonRight7Long();
} // namespace auton

// FOR SELECTING AUTON MODE BEFORE MATCH
namespace auton::autonSelect {
    enum class autonMode {
        SKILLS,
        SAWP,
        MIDDLE_LONG_LEFT,
        MIDDLE_LONG_RIGHT,
        LONG_MIDDLE_RIGHT,
        LONG_MIDDLE_LEFT,
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