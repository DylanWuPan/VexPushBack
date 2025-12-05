#include "auton.h"
#include "custom-utilities.h"
#include "globals.h"
#include "intake.h"
#include "localization.h"
#include "main.h"

using namespace devices;

namespace auton {
    // Auton Routes
    // void autonTest() {
    //     // localization::start(55.75, 22.75, 0); // like SAWP Auton

    //     // chassis.moveToPoint(46, 55, 1000, {.maxSpeed = 80});
    //     // intakeController::setIntakeState(intakeController::intakeState::Intake);
    // }

    void autonSkills2() {
        intakeController::isColorSorting = false;

        chassis.setPose(58, 22, -90);

        // FIRST LOADER
        chassis.moveToPoint(24, 22, 4000, {.maxSpeed = 80});
        chassis.turnToHeading(180, 500, {.maxSpeed = 80});
        intakeController::setIntakeState(intakeController::intakeState::Intake);
        matchLoader.set_value(true);
        chassis.moveToPoint(24, 7.5, 2500, {.maxSpeed = 80});
        pros::delay(2500);

        // FIRST LONG GOAL
        chassis.moveToPoint(24, 22, 4000, {.forwards = false, .maxSpeed = 80});
        chassis.turnToHeading(0, 1000, {.maxSpeed = 80});
        topAligner.set_value(true);
        matchLoader.set_value(false);
        pros::delay(1100);
        chassis.setPose(utilities::getPoseWithDistance(false, false, false, true));
        // pros::delay(100);
        chassis.moveToPose(23, 41.5, 0, 2000);
        pros::delay(300);
        intakeController::setIntakeState(intakeController::intakeState::TopScore);
        pros::delay(3000);
        chassis.setPose(24, 39, chassis.getPose().theta);
        pros::delay(1000);

        // SECOND LOADER
        intakeController::setIntakeState(intakeController::intakeState::Intake);
        chassis.moveToPoint(24, 28, 4000, {.forwards = false, .maxSpeed = 80});
        topAligner.set_value(false);
        chassis.turnToHeading(90, 1000, {.maxSpeed = 80});
        // chassis.moveToPoint(110, 28, 5000, {.maxSpeed = 80});
        chassis.moveToPoint(121.5, 28, 5000, {.maxSpeed = 80});
        pros::delay(1500);
        chassis.setPose(utilities::getPoseWithDistance(true, true, false, false));
        // pros::delay(100);
        // chassis.moveToPoint(121.5, 28, 5000, {.maxSpeed = 80});
        chassis.turnToHeading(180, 1000, {.maxSpeed = 80});
        matchLoader.set_value(true);
        chassis.moveToPoint(121.5, 4.5, 2000, {.maxSpeed = 80});
        pros::delay(2000);
        chassis.moveToPoint(121.5, 3, 500, {.maxSpeed = 20});
        pros::delay(500);

        // SECOND LONG GOAL
        chassis.moveToPoint(121.5, 20, 4000, {.forwards = false, .maxSpeed = 80});
        chassis.turnToHeading(0, 1000, {.maxSpeed = 80});
        topAligner.set_value(true);
        matchLoader.set_value(false);
        pros::delay(1200);
        chassis.setPose(utilities::getPoseWithDistance(false, true, false, false));
        // pros::delay(100);
        chassis.moveToPose(119.5, 44, 0, 2000);
        pros::delay(500);
        intakeController::setIntakeState(intakeController::intakeState::TopScore);
        pros::delay(2500);
        chassis.moveToPoint(119.5, 45, 400, {.maxSpeed = 20});
        pros::delay(500);
        chassis.setPose(120, 39, chassis.getPose().theta);
        pros::delay(500);

        // ALLEY
        intakeController::setIntakeState(intakeController::intakeState::Intake);
        topAligner.set_value(false);
        chassis.moveToPoint(120, 25, 4000, {.forwards = false, .maxSpeed = 80});
        chassis.moveToPose(133, 52, 0, 4000);
        pros::delay(2000);
        chassis.setPose(utilities::getPoseWithDistance(false, true, false, false));
        // pros::delay(100);
        chassis.moveToPoint(131, 105, 4000, {.maxSpeed = 80});
        pros::delay(1500);
        chassis.setPose(utilities::getPoseWithDistance(true, true, false, false));
        pros::delay(100);

        // THIRD LOADER
        chassis.moveToPoint(116.5, 120, 4000, {.maxSpeed = 80});
        chassis.turnToHeading(0, 1000, {.maxSpeed = 80});
        matchLoader.set_value(true);
        topAligner.set_value(false);
        chassis.moveToPoint(116.5, 137, 2000, {.maxSpeed = 80});
        pros::delay(2000);
        chassis.moveToPoint(116.5, 140, 500, {.maxSpeed = 20});
        pros::delay(500);

        // THIRD GOAL
        chassis.moveToPoint(117, 124, 4000, {.forwards = false, .maxSpeed = 80});
        chassis.turnToHeading(179, 1000, {.maxSpeed = 80});
        topAligner.set_value(true);
        matchLoader.set_value(false);
        pros::delay(1100);
        chassis.setPose(utilities::getPoseWithDistance(false, false, false, true));
        // pros::delay(100);
        chassis.moveToPose(120.5, 102, 180, 4000);
        pros::delay(500);
        intakeController::setIntakeState(intakeController::intakeState::TopScore);
        pros::delay(1500);
        chassis.moveToPoint(120.5, 100, 500, {.maxSpeed = 20});
        pros::delay(500);
        chassis.setPose(120, 105, chassis.getPose().theta);
        pros::delay(500);

        // FOURTH LOADER
        intakeController::setIntakeState(intakeController::intakeState::Intake);
        chassis.moveToPoint(120, 112, 4000, {.forwards = false, .maxSpeed = 80});
        topAligner.set_value(false);
        chassis.turnToHeading(-90, 1000, {.maxSpeed = 80});
        chassis.moveToPoint(21.5, 112, 5000, {.maxSpeed = 80});
        pros::delay(1500);
        chassis.setPose(utilities::getPoseWithDistance(true, true, false, false));
        // pros::delay(100);
        chassis.turnToHeading(0, 1000, {.maxSpeed = 80});
        matchLoader.set_value(true);
        chassis.moveToPoint(21.5, 141, 2000, {.maxSpeed = 80});
        pros::delay(2000);
        chassis.moveToPoint(21.5, 144, 1000, {.maxSpeed = 20});
        pros::delay(1000);

        // FOURTH LONG GOAL
        chassis.moveToPoint(21.5, 120, 4000, {.forwards = false, .maxSpeed = 80});
        chassis.turnToHeading(180, 1000, {.maxSpeed = 80});
        topAligner.set_value(true);
        matchLoader.set_value(false);
        pros::delay(1100);
        chassis.setPose(utilities::getPoseWithDistance(false, true, false, false));
        // pros::delay(100);
        chassis.moveToPose(25, 98, 180, 2000);
        pros::delay(500);
        intakeController::setIntakeState(intakeController::intakeState::TopScore);
        pros::delay(2500);
        chassis.moveToPoint(25, 97, 400, {.maxSpeed = 20});
        pros::delay(1000);
        chassis.setPose(24, 105, chassis.getPose().theta);
        pros::delay(500);

        // PARK
        chassis.moveToPoint(24, 120, 4000, {.forwards = false, .maxSpeed = 80});
        // chassis.moveToPose(72, 140, 90, 100000, {.forwards = false, .minSpeed = 100});
        chassis.moveToPose(72, 120, 0, 4000, {.maxSpeed = 80});
        chassis.moveToPoint(72, 140, 100000, {.minSpeed = 100});
        pros::delay(2000);
        matchLoader.set_value(true);

        pros::delay(5000);
    }

    void autonSkills() {
        intakeController::isColorSorting = false;

        chassis.setPose(86, 22, 90);
        // chassis.setPose(utilities::getPoseWithDistance(true, true, false, false));

        // FIRST LOADER
        chassis.moveToPoint(120, 22, 4000, {.maxSpeed = 80});
        chassis.turnToHeading(180, 500, {.maxSpeed = 80});
        intakeController::setIntakeState(intakeController::intakeState::Intake);
        matchLoader.set_value(true);
        chassis.moveToPoint(120, 10.5, 2500, {.maxSpeed = 80});
        pros::delay(1500);
        chassis.moveToPoint(120, 9, 500, {.maxSpeed = 20});
        pros::delay(500);
        chassis.moveToPoint(120, 9, 500, {.maxSpeed = 20});
        pros::delay(500);

        // FIRST LONG GOAL
        chassis.moveToPoint(120, 22, 4000, {.forwards = false, .maxSpeed = 80});
        chassis.turnToHeading(0, 1000, {.maxSpeed = 80});
        topAligner.set_value(true);
        matchLoader.set_value(false);
        pros::delay(1100);
        chassis.setPose(utilities::getPoseWithDistance(false, true, false, false));
        // pros::delay(100);
        chassis.moveToPose(121, 41.5, 0, 2000);
        pros::delay(300);
        intakeController::setIntakeState(intakeController::intakeState::TopScore);
        pros::delay(2000);
        chassis.setPose(120, 39, chassis.getPose().theta);
        pros::delay(1000);

        // ALLEY
        intakeController::setIntakeState(intakeController::intakeState::Intake);
        topAligner.set_value(false);
        chassis.moveToPoint(120, 25, 4000, {.forwards = false, .maxSpeed = 80});
        wing.set_value(true);
        chassis.moveToPose(134, 52, 0, 4000);
        pros::delay(2000);
        chassis.setPose(utilities::getPoseWithDistance(false, true, false, false));
        // pros::delay(100);
        chassis.moveToPoint(132, 105, 4000, {.maxSpeed = 80});
        pros::delay(1500);
        chassis.setPose(utilities::getPoseWithDistance(true, true, false, false));
        pros::delay(100);

        // SECOND LOADER
        chassis.moveToPoint(119, 120, 4000, {.maxSpeed = 80});
        chassis.turnToHeading(0, 1000, {.maxSpeed = 80});
        matchLoader.set_value(true);
        topAligner.set_value(false);
        chassis.moveToPoint(119, 135, 2000, {.maxSpeed = 80});
        pros::delay(1500);
        chassis.moveToPoint(119, 137, 500, {.maxSpeed = 20});
        pros::delay(500);
        chassis.moveToPoint(119, 137, 500, {.maxSpeed = 20});
        pros::delay(500);

        // SECOND GOAL
        chassis.moveToPoint(121.5, 128, 4000, {.forwards = false, .maxSpeed = 80});
        chassis.turnToHeading(180, 1000, {.direction = lemlib::AngularDirection::CW_CLOCKWISE, .maxSpeed = 80});
        topAligner.set_value(true);
        matchLoader.set_value(false);
        pros::delay(1100);
        chassis.setPose(utilities::getPoseWithDistance(false, false, false, true));
        // pros::delay(100);
        chassis.moveToPose(121.5, 102, 180, 4000);
        pros::delay(500);
        intakeController::setIntakeState(intakeController::intakeState::TopScore);
        pros::delay(500);
        chassis.moveToPoint(121.5, 100, 500, {.maxSpeed = 20});
        pros::delay(500);
        chassis.setPose(121.5, 105, chassis.getPose().theta);
        pros::delay(500);

        // THIRD LOADER
        intakeController::setIntakeState(intakeController::intakeState::Intake);
        chassis.moveToPoint(120, 112, 4000, {.forwards = false, .maxSpeed = 80});
        topAligner.set_value(false);
        chassis.turnToHeading(-90, 1000, {.maxSpeed = 80});
        chassis.moveToPoint(21.5, 112, 5000, {.maxSpeed = 80});
        pros::delay(1500);
        chassis.setPose(utilities::getPoseWithDistance(true, true, false, false));
        // pros::delay(100);
        chassis.turnToHeading(0, 1000, {.maxSpeed = 80});
        matchLoader.set_value(true);
        chassis.moveToPoint(21.5, 135, 2000, {.maxSpeed = 80});
        pros::delay(2000);
        chassis.moveToPoint(21.5, 137, 500, {.maxSpeed = 20});
        pros::delay(500);
        chassis.moveToPoint(21.5, 137, 500, {.maxSpeed = 20});
        pros::delay(500);

        // THIRD LONG GOAL
        chassis.moveToPoint(23.25, 120, 4000, {.forwards = false, .maxSpeed = 80});
        chassis.turnToHeading(180, 1000, {.maxSpeed = 80});
        topAligner.set_value(true);
        matchLoader.set_value(false);
        pros::delay(1100);
        chassis.setPose(utilities::getPoseWithDistance(false, true, false, false));
        // pros::delay(100);
        chassis.moveToPose(25, 98, 180, 2000);
        pros::delay(500);
        intakeController::setIntakeState(intakeController::intakeState::TopScore);
        pros::delay(500);
        chassis.moveToPoint(25, 97, 400, {.maxSpeed = 20});
        pros::delay(500);
        chassis.setPose(24, 105, chassis.getPose().theta);
        pros::delay(500);

        // ALLEY
        intakeController::setIntakeState(intakeController::intakeState::Intake);
        topAligner.set_value(false);
        chassis.moveToPoint(24, 119, 4000, {.forwards = false, .maxSpeed = 80});
        // wing.set_value(true);
        chassis.moveToPose(13, 92, 180, 4000);
        pros::delay(2000);
        chassis.setPose(utilities::getPoseWithDistance(false, true, false, false));
        // pros::delay(100);
        chassis.moveToPoint(15, 39, 4000, {.maxSpeed = 80});
        pros::delay(1500);
        chassis.setPose(utilities::getPoseWithDistance(true, true, false, false));
        pros::delay(100);

        // FOURTH LOADER
        chassis.moveToPoint(24, 24, 4000, {.maxSpeed = 80});
        chassis.turnToHeading(180, 1000, {.maxSpeed = 80});
        matchLoader.set_value(true);
        topAligner.set_value(false);
        chassis.moveToPoint(24, 9, 2000, {.maxSpeed = 80});
        pros::delay(1500);
        chassis.moveToPoint(24, 7, 500, {.maxSpeed = 20});
        pros::delay(500);
        chassis.moveToPoint(24, 7, 500, {.maxSpeed = 20});
        pros::delay(500);

        // FOURTH GOAL
        chassis.moveToPoint(24, 20, 4000, {.forwards = false, .maxSpeed = 80});
        chassis.turnToHeading(-1, 1000, {.direction = lemlib::AngularDirection::CW_CLOCKWISE, .maxSpeed = 80});
        topAligner.set_value(true);
        matchLoader.set_value(false);
        pros::delay(1100);
        chassis.setPose(utilities::getPoseWithDistance(false, false, false, true));
        // pros::delay(100);
        chassis.moveToPose(24, 42, 0, 4000);
        pros::delay(500);
        intakeController::setIntakeState(intakeController::intakeState::TopScore);
        pros::delay(500);
        chassis.moveToPoint(24, 44, 500, {.maxSpeed = 20});
        pros::delay(500);
        chassis.setPose(24, 39, chassis.getPose().theta);
        pros::delay(500);

        // PARK
        chassis.moveToPose(40, 24, 90, 4000, {.forwards = false, .maxSpeed = 80});
        // chassis.turnToHeading(90, 4000, {.maxSpeed = 80});
        chassis.moveToPose(72, 4, 90, 100000, {.minSpeed = 100});
        pros::delay(2000);
        matchLoader.set_value(true);

        pros::delay(5000);
    }

    void autonSAWP2() {
        chassis.setPose(55.75, 22.75, 0);

        // 3 BALLS
        chassis.moveToPoint(46, 55, 1000, {.maxSpeed = 80});
        intakeController::setIntakeState(intakeController::intakeState::Intake);
        pros::delay(600);
        matchLoader.set_value(true);

        // HIGH MID
        chassis.moveToPose(56.5, 62.5, 55, 2000);
        // intakeController::setIntakeState(intakeController::intakeState::Intake);
        pros::delay(1100);
        intakeController::setIntakeState(intakeController::intakeState::MiddleScore);
        pros::delay(1400);

        // LOW MID
        chassis.moveToPoint(48, 54, 4000, {.forwards = false, .maxSpeed = 120});
        intakeController::setIntakeState(intakeController::intakeState::Intake);
        matchLoader.set_value(false);
        chassis.moveToPose(81, 65, -30, 3000);
        pros::delay(1300);
        intakeController::setIntakeState(intakeController::intakeState::BottomScore);
        pros::delay(1700);

        // MATCH LOAD
        chassis.moveToPoint(122, 24, 4000, {.forwards = false, .maxSpeed = 120});
        intakeController::setIntakeState(intakeController::intakeState::Intake);
        chassis.turnToHeading(180, 1000, {.maxSpeed = 120});
        matchLoader.set_value(true);
        chassis.moveToPoint(122, 9, 1100, {.maxSpeed = 120});
        pros::delay(1200);
        chassis.moveToPoint(122, 24, 4000, {.forwards = false, .maxSpeed = 120});

        // LONG GOAL
        chassis.moveToPose(122.5, 46, 0, 4000);
        topAligner.set_value(true);
        pros::delay(500);
        matchLoader.set_value(false);
        pros::delay(500);
        intakeController::setIntakeState(intakeController::intakeState::TopScore);
        pros::delay(70);
        // intakeController::setIntakeState(intakeController::intakeState::TopScore);

        pros::delay(5000);
    }

    void autonSAWP() {
        chassis.setPose(55.5, 22, 270);

        // Match load
        chassis.moveToPoint(23, 22, 4000, {.maxSpeed = 80, .earlyExitRange = 0.2});
        // chassis.turnToHeading(180, 500, {.maxSpeed = 80});
        chassis.moveToPoint(22, 7, 1200, {.minSpeed = 60});
        matchLoader.set_value(true);
        intakeController::setIntakeState(intakeController::intakeState::Intake);
        pros::delay(1200);

        // Long goal
        chassis.moveToPoint(22, 24, 2000, {.forwards = false});
        chassis.moveToPose(19.5, 40.5, 1, 3000);
        pros::delay(500);
        topAligner.set_value(true);
        matchLoader.set_value(false);
        pros::delay(200);
        intakeController::setIntakeState(intakeController::intakeState::TopScore);
        pros::delay(1000);
        intakeController::setIntakeState(intakeController::intakeState::Intake);

        // MidGoal
        chassis.moveToPoint(19.5, 24, 4000, {.forwards = false});
        chassis.moveToPose(54.5, 62.5, 46, 3000, {.maxSpeed = 80});
        topAligner.set_value(false);
        pros::delay(800);
        matchLoader.set_value(true);
        intakeController::setIntakeState(intakeController::intakeState::MiddleScore);
        pros::delay(500);
        intakeController::setIntakeState(intakeController::intakeState::Intake);

        chassis.moveToPoint(48, 48, 4000, {.forwards = false, .minSpeed = 60, .earlyExitRange = 1});
        matchLoader.set_value(false);

        chassis.moveToPoint(96, 54, 4000, {.minSpeed = 40, .earlyExitRange = 1});
        pros::delay(1000);
        matchLoader.set_value(true);

        // SECOND LONG GOAL
        chassis.moveToPoint(120, 36, 4000, {.minSpeed = 40, .earlyExitRange = 1});
        matchLoader.set_value(false);
        chassis.moveToPose(122, 45, 0, 5000, {.maxSpeed = 80});
        pros::delay(500);
        topAligner.set_value(true);
        pros::delay(500);
        intakeController::setIntakeState(intakeController::intakeState::TopScore);

        pros::delay(5000);
    }

    void autonLongMiddleLeft() {
        chassis.setPose(55.5, 22, 270);

        // Match load
        chassis.moveToPoint(24, 22, 4000, {.maxSpeed = 80});
        chassis.turnToHeading(180, 550, {.maxSpeed = 80});
        matchLoader.set_value(true);
        intakeController::setIntakeState(intakeController::intakeState::Intake);
        chassis.moveToPoint(22, 3, 1200, {.minSpeed = 120});
        pros::delay(1200);

        // Long goal
        chassis.moveToPoint(22, 24, 2000, {.forwards = false});
        chassis.moveToPose(20, 40.5, 1, 3000);
        pros::delay(500);
        topAligner.set_value(true);
        pros::delay(100);
        matchLoader.set_value(false);
        pros::delay(400);
        intakeController::setIntakeState(intakeController::intakeState::TopScore);
        pros::delay(2200);
        chassis.moveToPoint(20, 42, 500);

        // // DESCORE
        // chassis.moveToPoint(20, 30, 4000, {.forwards = false, .minSpeed = 80, .earlyExitRange = 2});
        // pros::delay(200);
        topAligner.set_value(false);
        // chassis.moveToPoint(20, 40.5, 2000, {.minSpeed = 120});

        // MidGoal
        chassis.moveToPoint(20, 24, 4000, {.forwards = false});
        intakeController::setIntakeState(intakeController::intakeState::Intake);
        topAligner.set_value(false);
        chassis.moveToPose(54.5, 62, 47, 6000, {.maxSpeed = 50});
        pros::delay(2500);
        intakeController::setIntakeState(intakeController::intakeState::MiddleScore);

        pros::delay(5000);
    }

    void autonLongMiddleRight() {
        chassis.setPose(88.5, 22, 90);
        chassis.setPose(utilities::getPoseWithDistance(true, true, false, false));

        // Match load
        chassis.moveToPoint(121, 22, 4000, {.maxSpeed = 80});
        chassis.turnToHeading(180, 500, {.maxSpeed = 80});
        matchLoader.set_value(true);
        intakeController::setIntakeState(intakeController::intakeState::Intake);
        chassis.moveToPoint(122, 3, 1200 /*, {.minSpeed = 60}*/);
        pros::delay(1050);

        // Long goal
        chassis.moveToPoint(122, 24, 1000, {.forwards = false});
        pros::delay(1100);
        chassis.setPose(utilities::getPoseWithDistance(false, false, false, true));
        chassis.moveToPose(120, 40.5, 1, 3000);
        pros::delay(500);
        topAligner.set_value(true);
        pros::delay(100);
        matchLoader.set_value(false);
        pros::delay(400);
        intakeController::setIntakeState(intakeController::intakeState::TopScore);
        pros::delay(2000);
        chassis.moveToPoint(120, 42, 500, {.maxSpeed = 20});
        pros::delay(550);
        chassis.setPose(120, 39, chassis.getPose().theta);

        // DESCORE
        // chassis.moveToPoint(124, 30, 4000, {.forwards = false, .maxSpeed = 80});
        // pros::delay(200);
        // topAligner.set_value(false);
        // chassis.moveToPoint(124, 40.5, 2000, {.minSpeed = 120});

        // MidGoal
        chassis.moveToPoint(120, 24, 1000, {.forwards = false});
        pros::delay(1050);
        chassis.setPose(utilities::getPoseWithDistance(false, true, true, false));
        intakeController::setIntakeState(intakeController::intakeState::Intake);
        topAligner.set_value(false);
        chassis.moveToPose(82, 63, -45, 6000, {.maxSpeed = 40});
        pros::delay(3000);
        intakeController::setIntakeState(intakeController::intakeState::BottomScore);

        pros::delay(5000);
    }

    void autonMiddleLongLeft() {
        chassis.setPose(55.75, 22.75, 0);
        chassis.setPose(utilities::getPoseWithDistance(false, false, true, true));

        // 3 BALLS
        chassis.moveToPoint(46, 55, 4000, {.maxSpeed = 50});
        intakeController::setIntakeState(intakeController::intakeState::Intake);
        pros::delay(1400);
        matchLoader.set_value(true);

        // MIDDLE GOAL
        chassis.moveToPose(61, 62, 45, 4000, {.maxSpeed = 60});
        pros::delay(1000);
        matchLoader.set_value(false);
        pros::delay(1000);
        intakeController::setIntakeState(intakeController::intakeState::BottomScore);
        pros::delay(2000);
        intakeController::setIntakeState(intakeController::intakeState::Intake);

        // MATCHLOAD
        chassis.moveToPoint(24, 24, 4000, {.forwards = false, .maxSpeed = 80});
        chassis.turnToHeading(180, 1000, {.maxSpeed = 80});
        pros::delay(1050);
        matchLoader.set_value(true);
        chassis.setPose(utilities::getPoseWithDistance(false, true, false, false));
        chassis.moveToPoint(24, 10, 1100);
        pros::delay(1100);

        // LONG GOAL
        chassis.moveToPoint(22, 24, 1000, {.forwards = false});
        pros::delay(1100);
        chassis.setPose(utilities::getPoseWithDistance(false, true, false, false));
        chassis.moveToPose(24, 40.5, -1, 3000);
        pros::delay(500);
        topAligner.set_value(true);
        pros::delay(100);
        matchLoader.set_value(false);
        pros::delay(400);
        intakeController::setIntakeState(intakeController::intakeState::TopScore);

        pros::delay(5000);
    }

    void autonMiddleLongRight() {
        chassis.setPose(88.25, 22.75, 0);
        chassis.setPose(utilities::getPoseWithDistance(false, true, true, false));

        // 3 BALLS
        chassis.moveToPoint(98, 55, 4000, {.maxSpeed = 80});
        intakeController::setIntakeState(intakeController::intakeState::Intake);
        pros::delay(600);
        matchLoader.set_value(true);

        // MIDDLE GOAL
        chassis.moveToPose(84.25, 60.75, -45, 2100);
        pros::delay(1000);
        matchLoader.set_value(false);
        pros::delay(100);
        intakeController::setIntakeState(intakeController::intakeState::BottomScore);
        pros::delay(1000);
        intakeController::setIntakeState(intakeController::intakeState::Intake);

        // MATCHLOAD
        chassis.moveToPoint(120, 24, 4000, {.forwards = false, .maxSpeed = 80});
        chassis.turnToHeading(180, 1000, {.maxSpeed = 80});
        pros::delay(700);
        matchLoader.set_value(true);
        pros::delay(350);
        chassis.setPose(utilities::getPoseWithDistance(true, false, false, true));
        chassis.moveToPoint(120, 10, 1100);
        pros::delay(1100);

        // LONG GOAL
        chassis.moveToPoint(122, 24, 1000, {.forwards = false});
        pros::delay(1100);
        chassis.setPose(utilities::getPoseWithDistance(false, false, false, true));
        chassis.moveToPose(120.5, 41.5, 1, 3000);
        pros::delay(500);
        topAligner.set_value(true);
        pros::delay(100);
        matchLoader.set_value(false);
        pros::delay(100);
        intakeController::setIntakeState(intakeController::intakeState::TopScore);
        pros::delay(1500);
        chassis.setPose(120, 39, chassis.getPose().theta);

        // WINGS
        chassis.moveToPoint(106, 32, 4000, {.forwards = false, .maxSpeed = 80});
        intakeController::setIntakeState(intakeController::intakeState::Intake);
        topAligner.set_value(false);
        chassis.turnToHeading(2, 500, {.maxSpeed = 80});
        wing.set_value(true);
        chassis.moveToPose(107, 61.5, 0, 10000, {.maxSpeed = 60});
        wing.set_value(false);

        pros::delay(5000);
    }

    void autonLeft7Long() {
        chassis.setPose(55.75, 22.75, 0);

        // 3 BALLS
        chassis.moveToPoint(46, 55, 4000, {.maxSpeed = 50});
        intakeController::setIntakeState(intakeController::intakeState::Intake);
        pros::delay(1400);
        matchLoader.set_value(true);

        // MATCHLOAD
        chassis.moveToPoint(22, 22, 4000, {.maxSpeed = 80});
        chassis.turnToHeading(180, 500, {.maxSpeed = 80});
        chassis.moveToPoint(21, 8, 1100, {.maxSpeed = 120});
        pros::delay(1100);

        // LONG GOAL
        chassis.moveToPoint(21, 24, 4000, {.forwards = false, .maxSpeed = 80});
        chassis.moveToPose(20, 43, 0, 4000, {.maxSpeed = 80});
        pros::delay(500);
        topAligner.set_value(true);
        pros::delay(100);
        matchLoader.set_value(false);
        pros::delay(400);
        intakeController::setIntakeState(intakeController::intakeState::TopScore);
        pros::delay(3000);
        chassis.moveToPoint(20, 45, 500);

        // WINGS
        wing.set_value(true);
        intakeController::setIntakeState(intakeController::intakeState::Intake);
        chassis.moveToPoint(20, 30, 4000, {.forwards = false, .maxSpeed = 80});
        chassis.moveToPose(6.5, 45, 1, 4000, {.maxSpeed = 80});
        topAligner.set_value(false);
        // chassis.turnToHeading(1, 500, {.maxSpeed = 80});
        wing.set_value(false);
        chassis.moveToPoint(7, 63, 10000, {.maxSpeed = 60});

        pros::delay(5000);
    }

    void autonRight7Long() {
        chassis.setPose(88.25, 22.75, 0);

        // 3 BALLS
        chassis.moveToPoint(98, 55, 4000, {.maxSpeed = 50});
        intakeController::setIntakeState(intakeController::intakeState::Intake);
        pros::delay(1500);
        matchLoader.set_value(true);

        // MATCHLOAD
        chassis.moveToPoint(123, 22, 4000, {.maxSpeed = 80});
        chassis.turnToHeading(180, 500, {.maxSpeed = 80});
        chassis.moveToPoint(124.5, 10, 1100, {.maxSpeed = 120});
        pros::delay(1100);

        // LONG GOAL
        chassis.moveToPoint(123.5, 24, 4000, {.forwards = false, .maxSpeed = 80});
        chassis.moveToPose(124.5, 43, 0, 4000, {.maxSpeed = 80});
        pros::delay(500);
        topAligner.set_value(true);
        pros::delay(100);
        matchLoader.set_value(false);
        pros::delay(400);
        intakeController::setIntakeState(intakeController::intakeState::TopScore);
        pros::delay(3700);
        chassis.moveToPoint(124, 45, 500);

        // WINGS
        chassis.moveToPoint(113, 32, 4000, {.forwards = false, .maxSpeed = 80});
        intakeController::setIntakeState(intakeController::intakeState::Intake);
        topAligner.set_value(false);
        chassis.turnToHeading(4, 500, {.maxSpeed = 80});
        chassis.moveToPoint(114, 66, 10000, {.maxSpeed = 60});

        pros::delay(5000);
    }
} // namespace auton

// FOR SELECTING AUTON MODE BEFORE MATCH
namespace auton::autonSelect {
    autonMode mode(autonMode::MIDDLE_LONG_RIGHT);

    void printAutonMode(int line) {
        switch (mode) {
            case autonMode::SKILLS: {
                pros::lcd::set_text(line, "Auton mode: Skills");
                break;
            }
            case autonMode::SAWP: {
                pros::lcd::set_text(line, "Auton mode: SAWP");
                break;
            }
            case autonMode::MIDDLE_LONG_LEFT: {
                pros::lcd::set_text(line, "Auton mode: Middle Long Left");
                break;
            }
            case autonMode::MIDDLE_LONG_RIGHT: {
                pros::lcd::set_text(line, "Auton mode: Middle Long Right");
                break;
            }
            case autonMode::LONG_MIDDLE_LEFT: {
                pros::lcd::set_text(line, "Auton mode: Long Middle Left");
                break;
            }
            case autonMode::LONG_MIDDLE_RIGHT: {
                pros::lcd::set_text(line, "Auton mode: Long Middle Right");
                break;
            }
            case autonMode::LEFT_7_LONG: {
                pros::lcd::set_text(line, "Auton mode: Left 7 Long");
                break;
            }
            case autonMode::RIGHT_7_LONG: {
                pros::lcd::set_text(line, "Auton mode: Right 7 Long");
                break;
            }
        }        
        pros::lcd::print(line + 1, "Alliance: %s", intakeController::isRedAlliance ? "RED" : "BLUE");
    }
    void incrementAutonMode() {
        mode = static_cast<autonMode>((static_cast<int>(mode) + 1) % NUM_AUTONS);
    }
    void decrementAutonMode() {
        mode = static_cast<autonMode>((static_cast<int>(mode) - 1) % NUM_AUTONS);
    }
} // namespace auton::autonSelect