/**
 * sm64bljtrainer-N64 - sfx.c
 *
 * Copyright 2023, Coby Walters
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE.txt file in the root directory of this source tree.
 */

#include "sfx.h"

#define SFX_SAMPLE_RATE 8192
#define SFX_NUM_BUFFERS 1
#define SFX_MAX_BITS 8

static wav64_t sfx_cache[SFX_ID_COUNT];

/* This array must line up with sfx_id_t */
static const char *const sfx_files[SFX_ID_COUNT] = {
    "sfx/click.wav64",
    "sfx/select.wav64",
};

void sfx_init(void) {
    audio_init(SFX_SAMPLE_RATE, SFX_NUM_BUFFERS);
    audio_write_silence();
    mixer_init(SFX_ID_COUNT);
    /* Load the sound effects cache */
    for (size_t i = 0; i < SFX_ID_COUNT; i++) {
        wav64_open(&sfx_cache[i], sfx_files[i]);
        mixer_ch_set_limits(i, 16, SFX_SAMPLE_RATE, 2048);
    }
}

void sfx_play(sfx_id_t sfx_id) {
    // Either of these give roughly the same result
    //wav64_play(&sfx_cache[sfx_id], sfx_id);
    mixer_ch_play(sfx_id, &sfx_cache[sfx_id].wave);
}

void sfx_buffer_sound_effects() {
    if (audio_can_write()) {
        short *const buf = audio_write_begin();
        mixer_poll(buf, audio_get_buffer_length());
        audio_write_end();
    }
}