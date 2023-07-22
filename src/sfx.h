/**
 * sm64bljtrainer-N64 - sfx.h
 *
 * Copyright 2023, Coby Walters
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE.txt file in the root directory of this source tree.
 */

#ifndef SFX_H
#define SFX_H

#include "system.h"

typedef enum {
    SFX_CLICK,
    SFX_DUMMY,
    SFX_ID_COUNT, /* Not an actual ID, just a counter */
} sfx_id_t;

void sfx_init(void);
void sfx_play(sfx_id_t sfx_id);
void sfx_toggle_audio();
int16_t *read_dfs_raw_audio(const char *const file);
void sfx_buffer_sound_effects();

#endif