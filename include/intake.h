#pragma once
#include "main.h"
#include "globals.h"
#include "auton.h"
#include "periodic-task.h"

namespace intakeController {
    using namespace devices;

    // ---------- Variables ----------
    constexpr int DELAY = 5;

    bool isColorSorting;
    bool isAntiJamming;
    bool isSkipping;
    bool isJamming;
    bool rogueBall;

    extern double jamThreshold;

    extern bool isRedAlliance;
    constexpr int BLUE_HUE = 230;
    constexpr int RED_HUE = 350;
	constexpr int INTAKE_VELOCITY = 600;
	constexpr int HOPPER_VELOCITY = 200;
	constexpr int TOPSCORE_VELOCITY = 200;
    
    void discardBall();

    void start();
    void update();
    extern PeriodicTask periodicTask;
}