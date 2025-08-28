/**
 * \file main.h
 *
 * Contains common definitions and header files used throughout your PROS
 * project.
 *
 * \copyright Copyright (c) 2017-2023, Purdue University ACM SIGBots.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

/**
 * If defined, some commonly used enums will have preprocessor macros which give
 * a shorter, more convenient naming pattern.
 */
#define PROS_USE_SIMPLE_NAMES

/**
 * If defined, C++ literals will be available for use.
 */
#define PROS_USE_LITERALS

#include "api.h"

/**
 * Add more #includes here as needed
 */
// #include "okapi/api.hpp"

/**
 * Alliance color enum
 */
enum Alliance {
  RED,
  BLUE
};

extern Alliance ALLIANCE;

/**
 * If you find doing pros::Motor() to be tedious and you'd prefer just to do
 * Motor, you can use the namespace with the following commented-out line.
 *
 * IMPORTANT: Only use either the okapi or pros namespace, not both concurrently!
 */
// using namespace pros;
// using namespace pros::literals;
// using namespace okapi;

/**
 * Prototypes for competition control and user-defined functions.
 */
#ifdef __cplusplus
extern "C" {
#endif

void setLBState(int state);
void nextLBState(void);
void prevLBState(void);
void moveLB(float velocity);
void LBControl(void);
void colorSort(void);
void skipRing(void);
void autonomous(void);
void initialize(void);
void disabled(void);
void competition_initialize(void);
void opcontrol(void);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/**
 * You can add C++-only headers here
 */
// #include <iostream>
#endif

#endif  // _PROS_MAIN_H_