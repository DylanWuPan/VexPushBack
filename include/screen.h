#pragma once
#include "main.h"
#include "globals.h"
#include "auton.h"
#include "periodic-task.h"
#include "liblvgl/llemu.hpp"

namespace screenController {
    // ---------- Variables ----------
    extern int printMode;
    constexpr int MAX_PRINT_MODE = 1;
    constexpr int DELAY = 1000;

    void start();
    void update();
    extern PeriodicTask periodicTask;

    // ---------- Functions ----------
    void onCenterButton();
    void onLeftButton();
    void onRightButton();
}