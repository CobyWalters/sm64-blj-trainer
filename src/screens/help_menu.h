/**
 * sm64bljtrainer-N64 - help_menu.h
 *
 * Copyright 2023, Coby Walters
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE.txt file in the root directory of this source tree.
 */

#ifndef HELP_MENU_H
#define HELP_MENU_H

#include "../system.h"
#include "../text.h"

void help_menu_tick(game_state_t* game_state, const gamepad_state_t *const gamepad);
void help_menu_draw(void);

#endif