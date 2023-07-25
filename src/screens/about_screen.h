/**
 * sm64bljtrainer-N64 - about_screen.h
 *
 * Copyright 2023, rollercobester
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE.txt file in the root directory of this source tree.
 */

#ifndef ABOUT_SCREEN_H
#define ABOUT_SCREEN_H

#include "../input.h"
#include "../system.h"
#include "../text.h"

void about_screen_tick(game_state_t* game_state);
void about_screen_draw(void);

#endif