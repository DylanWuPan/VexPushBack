#include "screen.h"
#include "intake.h"

namespace screenController {
    using namespace devices;

    int printMode = 0;

    // bool enableFlag = false;
    // uint32_t time;
    // std::optional<pros::Task> task;
    PeriodicTask periodicTask{update, DELAY, "Screen Task"};

    // ---------- Functions ----------
    void onCenterButton() {
        if (++printMode > MAX_PRINT_MODE) printMode = 0;
        // update();
    }
    void onLeftButton() {
        auton::autonSelect::decrementAutonMode();
        update();
    }
    void onRightButton() {
        auton::autonSelect::incrementAutonMode();
        update();
    }

    void start() {
        pros::lcd::initialize();
        // pros::delay(100);

        pros::lcd::register_btn0_cb(onLeftButton);
        pros::lcd::register_btn1_cb(onCenterButton);
        pros::lcd::register_btn2_cb(onRightButton);

        // auton::autonSelect::printAutonMode(0);

        // pros::delay(500);

        // enableFlag = true;
        // time = pros::millis();
        // if (!task.has_value()) {
        //     task.emplace(loop, TASK_NAME);
        // }
        periodicTask.start();
    }

    // void loop() {
    //     while (true) {
    //         if (!enableFlag) return;
    //         update();

    //         // time += taskDelay;
    //         task->delay(DELAY);
    //     }
    // }

    void update() {
        for (int i = 0; i < 7; ++i) {
            pros::lcd::clear_line(i); // for some reason pros::lcd::clear makes it crash
        }
        switch (printMode) {
            case 0:
                auton::autonSelect::printAutonMode(0);
                pros::lcd::print(2, "LB: %g, LM: %g, LF: %g\n", devices::leftDrive.get_temperature(0), devices::leftDrive.get_temperature(1), devices::leftDrive.get_temperature(2));
                pros::lcd::print(3, "RB: %g, RM: %g, RF: %g\n", devices::rightDrive.get_temperature(0), devices::rightDrive.get_temperature(1), devices::rightDrive.get_temperature(2));
                pros::lcd::print(5, "Brain: %g, Cntrlr: %i\n", pros::battery::get_capacity(), devices::controller.get_battery_level());
                break;
            case 1:
                auton::autonSelect::printAutonMode(0);
                // lemlib::Pose robotPos = chassis.getPose();
                // pros::lcd::print(2, "X: %f, Y: %f", robotPos.x, robotPos.y);
                pros::lcd::print(3, "COLOR SENSOR: %f", colorSensor.get_hue());
                pros::lcd::print(4, "ROGUE BALL: %s", intakeController::rogueBall ? "TRUE" : "FALSE");
                break;
        }
    }
}