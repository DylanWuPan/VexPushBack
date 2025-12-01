#include "periodic-task.h"

void PeriodicTask::loopWrapper(void* obj_ptr) {
    PeriodicTask* instance = static_cast<PeriodicTask*>(obj_ptr);
    instance->loop();
}

PeriodicTask::PeriodicTask(std::function<void()> update, int delay, const char* name)
    : update{update}, enableFlag{false}, time{0}, name{name}, taskDelay{delay} {}

void PeriodicTask::loop() {
    while (true) {
        if (!enableFlag)
            return;
        update();

        task->delay_until(&time, taskDelay);
    }
}

void PeriodicTask::start() {
    enableFlag = true;
    time = pros::millis();

    if (!task.has_value()) {
        task.emplace(loopWrapper, this, name);
    }
}

void PeriodicTask::end() {
    enableFlag = false;
}

uint32_t PeriodicTask::getTimeSinceLastUpdate() {
    return pros::millis() - time;
}

void PeriodicTask::setDelay(int delay) {
    taskDelay = delay;
}