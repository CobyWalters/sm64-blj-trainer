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

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <libdragon.h>

typedef int64_t ticks_t;

#define TICKS_PER_MS ((ticks_t)(TICKS_PER_SECOND / 1000))

#define CONTROLLER_1 0
#define CONTROLLER_2 1
#define CONTROLLER_3 2
#define CONTROLLER_4 3

#define COLOR_BLACK graphics_make_color(0,   0,   0,   255)
#define COLOR_WHITE graphics_make_color(255, 255, 255, 255)
#define COLOR_RED   graphics_make_color(223, 104, 93,  255)
#define COLOR_GREEN graphics_make_color(35,  176, 58,  255)

typedef enum {
    MAIN_MENU,
    PRACTICE_TOOL,
    ABOUT_SCREEN,
    HELP_MENU
} game_state_t;

typedef struct SI_condat gamepad_state_t;
typedef struct controller_data controllers_state_t;

#endif