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
            pros::delay(70);
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
            case true: rogueBall = abs(colorSensor.get_hue() - BLUE_HUE) < 20; break;
            case false: rogueBall = abs(colorSensor.get_hue() - RED_HUE) < 20; break;
        }
        if(rogueBall && intake.get_voltage() > 0){
            discardBall();
        }
    }
}
