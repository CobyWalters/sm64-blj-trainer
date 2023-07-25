/**
 * sm64bljtrainer-N64 - help_menu.c
 *
 * Copyright 2023, rollercobester
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE.txt file in the root directory of this source tree.
 */

#include "help_menu.h"

void help_menu_tick(game_state_t* game_state) {
    if (b_press()) {
        *game_state = MAIN_MENU;
    }
}

void help_menu_draw() {

    /* Draw title */
    text_set_font(FONT_BOLD);
    text_draw(32, 24, "Help", ALIGN_LEFT);

    /* Draw body text */
    text_set_font(FONT_MEDIUM);
    text_draw_wordwrap(32, 44, 320-64, 
        "For consistency, an optimal blj mash starts with three A presses "
        "on specific frames, followed by mashing as fast as possible. "
        "There are two options to choose from:\n\n"
        "Fast: 1 - 4 - 8 - mash\n"
        "Faster: 1 - 4 - 6 - mash\n\n"
        "The practice tool will run a 30 frame counter for 1 second once "
        "you start pressing A and display what frames you hit."
    );
}