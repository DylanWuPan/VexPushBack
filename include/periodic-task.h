#pragma once
#include "main.h"

class PeriodicTask {
  public:
    PeriodicTask(std::function<void()> update, int delay, char* name);
    void loop();
    void start();
    void end();
    uint32_t getTimeSinceLastUpdate();
    void setDelay(int delay);

  private:
    // For initializing the task (not the cleanest)
    static void loopWrapper(void* obj_ptr);

    std::function<void()> update;

    bool enableFlag;
    uint32_t time;
    int taskDelay;
    const char* name;
    std::optional<pros::Task> task;
};