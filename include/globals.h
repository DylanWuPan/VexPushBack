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
extern pros::Optical colorsensor;
extern lemlib::Chassis chassis;
extern pros::Motor intake;
extern pros::Motor hopper;
extern pros::Motor hopper2;
extern pros::Motor topscore;
extern pros::ADIDigitalOut matchloader;
extern pros::ADIDigitalOut topaligner;

#endif