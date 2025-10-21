#include "intake.h"

namespace intakeController {
    bool isSkipping = false;
    bool rogueBall = false;
    bool isRedAlliance = true;

    PeriodicTask periodicTask{update, DELAY, "Intake Task"};

    void discardBall() {
        if(!isSkipping){
            isSkipping = true;
            hopper.move_velocity(-HOPPER_VELOCITY);
            topScore.move_velocity(TOPSCORE_VELOCITY);
            pros::delay(50);
            hopper.move_velocity(HOPPER_VELOCITY);

            rogueBall = false;
            isSkipping = false;
        }
    }

    void start() {
        colorSensor.set_led_pwm(100);

        periodicTask.start();
    }

    void update() {
        switch(isRedAlliance) {
            case true:
                rogueBall = colorSensor.get_hue() < BLUE_HUE;
                break;
            case false:
                rogueBall = colorSensor.get_hue() > RED_HUE;
                break;
        }
        if(rogueBall && intake.get_voltage() > 0){
            discardBall();
        }
    }
}
