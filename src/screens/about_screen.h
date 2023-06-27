/**
 * sm64bljtrainer-N64 - about_screen.h
 *
 * Copyright 2023, Coby Walters
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE.txt file in the root directory of this source tree.
 */

#ifndef ABOUT_SCREEN_H
#define ABOUT_SCREEN_H

#include "../system.h"
#include "../text.h"

void about_screen_tick(game_state_t* game_state, const gamepad_state_t *const gamepad);
void about_screen_draw(void);

#endif