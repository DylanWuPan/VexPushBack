#include "screen.h"
#include "intake.h"

namespace screenController {
    using namespace devices;

    int printMode = 0;

    PeriodicTask periodicTask{update, DELAYS[printMode], "Screen Task"};

    // ---------- Functions ----------
    void onCenterButton() {
        if (++printMode > MAX_PRINT_MODE) printMode = 0;
        periodicTask.setDelay(DELAYS[printMode]);
        update();
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

        pros::lcd::register_btn0_cb(onLeftButton);
        pros::lcd::register_btn1_cb(onCenterButton);
        pros::lcd::register_btn2_cb(onRightButton);

        periodicTask.start();
    }

    void update() {
        for (int i = 0; i < 7; ++i) {
            pros::lcd::clear_line(i); // for some reason pros::lcd::clear makes it crash
        }
        switch (printMode) {
            case 0:
                auton::autonSelect::printAutonMode(0);
                pros::lcd::print(2, "LB: %g, LM: %g, LF: %g\n", leftDrive.get_temperature(0), leftDrive.get_temperature(1), leftDrive.get_temperature(2));
                pros::lcd::print(3, "RB: %g, RM: %g, RF: %g\n", rightDrive.get_temperature(0), rightDrive.get_temperature(1), rightDrive.get_temperature(2));
                pros::lcd::print(4, "Int: %g, Hop: %g, Top: %g\n", intake.get_temperature(), hopper.get_temperature(), topScore.get_temperature());
                pros::lcd::print(5, "Brain: %g, Cntrlr: %i\n", pros::battery::get_capacity(), controller.get_battery_level());
                break;
            case 1:
                auton::autonSelect::printAutonMode(0);
                lemlib::Pose robotPos = chassis.getPose();
                pros::lcd::print(2, "X: %f, Y: %f", robotPos.x, robotPos.y);
                pros::lcd::print(3, "COLOR SENSOR: %f", colorSensor.get_hue());
                pros::lcd::print(4, "ROGUE BALL: %s", intakeController::rogueBall ? "TRUE" : "FALSE");
                break;
        }
    }
}