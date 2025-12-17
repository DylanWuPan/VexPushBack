#include "intake.h"

using namespace devices;

namespace intakeController {
    // ---------- Variables ----------

    bool isRedAlliance = false;
    bool isColorSorting = true;
    bool isAntiJamming = true;
    bool isSkipping = false;
    bool isJamming = false;
    bool rogueBall = false;

    int antiJamPauseEndTime = 0; // for pausing antijam/colorsort
    intakeState currentState = intakeState::Stop;

    PeriodicTask periodicTask{update, DELAY, "Intake Task"};

    // ---------- Functions ----------

    void setIntakeState(intakeState state, bool allowRepeat) {
        if (!allowRepeat && state == currentState)
            return; // only for first times
        currentState = state;
        switch (state) {
            case intakeState::Intake: {
                intake.move_velocity(intakeController::INTAKE_VELOCITY_MAX);
                hopper.move_velocity(intakeController::HOPPER_VELOCITY_MAX);
                topScore.move_velocity(-intakeController::TOPSCORE_VELOCITY_MAX);
                antiJamPauseEndTime = pros::millis() + ANTI_JAM_PAUSE_DURATION;
                break;
            }
            case intakeState::TopScore: {
                topScore.move_velocity(intakeController::TOPSCORE_VELOCITY_MAX);
                hopper.move_velocity(-0.67 * intakeController::HOPPER_VELOCITY_MAX);
                intake.move_velocity(intakeController::INTAKE_VELOCITY_MAX);
                antiJamPauseEndTime = pros::millis() + ANTI_JAM_PAUSE_DURATION;
                break;
            }
            case intakeState::MiddleScore: {
                topScore.move_velocity(-0.5 * intakeController::TOPSCORE_VELOCITY_MAX);
                hopper.move_velocity(-0.67 * intakeController::HOPPER_VELOCITY_MAX);
                intake.move_velocity(1 * intakeController::INTAKE_VELOCITY_MAX);
                antiJamPauseEndTime = pros::millis() + ANTI_JAM_PAUSE_DURATION;
                break;
            }
            case intakeState::BottomScore: {
                hopper.move_velocity(-0.67 * intakeController::HOPPER_VELOCITY_MAX);
                intake.move_velocity(-1 * intakeController::INTAKE_VELOCITY_MAX);
                antiJamPauseEndTime = pros::millis() + ANTI_JAM_PAUSE_DURATION;
                break;
            }
            case intakeState::Stop: {
                intake.move_velocity(0);
                hopper.move_velocity(0);
                topScore.move_velocity(0);
                break;
            }
        }
    }

    void discardBall() {
        if (!isSkipping) {
            isSkipping = true;
            switch (currentState) {
                case intakeState::Intake: {
                    hopper.move_velocity(-HOPPER_VELOCITY_MAX);
                    pros::delay(60);
                    setIntakeState(currentState, true);
                    break;
                }
                // case intakeState::TopScore: {
                //     pros::delay(60);
                //     topScore.move_velocity(-TOPSCORE_VELOCITY_MAX);
                //     hopper.move_velocity(0);
                //     pros::delay(100);
                //     setIntakeState(currentState, true);
                //     pros::delay(10);
                //     // antiJamPauseEndTime = pros::millis() + 60;
                //     break;
                // }
                    // case intakeState::MiddleScore: {
                    //     pros::delay(20);
                    //     topScore.move_velocity(TOPSCORE_VELOCITY_MAX);
                    //     pros::delay(30);
                    //     topScore.move_velocity(-0.5 * TOPSCORE_VELOCITY_MAX);
                    //     break;
                    // }
                    // case intakeState::BottomScore: {
                    //     intake.move_velocity(INTAKE_VELOCITY_MAX);
                    //     pros::delay(70);
                    //     intake.move_velocity(-0.67 * INTAKE_VELOCITY_MAX);
                    //     break;
                    // }
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
            switch (isRedAlliance) {
                case true:
                    rogueBall = fabs(colorSensor.get_hue() - BLUE_HUE) < 20.0;
                    break;
                case false:
                    rogueBall = fabs(colorSensor.get_hue() - RED_HUE) < 20.0;
                    break;
            }
            if (rogueBall && abs(intake.get_voltage()) > 0) {
                discardBall();
            }
        }
        if (isAntiJamming && pros::millis() >= antiJamPauseEndTime) {
            if (fabs(hopper.get_actual_velocity()) < JAM_THRESHOLD && fabs(hopper.get_target_velocity()) > JAM_THRESHOLD) {
                isJamming = true;
                int targetVelo = hopper.get_target_velocity();
                hopper.move_voltage(targetVelo > 0 ? -12000 : 12000);
                pros::delay(100);
                hopper.move_voltage(targetVelo > 0 ? 12000 : -12000);
                pros::delay(10);
                // hopper.move_velocity(targetVelo);
                setIntakeState(currentState, true);
                isJamming = false;
            }

            if (fabs(intake.get_actual_velocity()) < JAM_THRESHOLD && fabs(intake.get_target_velocity()) > JAM_THRESHOLD) {
                isJamming = true;
                int targetVelo = intake.get_target_velocity();
                intake.move_voltage(targetVelo > 0 ? -12000 : 12000);
                pros::delay(70);
                intake.move_voltage(targetVelo > 0 ? 12000 : -12000);
                pros::delay(10);
                // intake.move_velocity(targetVelo);
                setIntakeState(currentState, true);
                isJamming = false;
            }

            if (fabs(topScore.get_actual_velocity()) < JAM_THRESHOLD && fabs(topScore.get_target_velocity()) > JAM_THRESHOLD) {
                isJamming = true;
                int targetVelo = topScore.get_target_velocity();
                topScore.move_voltage(targetVelo > 0 ? -12000 : 12000);
                pros::delay(70);
                topScore.move_voltage(targetVelo > 0 ? 12000 : -12000);
                pros::delay(10);
                // topScore.move_velocity(targetVelo);
                setIntakeState(currentState, true);
                isJamming = false;
            }
        }
    }
} // namespace intakeController
