/**
 * sm64bljtrainer-N64 - input.h
 *
 * Copyright 2023, rollercobester
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE.txt file in the root directory of this source tree.
 */

#ifndef INPUT_H
#define INPUT_H

#include "system.h"
#include "sfx.h"

void input_tick();
bool a_press();
bool b_press();
bool l_press();
bool r_press();
bool start_press();
bool dpad_up();
bool dpad_down();
bool stick_up();
bool stick_down();

#endif