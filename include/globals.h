#include "main.h"

using namespace pros;
using namespace pros::v5;
#ifndef GLOBALS
#define GLOBALS

extern pros::MotorGroup left_drivetrain;
extern pros::MotorGroup right_drivetrain;
extern pros::Rotation vertical_tracking;
extern pros::Rotation horizontal_tracking;
extern pros::Controller controller;
extern pros::IMU inertial; 
extern lemlib::Chassis chassis;
extern pros::Motor intake;
extern pros::Motor hopper;
extern pros::Motor topscore;

#endif