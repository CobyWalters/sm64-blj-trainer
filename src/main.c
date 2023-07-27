/**
 * sm64bljtrainer-N64 - main.c
 *
 * Copyright 2023, rollercobester
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

game_state_t game_state;

void reset_handler(exception_t *ex) {
    if (ex->type != EXCEPTION_TYPE_RESET) {
        exception_default_handler(ex);
        return;
    }
    display_close();
    free(gfx);
    abort();
}

void low_latency_poll() {
    /** 
     * Could theoretically move input and screen ticks here if done correctly.
     * This would undoubtedly be more complicated and I don't yet know if it
     * would be more or less true to the input detection in Super Mario 64.
     */
}

void per_frame_poll() {
    /* Evaluate controller input */
    controller_scan();
    input_tick();
    
    /* Reset text formatting */
    gfx_set_color(COLOR_WHITE);
    graphics_fill_screen(gfx->disp, graphics_convert_color(COLOR_BLACK));

    /* Reset text formatting and wipe the screen */
    text_set_font(FONT_MEDIUM);
    gfx_set_color(COLOR_WHITE);
    graphics_fill_screen(gfx->disp, graphics_convert_color(COLOR_BLACK));

    /* Perform screen tick operations and draw screen */
    switch (game_state) {
        case MAIN_MENU:
            main_menu_tick();
            main_menu_draw();
            break;
        case PRACTICE_TOOL:
            practice_tool_tick();
            practice_tool_draw();
            break;
        case ABOUT_SCREEN:
            about_screen_tick();
            about_screen_draw();
            break;
        case HELP_MENU:
            help_menu_tick();
            help_menu_draw();
            break;
    }

    /* Finish drawing and show the framebuffer */
    gfx_display_flip();
}

int main() {

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
    //game_state = malloc(sizeof(game_state_t));
    game_state = MAIN_MENU;

    /* Initial scan to avoid garbage input */
    controller_scan();

    /* Run the game loop */
    while (1) {

        /* Execute sub frame operations until a frame buffer is grabbed */
        static display_context_t disp = 0;
        while (gfx_display_lock(disp)) {
            low_latency_poll();
        }

        /* Continue executing sub frame operations until the next frame tick has occured */
        while (fps_frame_lock()) {
            low_latency_poll();
        }

        /* Execute all frame based operations */
        per_frame_poll();
    }
}

#endif