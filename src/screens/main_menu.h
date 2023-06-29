/**
 * sm64bljtrainer-N64 - main_menu.h
 *
 * Copyright 2023, Coby Walters
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE.txt file in the root directory of this source tree.
 */

#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "../input.h"
#include "../system.h"
#include "../text.h"

void main_menu_tick(game_state_t* game_state);
void main_menu_draw(void);

#endif