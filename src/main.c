/**
 * sm64bljtrainer-N64 - main.c
 *
 * Copyright 2023, Coby Walters
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE.txt file in the root directory of this source tree.
 */

#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <libdragon.h>
#include <exception.h>
#include "screens/about_screen.c"
#include "screens/help_menu.c"
#include "screens/main_menu.c"
#include "screens/practice_tool.c"
#include "input.h"
#include "fps.h"
#include "gfx.h"
#include "sfx.h"
#include "system.h"

void reset_handler(exception_t *ex) {
    if (ex->type != EXCEPTION_TYPE_RESET) {
        exception_default_handler(ex);
        return;
    }
    display_close();
    abort();
}

int16_t *sfx;

int main(void) {

    /* Initialize libdragon subsystems */
    timer_init();
    controller_init();
    dfs_init(DFS_DEFAULT_LOCATION);

    /* Initialize game subsystems */
    gfx_init(RESOLUTION_320x240, DEPTH_32_BPP, BUFFERING_DOUBLE, GAMMA_NONE,
        ANTIALIAS_RESAMPLE);
    sfx_init();
    text_init();

    console_set_debug(true);
    register_exception_handler(reset_handler);

    /* Initialize game state */
    game_state_t game_state = MAIN_MENU;

    /* Initial scan to avoid garbage input */
    controller_scan();
    int16_t* sfx = (int16_t*)read_dfs_raw_audio("click2.raw");

    /* Run the main loop */
    while (1) {

        sfx_buffer_sound_effects();

        /* FPS control */
        bool new_frame = fps_tick();
        if (!new_frame) continue;

        /* Update controller state */
        controller_scan();
        input_tick();

        if (a_press()) {
            audio_write(sfx);
        }

        /* Gamestate frame tick calculations */
        switch (game_state) {
            case MAIN_MENU:
                main_menu_tick(&game_state);
                break;
            case PRACTICE_TOOL:
                practice_tool_tick(&game_state);
                break;
            case ABOUT_SCREEN:
                about_screen_tick(&game_state);
                break;
            case HELP_MENU:
                help_menu_tick(&game_state);
                break;
        }

        /* Grab a display buffer and start drawing */
        gfx_display_lock();
        gfx_set_color(COLOR_WHITE);
        graphics_fill_screen(gfx->disp, graphics_convert_color(COLOR_BLACK));
        switch (game_state) {
            case MAIN_MENU:
                main_menu_draw();
                break;
            case PRACTICE_TOOL:
                practice_tool_draw();
                break;
            case ABOUT_SCREEN:
                about_screen_draw();
                break;
            case HELP_MENU:
                help_menu_draw();
                break;
        }

        /* Finish drawing and show the framebuffer */
        gfx_display_flip();
    }
}

#endif