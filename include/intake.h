#pragma once
#include "main.h"
#include "globals.h"
#include "auton.h"
#include "periodic-task.h"

namespace intakeController {
    using namespace devices;

    // ---------- Variables ----------
    constexpr int DELAY = 5;

    extern bool isColorSorting;
    extern bool isAntiJamming;
    extern bool isSkipping;
    extern bool isJamming;
    extern bool rogueBall;

    extern int antiJamPauseEndTime; // for pausing antijam

    extern double jamThreshold;

    extern bool isRedAlliance;
    constexpr int BLUE_HUE = 240;
    constexpr int RED_HUE = 350;
	constexpr int INTAKE_VELOCITY_MAX = 600;
	constexpr int HOPPER_VELOCITY_MAX = 200;
	constexpr int TOPSCORE_VELOCITY_MAX = 200;

    constexpr int ANTI_JAM_PAUSE_DURATION = 100;

    enum class intakeState {
        Intake,
        TopScore,
        MiddleScore,
        BottomScore,
        Stop,
    };

    extern intakeState currentState;

    void setIntakeState(intakeState state);

    void discardBall();

    void start();
    void update();
    extern PeriodicTask periodicTask;
}