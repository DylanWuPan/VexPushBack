#pragma once
#include "auton.h"
#include "globals.h"
#include "liblvgl/llemu.hpp"
#include "main.h"
#include "periodic-task.h"

namespace screenController {
    // ---------- Constants ----------

    constexpr int MAX_PRINT_MODE = 2;
    constexpr int DELAYS[] = {50, 1000, 100}; // different cycle times for the different print modes

    // ---------- Variables ----------

    extern int printMode;
    extern PeriodicTask periodicTask;

    // ---------- Functions ----------

    void start();
    void update();
    void onCenterButton();
    void onLeftButton();
    void onRightButton();
} // namespace screenController