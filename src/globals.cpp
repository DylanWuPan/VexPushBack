#include "main.h"

pros::MotorGroup left_drivetrain({-1, -2, -3}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::MotorGroup right_drivetrain({ 8, 9, 10}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Rotation vertical_tracking(13);
pros::Rotation horizontal_tracking(-17);
pros::Imu inertial(20);

pros::Motor intake(-11, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor hopper(21, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor topscore(12, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);

pros::Controller controller(CONTROLLER_MASTER);