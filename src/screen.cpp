#include "screen.h"
#include "custom-utilities.h"
#include "intake.h"
#include "localization.h"

using namespace devices;
using namespace utilities;

namespace screenController {
    // ---------- Variables ----------

    int printMode = 2;
    PeriodicTask periodicTask{update, DELAYS[printMode], "Screen Task"};

    // ---------- Functions ----------

    void onCenterButton() {
        if (++printMode > MAX_PRINT_MODE)
            printMode = 0;
        periodicTask.setDelay(DELAYS[printMode]);
        update();
    }
    void onLeftButton() {
        // auton::autonSelect::decrementAutonMode();
        intakeController::isRedAlliance = !intakeController::isRedAlliance;
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
        switch (printMode) {
            case 0: {
                for (int i = 0; i < 8; ++i) {
                    pros::lcd::clear_line(i); // for some reason pros::lcd::clear makes it crash
                }
                auton::autonSelect::printAutonMode(0);
                lemlib::Pose robotPos = chassis.getPose();
                pros::lcd::print(2, "Angle: %g, X: %f, Y: %f", robotPos.theta, robotPos.x, robotPos.y);
                pros::lcd::print(3, "Color: %f", colorSensor.get_hue());
                pros::lcd::print(4, "Lat: %g, Vert: %g", latTracker.get_position() * 0.01, vertTracker.get_position() * 0.01);
                pros::lcd::print(5, "DIST FRONT: %f  BACK: %f", getDistance(distanceSensor::Front), getDistance(distanceSensor::Back));
                pros::lcd::print(6, "DIST RIGHT: %f  LEFT: %f", getDistance(distanceSensor::Right), getDistance(distanceSensor::Left));
                break;
            }
            case 1: {
                for (int i = 0; i < 8; ++i) {
                    pros::lcd::clear_line(i); // for some reason pros::lcd::clear makes it crash
                }
                auton::autonSelect::printAutonMode(0);
                pros::lcd::print(2, "LB: %g, LM: %g, LF: %g\n", leftDrive.get_temperature(0), leftDrive.get_temperature(1), leftDrive.get_temperature(2));
                pros::lcd::print(3, "RB: %g, RM: %g, RF: %g\n", rightDrive.get_temperature(0), rightDrive.get_temperature(1), rightDrive.get_temperature(2));
                pros::lcd::print(4, "Int: %g, Hop: %g, Top: %g\n", intake.get_temperature(), hopper.get_temperature(), topScore.get_temperature());
                pros::lcd::print(5, "Brain: %g, Cntrlr: %i\n", pros::battery::get_capacity(), controller.get_battery_level());
                break;
            }
            case 2: {
                // Blank screen for other prints
                // pros::lcd::clear_line(5);
                // pros::lcd::clear_line(6);
                // pros::lcd::clear_line(7);

                // lemlib::Pose robotPos = chassis.getPose();
                // pros::lcd::print(4, "x: %g, y: %g, angle: %g", round(robotPos.x * 100) * 0.01, round(robotPos.y * 100) * 0.01, round(robotPos.theta * 100) * 0.01);
                // // localization::logLocalization(5 );
                // pros::lcd::print(6, "DIST FRONT: %f  BACK: %f", getDistance(distanceSensor::Front), getDistance(distanceSensor::Back));
                // pros::lcd::print(7, "DIST RIGHT: %f  LEFT: %f", getDistance(distanceSensor::Right), getDistance(distanceSensor::Left));
            }
        }
    }
} // namespace screenController