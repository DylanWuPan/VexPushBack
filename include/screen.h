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
    // void loop();

    // constexpr char* TASK_NAME = "Screen Task";
    // extern bool enableFlag;
    // extern uint32_t time;
    // extern std::optional<pros::Task> task;
    extern PeriodicTask periodicTask;

    // ---------- Functions ----------
    void onCenterButton();
    void onLeftButton();
    void onRightButton();
}