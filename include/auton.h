#pragma once
#include "globals.h"
#include "main.h"

namespace auton {
	void autonTest();
    void autonSkills();
    void autonSkillsLeft();
    void autonSkills2();
    void autonSAWP(bool isRedAlliance);
    void autonSAWP2(bool isRedAlliance);
    void autonLongMiddleLeft(bool isRedAlliance);
    void autonLongMiddleRight(bool isRedAlliance);
    void autonMiddleLongLeft(bool isRedAlliance);
    void autonMiddleLongRight(bool isRedAlliance);
    void autonLeft7Long(bool isRedAlliance);
    void autonRight7Long(bool isRedAlliance);
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