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
static int current_frame = 0;
static int frame_gap = 0;
  
int get_first_bad_input_frame() {
    if (blj_frames[1])  return 2;
    if (blj_frames[2])  return 3;
    if (!blj_frames[3]) return 4;
    if (blj_frames[4])  return 5;
    if (blj_frames[6])  return 7;
    if (!blj_frames[5] && !blj_frames[7]) return 8;
    return -1;
}

void practice_tool_tick(game_state_t* game_state) {
    
    if (b_press()) {
        *game_state = MAIN_MENU;
    }

    /* Advance the frame if timer is running */
    if (current_frame > 0 && current_frame < 30) {
        ++current_frame;
    }

    if (!a_press()) {
        ++frame_gap;
    } else {
        if (current_frame == 0 || frame_gap > 4) {
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

    //input_draw();

    /* Draw frame counter */
    text_set_font(FONT_MEDIUM);
    char frame_text[10];
    sprintf(frame_text, "Frame: %d", current_frame);
    text_draw(32, 24, frame_text, ALIGN_LEFT);
    
    /* Draw repo url */
    text_draw(gfx->width/2, 201, "github.com/CobyWalters/sm64-blj-trainer", ALIGN_CENTER);

    /* Draw starting text */
    if (current_frame == 0) {
        text_draw(gfx->width/2, gfx->height/2, "Press a to start.", ALIGN_CENTER);
        return;
    }

    /* Determine the first frame with a bad input */
    int bad_blj_frame = get_first_bad_input_frame();

    /* Build the blj frame string, keeping track of which index the string should start being colored red */
    int margin = 20;
    int red_text_index = 0;
    char buf[4];
    char blj_frame_text[64];
    strcpy(blj_frame_text, "");

    for (int i = 1; i <= 30; ++i) {
        if (text_get_line_width(blj_frame_text) > (gfx->width - 2 * margin)) {
            break;
        } else if (!blj_frames[i-1]) {
            continue;
        } else if (i < bad_blj_frame) {
            red_text_index += 2;
        }
        sprintf(buf, " %d", i);
        strcat(blj_frame_text, buf);
    }

    if (!red_text_index) red_text_index = 63;

    /* Draw the blj frames */
    graphics_set_color(COLOR_GREEN, 0);
    text_draw_partial(gfx->width/2, gfx->height/2 - 5, blj_frame_text, ALIGN_CENTER, 0, red_text_index);
    graphics_set_color(COLOR_RED, 0);
    text_draw_partial(gfx->width/2, gfx->height/2 - 5, blj_frame_text, ALIGN_CENTER, red_text_index, 63);
}