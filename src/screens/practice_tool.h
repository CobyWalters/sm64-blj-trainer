/**
 * sm64bljtrainer-N64 - practice_tool.h
 *
 * Copyright 2023, rollercobester
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE.txt file in the root directory of this source tree.
 */

#ifndef PRACTICE_TOOL_H
#define PRACTICE_TOOL_H

#include <string.h>
#include "../fps.h"
#include "../gfx.h"
#include "../input.h"
#include "../sfx.h"
#include "../system.h"
#include "../text.h"

typedef enum {
    FRAMES_1_4_6,
    FRAMES_1_4_8, /* Not an actual ID, just a counter */
} rhythm_mode_t;

bool is_blj_frame(int frame);
int get_first_bad_input_frame();
void practice_tool_tick(game_state_t* game_state);
void practice_tool_draw();

#endif