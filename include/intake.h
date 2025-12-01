#pragma once
#include "auton.h"
#include "globals.h"
#include "main.h"
#include "periodic-task.h"

namespace intakeController {
    // ---------- Types ----------

    enum class intakeState {
        Intake,
        TopScore,
        MiddleScore,
        BottomScore,
        Stop,
    };

    // ---------- Constants ----------

    constexpr int DELAY = 5; // msec

    constexpr int BLUE_HUE = 240;
    constexpr int RED_HUE = 350;

    constexpr int INTAKE_VELOCITY_MAX = 600;   // rpm
    constexpr int HOPPER_VELOCITY_MAX = 200;   // rpm
    constexpr int TOPSCORE_VELOCITY_MAX = 200; // rpm

    constexpr int ANTI_JAM_PAUSE_DURATION = 100; // msec

    constexpr double JAM_THRESHOLD = 5.0; // rpm

    // ---------- Variables ----------

    extern bool isRedAlliance;
    extern bool isColorSorting;
    extern bool isAntiJamming;
    extern bool isSkipping;
    extern bool isJamming;
    extern bool rogueBall;

    extern int antiJamPauseEndTime; // for pausing antijam
    extern intakeState currentState;

    extern PeriodicTask periodicTask;

    // ---------- Functions ----------

    void setIntakeState(intakeState state);

    void discardBall();

    void start();
    void update();
} // namespace intakeController