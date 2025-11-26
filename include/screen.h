#pragma once
#include "main.h"
#include "globals.h"
#include "auton.h"
#include "periodic-task.h"
#include "liblvgl/llemu.hpp"

namespace screenController {
    // ---------- Constants ----------
    
    constexpr int MAX_PRINT_MODE = 1;
    constexpr int DELAYS[] = {20, 1000, 1000}; // different cycle times for the different print modes

    // ---------- Variables ----------

    extern int printMode;
    extern PeriodicTask periodicTask;

    // ---------- Functions ----------

    void start();
    void update();
    void onCenterButton();
    void onLeftButton();
    void onRightButton();
}