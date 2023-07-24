/**
 * sm64bljtrainer-N64 - system.h
 *
 * Copyright 2023, Coby Walters
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE.txt file in the root directory of this source tree.
 */

#ifndef SYSTEM_H
#define SYSTEM_H

#include <math.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <libdragon.h>
#include <limits.h>

typedef enum {
    MAIN_MENU,
    PRACTICE_TOOL,
    ABOUT_SCREEN,
    HELP_MENU
} game_state_t;

typedef struct SI_condat gamepad_state_t;
typedef struct controller_data controllers_state_t;

// Make sure this lines up with BUFFERS_PER_SECOND in libdragon's audio.c (default 25)
#define BUFFERS_PER_SECOND 30

#endif