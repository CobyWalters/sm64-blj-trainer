/**
 * sm64bljtrainer-N64 - gfx.c
 *
 * Copyright 2023, Coby Walters
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE.txt file in the root directory of this source tree.
 */

#include "gfx.h"

gfx_t *gfx;

void gfx_init(resolution_t res, bitdepth_t depth, buffer_mode_t num_buffers,
    gamma_t gamma, antialias_t aa) {
    display_init(res, depth, num_buffers, gamma, aa);
    gfx = malloc(sizeof(gfx_t));
    gfx->res = res;
    gfx->width = res.width;
    gfx->height = res.height;
    gfx->color_depth = depth;
    gfx->num_buffers = num_buffers;
    gfx->gamma = gamma;
    gfx->antialias = aa;
    gfx->disp = 0;
    gfx->color = COLOR_WHITE;
}

void gfx_set_color(color_t color) {
    gfx->color = color;
    int color_32_bit = graphics_convert_color(color);
    graphics_set_color(color_32_bit, 0);
}

color_t gfx_get_color() {
    return gfx->color;
}

color_t gfx_make_color(int r, int g, int b, int a) {
    color_t color;
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
    return color;
}

color_t gfx_blend_colors(color_t color_1, int color_1_weight, color_t color_2,
    int color_2_weight) {
    color_t color;
    color.r = (color_1.r * color_1_weight + color_2.r * color_2_weight) /
                (color_1_weight + color_2_weight);
    color.g = (color_1.g * color_1_weight + color_2.g * color_2_weight) /
                (color_1_weight + color_2_weight);
    color.b = (color_1.b * color_1_weight + color_2.b * color_2_weight) /
                (color_1_weight + color_2_weight);
    color.a = (color_1.a * color_1_weight + color_2.a * color_2_weight) /
                (color_1_weight + color_2_weight);
    return color;
}

void gfx_display_lock(void) {
    /* Grab a render buffer */
    static display_context_t disp = 0;
    while (!(disp = display_lock())) { /* Spinlock! */ }
    gfx->disp = disp;
}

void gfx_display_flip(void) {
    if (!gfx->disp) return;
    /* Force backbuffer flip and reset the display handle */
    display_show(gfx->disp);
    gfx->disp = 0;
}

sprite_t *read_dfs_sprite(const char *const file) {
    int fp = dfs_open(file);
    sprite_t *sprite = malloc(dfs_size(fp));
    dfs_read(sprite, 1, dfs_size(fp), fp);
    dfs_close(fp);
    return sprite;
}