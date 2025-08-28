#include "main.h"

pros::MotorGroup left_drivetrain({-8, -9, 10}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::MotorGroup right_drivetrain({ 2, 3, -15}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Rotation vertical_tracking(13);
pros::Rotation horizontal_tracking(-17);
pros::Imu inertial(21);

pros::Controller controller(CONTROLLER_MASTER);