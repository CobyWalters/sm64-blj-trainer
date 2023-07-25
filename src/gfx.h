/**
 * sm64bljtrainer-N64 - gfx.h
 *
 * Copyright 2023, Coby Walters
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE.txt file in the root directory of this source tree.
 */

#ifndef GFX_H
#define GFX_H

#include <libdragon.h>
#include "system.h"

#define COLOR_BLACK      gfx_make_color(0,   0,   0,   255)
#define COLOR_GRAY       gfx_make_color(100, 100, 100, 255)
#define COLOR_LIGHT_GRAY gfx_make_color(175, 175, 175, 255)
#define COLOR_WHITE      gfx_make_color(255, 255, 255, 255)
#define COLOR_RED        gfx_make_color(223, 104, 93,  255)
#define COLOR_GREEN      gfx_make_color(35,  176, 58,  255)

typedef enum {
    BUFFERING_DOUBLE = 2,
    BUFFERING_TRIPLE = 3
} buffer_mode_t;

typedef struct gfx_s {
    // Setup state
    resolution_t res;
    int width;
    int height;
    bitdepth_t color_depth;
    buffer_mode_t num_buffers;
    gamma_t gamma;
    antialias_t antialias;
    // Drawing state
    display_context_t disp;
    color_t color;
} gfx_t;

extern gfx_t *gfx;

void gfx_init(resolution_t res, bitdepth_t bit, buffer_mode_t num_buffers,
    gamma_t gamma, antialias_t aa);

void gfx_set_color(color_t color);
color_t gfx_get_color(void);
color_t gfx_make_color(int r, int g, int b, int a);
color_t gfx_blend_colors(color_t color_1, int color_1_weight, color_t color_2, int color_2_weight);

void gfx_display_lock(void);
void gfx_display_flip(void);
sprite_t *read_dfs_sprite(const char *file);

#endif