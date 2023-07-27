/**
 * sm64bljtrainer-N64 - practice_tool.c
 *
 * Copyright 2023, rollercobester
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE.txt file in the root directory of this source tree.
 */

#include "practice_tool.h"

static rhythm_mode_t rhythm_mode = FRAMES_1_4_8;
static bool blj_frames[30];
static int current_frame = 0;
static int frame_gap = -1;

bool is_blj_frame(int frame) {
    if (frame == 6 && rhythm_mode == FRAMES_1_4_8)
        return false;
    return frame % 2 == (int) (frame < 3);
}

int get_first_bad_input_frame() {
    if ( blj_frames[2]) return 3;
    if (!blj_frames[3]) return 4;
    if ( blj_frames[4]) return 5;
    if ( blj_frames[6]) return 7;
    if (!blj_frames[5] && !blj_frames[7]) return 8;
    return -1;
}

void practice_tool_tick() {
    if (b_press()) {
        game_state = MAIN_MENU;
        return;
    }

    if (l_press()) 
        rhythm_mode = FRAMES_1_4_6;
    if (r_press()) 
        rhythm_mode = FRAMES_1_4_8;
    if (start_press()) 
        sfx_toggle_audio();
    if (a_press()) {

        if (current_frame == 0 || frame_gap > 5) {
            /* Reset the timer if needed */
            for (int i = 0; i < 30; ++i) {
                blj_frames[i] = false;
            }
            current_frame = 1;
        } 

        blj_frames[current_frame - 1] = true;
        frame_gap = -1;
    }

    if (current_frame && current_frame < 30) {
        if (is_blj_frame(current_frame)) {
            sfx_play(SFX_CLICK);
        }
        ++current_frame;
    }
    ++frame_gap;
}

void practice_tool_draw() {
    /* Draw FPS*/
    //fps_draw();

    /* Draw repo url */
    text_draw(gfx->width/2, 216, "github.com/rollercobester/sm64-blj-trainer", ALIGN_CENTER);

    /* Draw frame counter */
    text_set_font(FONT_BOLD);
    char frame_text[10];
    sprintf(frame_text, "Frame: %d", current_frame);
    text_draw(32, 24, frame_text, ALIGN_LEFT);

    /* Draw rhythm mode */
    gfx_set_color((rhythm_mode == FRAMES_1_4_6 ? COLOR_WHITE: COLOR_GRAY));
    text_draw(gfx->width - 70, 24, "1 4 6", ALIGN_RIGHT);
    gfx_set_color(COLOR_LIGHT_GRAY);
    text_draw(gfx->width - 63, 24, "-", ALIGN_RIGHT);
    gfx_set_color((rhythm_mode == FRAMES_1_4_8 ? COLOR_WHITE: COLOR_GRAY));
    text_draw(gfx->width - 32, 24, "1 4 8", ALIGN_RIGHT);

    gfx_set_color(COLOR_WHITE);
    /* Draw starting text */
    if (current_frame == 0) {
        text_draw(gfx->width/2, gfx->height/2, "Press a to start.", ALIGN_CENTER);
        text_set_font(FONT_MEDIUM);
        text_draw(gfx->width/2, gfx->height/2 + 30, "Press start to toggle audio", ALIGN_CENTER);
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
    gfx_set_color(COLOR_GREEN);
    text_draw_partial(gfx->width/2, gfx->height/2 - 5, blj_frame_text, ALIGN_CENTER, 0, red_text_index);
    gfx_set_color(COLOR_RED);
    text_draw_partial(gfx->width/2, gfx->height/2 - 5, blj_frame_text, ALIGN_CENTER, red_text_index, 63);
}