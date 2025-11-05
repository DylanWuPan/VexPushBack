#include "intake.h"

namespace intakeController {
    bool isSkipping = false;
    bool isJamming = false;
    bool rogueBall = false;
    bool isRedAlliance = true;
    bool isColorSorting = true;
    bool isAntiJamming = true;

    PeriodicTask periodicTask{update, DELAY, "Intake Task"};

    void discardBall() {
        if(!isSkipping) {
            isSkipping = true;
            if(hopper.get_target_velocity() > 0){
                hopper.move_velocity(-HOPPER_VELOCITY);
                pros::delay(70);
                hopper.move_velocity(HOPPER_VELOCITY);
            } else{
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
        if(isColorSorting){
            switch(isRedAlliance) {
                case true: rogueBall = abs(colorSensor.get_hue() - BLUE_HUE) < 20; break;
                case false: rogueBall = abs(colorSensor.get_hue() - RED_HUE) < 20; break;
            }
            if(rogueBall && abs(intake.get_voltage()) > 0){
                discardBall();
            }
        }
        if(isAntiJamming){
            if(abs(hopper.get_actual_velocity()) == 0 && abs(hopper.get_target_velocity()) > 0){
                isJamming = true;
                if(hopper.get_target_velocity() > 0){
                    hopper.move_velocity(-HOPPER_VELOCITY);
                    pros::delay(50);
                    hopper.move_velocity(HOPPER_VELOCITY);
                } else{
                    hopper.move_velocity(HOPPER_VELOCITY);
                    pros::delay(50);
                    hopper.move_velocity(-HOPPER_VELOCITY);
                }
                isJamming = false;
            }

            if(abs(intake.get_actual_velocity()) == 0 && abs(intake.get_target_velocity()) > 0){
                isJamming = true;
                if(intake.get_target_velocity() > 0){
                    intake.move_velocity(-INTAKE_VELOCITY);
                    pros::delay(50);
                    intake.move_velocity(INTAKE_VELOCITY);
                } else{
                    intake.move_velocity(INTAKE_VELOCITY);
                    pros::delay(50);
                    intake.move_velocity(-INTAKE_VELOCITY);
                }
                isJamming = false;
            }

            if(abs(topScore.get_actual_velocity()) == 0 && abs(topScore.get_target_velocity()) > 0){
                isJamming = true;
                if(topScore.get_target_velocity() > 0){
                    topScore.move_velocity(-TOPSCORE_VELOCITY);
                    pros::delay(50);
                    topScore.move_velocity(TOPSCORE_VELOCITY);
                } else{
                    topScore.move_velocity(TOPSCORE_VELOCITY);
                    pros::delay(50);
                    topScore.move_velocity(-TOPSCORE_VELOCITY);
                }
                isJamming = false;
            }
        }
    }
}
