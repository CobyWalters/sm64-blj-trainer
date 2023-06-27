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
} gfx_t;

extern gfx_t *gfx;

void gfx_init(resolution_t res, bitdepth_t bit, buffer_mode_t num_buffers,
    gamma_t gamma, antialias_t aa);

void gfx_display_lock(void);
void gfx_display_flip(void);
sprite_t *read_dfs_sprite(const char *file);

#endif