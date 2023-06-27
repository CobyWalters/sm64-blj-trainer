/**
 * sm64bljtrainer-N64 - practice_tool.h
 *
 * Copyright 2023, Coby Walters
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE.txt file in the root directory of this source tree.
 */

#ifndef PRACTICE_TOOL_H
#define PRACTICE_TOOL_H

#include <string.h>
#include "../fps.h"
#include "../system.h"
#include "../text.h"

void practice_tool_tick(game_state_t* game_state, const gamepad_state_t *const gamepad);
void practice_tool_draw(void);

#endif