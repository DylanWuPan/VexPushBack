#include "main.h"

pros::MotorGroup left_drivetrain({-1, -2, -3}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::MotorGroup right_drivetrain({ 8, 9, 10}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

pros::Rotation vertical_tracking(20);
pros::Rotation horizontal_tracking(19);
pros::Imu inertial(21);
pros::Optical colorsensor(18);

pros::Motor intake(-11, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor hopper(-21, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
pros::Motor topscore(13, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
pros::Motor hopper2(-20, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);

pros::Controller controller(CONTROLLER_MASTER);

pros::ADIDigitalOut matchloader('H', false);
pros::ADIDigitalOut topaligner('G', false);