/**
 * sm64bljtrainer-N64 - fps.c
 *
 * Copyright 2023, rollercobester
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE.txt file in the root directory of this source tree.
 */

#include "fps.h"

ticks_t last_frame_tick = 0;
float average_fps = 0.0;

bool fps_tick(void) {
    /* Check timing to return if tick is a new frame tick */
    const ticks_t current_tick = timer_ticks();
    if (current_tick >= last_frame_tick + FPS_TICKS_PER_FRAME) {
        average_fps = (float)(TICKS_PER_SECOND) / (current_tick - last_frame_tick);
        last_frame_tick = current_tick;
        return true;
    }
    return false;
}


void fps_draw(void) {
    text_set_font(FONT_MEDIUM);
    static char fps_text[FPS_TEXT_LEN];
    const char *const fps_text_format = "FPS: %.2f";
    snprintf(fps_text, FPS_TEXT_LEN, fps_text_format, average_fps);
    text_draw(gfx->width - 32, 24, fps_text, ALIGN_RIGHT);
}