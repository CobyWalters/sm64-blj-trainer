/**
 * sm64bljtrainer-N64 - about_screen.c
 *
 * Copyright 2023, rollercobester
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE.txt file in the root directory of this source tree.
 */

#include "about_screen.h"

void about_screen_tick(game_state_t* game_state) {
    if (b_press()) {
        *game_state = MAIN_MENU;
    }
}

void about_screen_draw() {

    /* Draw title */
    text_set_font(FONT_BOLD);
    text_draw(32, 24, "About", ALIGN_LEFT);

    /* Draw body text */
    text_set_font(FONT_MEDIUM);
    text_draw_wordwrap(32, 44, 320-64, 
        "a sm64 blj rhythm trainer ROM by rollercobester\n\n"
        "Enter Command font by Font End Dev (fontenddev.com), licensed "
        "under CC BY 4.0\n"
        "On or Off Light Switch Tap sound effect by Mixkit (mixkit.co),"
        "licensed under Mixkit License\n\n"
        "This ROM is a n64 port of xandrey's practice tool. The GUI is "
        "heavily inspired by wermi's controller test ROM "
        "(github.com/wermipls/mimi).\n\n"
    );
}