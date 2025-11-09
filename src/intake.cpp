#include "intake.h"

namespace intakeController {
    bool isRedAlliance = true;
    bool isColorSorting = true;
    bool isAntiJamming = true;
    bool isSkipping = false;
    bool isJamming = false;
    bool rogueBall = false;

    double jamThreshold = 5;

    PeriodicTask periodicTask{update, DELAY, "Intake Task"};

    void discardBall() {
        if (!isSkipping) {
            isSkipping = true;
            // TODO: This isn't quite right - I think we want to discard
            // out the middle no matter which direction the hopper is spinning
            if (hopper.get_target_velocity() > 0) {
                hopper.move_velocity(-HOPPER_VELOCITY);
                pros::delay(70);
                hopper.move_velocity(HOPPER_VELOCITY);
            } else {
                hopper.move_velocity(HOPPER_VELOCITY);
                pros::delay(70);
                hopper.move_velocity(-HOPPER_VELOCITY);
            }
            rogueBall = false;
            isSkipping = false;
        }
    }

    void start() {
        colorSensor.set_led_pwm(100);

        periodicTask.start();
    }

    void update() {
        if (isColorSorting) {
            switch(isRedAlliance) {
                case true: rogueBall = fabs(colorSensor.get_hue() - BLUE_HUE) < 20; break;
                case false: rogueBall = fabs(colorSensor.get_hue() - RED_HUE) < 20; break;
            }
            if (rogueBall && abs(intake.get_voltage()) > 0) {
                discardBall();
            }
        }
        if (isAntiJamming) {
            if (fabs(hopper.get_actual_velocity()) < jamThreshold && fabs(hopper.get_target_velocity()) > jamThreshold) {
                isJamming = true;
                int targetVelo = hopper.get_target_velocity();
                hopper.move_voltage(targetVelo > 0? -12000 : 12000);
                pros::delay(40);
                hopper.move_voltage(targetVelo > 0? 12000 : -12000);
                pros::delay(10);
                hopper.move_velocity(targetVelo);
                isJamming = false;
            }

            if (fabs(intake.get_actual_velocity()) < jamThreshold && fabs(intake.get_target_velocity()) > jamThreshold) {
                isJamming = true;
                int targetVelo = intake.get_target_velocity();
                intake.move_voltage(targetVelo > 0? -12000 : 12000);
                pros::delay(40);
                intake.move_voltage(targetVelo > 0? 12000 : -12000);
                pros::delay(10);
                intake.move_velocity(targetVelo);
                isJamming = false;
            }

            if (fabs(topScore.get_actual_velocity()) < jamThreshold && fabs(topScore.get_target_velocity()) > jamThreshold) {
                isJamming = true;
                int targetVelo = topScore.get_target_velocity();
                topScore.move_voltage(targetVelo > 0? -12000 : 12000);
                pros::delay(40);
                topScore.move_voltage(targetVelo > 0? 12000 : -12000);
                pros::delay(10);
                topScore.move_velocity(targetVelo);
                isJamming = false;
            }
        }
    }
}
