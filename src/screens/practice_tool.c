/**
 * sm64bljtrainer-N64 - practice_tool.c
 *
 * Copyright 2023, Coby Walters
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE.txt file in the root directory of this source tree.
 */

#include "practice_tool.h"

static bool blj_frames[30];
static bool is_a_held = false;
static int current_frame = 0;
static int frame_gap = 0;

void practice_tool_tick(game_state_t* game_state, const gamepad_state_t *const gamepad) {
    
    if (gamepad->B) {
        *game_state = MAIN_MENU;
    }

    bool a_press = (!is_a_held && gamepad->A);
    is_a_held = gamepad->A;

    /* Advance the frame if timer is running */
    if (current_frame > 0 && current_frame < 30) {
        ++current_frame;
    }

    if (!a_press) {
        ++frame_gap;
    } else {
        if (current_frame == 0 || frame_gap > 5) {
            /* Reset the timer if needed */
            for (int i = 0; i < 30; ++i) {
                blj_frames[i] = false;
            }
            current_frame = 1;
        }
        blj_frames[current_frame - 1] = true;
        frame_gap = 0;
    }
}

void practice_tool_draw() {

    /* Draw FPS*/
    fps_draw();

    /* Draw frame counter */
    text_set_font(FONT_MEDIUM);
    char frame_text[10];
    sprintf(frame_text, "Frame: %d", current_frame);
    text_draw(15, 15, frame_text, ALIGN_LEFT);
    
    /* Draw repo url */
    text_draw(gfx->width - 12, 225, "github.com/CobyWalters/sm64-blj-trainer", ALIGN_RIGHT);

    /* Draw starting text */
    if (current_frame == 0) {
        text_draw(gfx->width/2, gfx->height/2, "Press a to start.", ALIGN_CENTER);
        return;
    }

    /* Build the blj frame string to determine the width */
    char buf[4];
    char blj_frame_text[64];
    strcpy(blj_frame_text, "");
    int margin = 20;

    for (int i = 1; i <= 30; ++i) {
        if (text_get_line_width(blj_frame_text) > (gfx->width - 2 * margin)) {
            break;
        } else if (!blj_frames[i - 1]) {
            continue;
        }
        sprintf(buf, " %d", i);
        strcat(blj_frame_text, buf);
    }

    /* Draw the blj frame string piece by piece */
    graphics_set_color(COLOR_GREEN, 0);

    int w = text_get_line_width(blj_frame_text);
    int x = gfx->width/2 - w/2;
    int y = gfx->height/2;

    char blj_frame_text2[64];
    strcpy(blj_frame_text2, "");

    for (int i = 1; i <= 30; ++i) {

        if (text_get_line_width(blj_frame_text2) > (gfx->width - 2 * margin)) {
            break;
        }
        
        if ((i == 4 || (i == 8 && !blj_frames[5])) && !blj_frames[i - 1]) {
            graphics_set_color(COLOR_RED, 0);
        } else if ((i == 2 || i == 3 || i == 5 || i == 7) && blj_frames[i - 1]) {
            graphics_set_color(COLOR_RED, 0);
        }

        if (blj_frames[i-1]) {
            sprintf(buf, " %d", i);
            strcat(blj_frame_text2, buf);
            text_draw(x, y, buf, ALIGN_LEFT);
            x += text_get_line_width(buf);
        }
    }
}