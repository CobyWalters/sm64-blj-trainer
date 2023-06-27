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