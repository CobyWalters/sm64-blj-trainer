/**
 * sm64bljtrainer-N64 - sfx.c
 *
 * Copyright 2023, Coby Walters
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE.txt file in the root directory of this source tree.
 */

#include "sfx.h"

#define SFX_SAMPLE_RATE 16000
#define SFX_NUM_BUFFERS 1

static bool audio_enabled;

/* This array must line up with sfx_id_t */
static const char *const sfx_files[SFX_ID_COUNT] = {
    "sfx/16bitclick.raw",
};

int16_t* sfx_audio[SFX_ID_COUNT];

/* put the right number (in bytes) */
static const int SFX_FILE_SIZE[SFX_ID_COUNT] = {
    2108,
};

void sfx_init(void) {
    audio_enabled = true;

    audio_init(SFX_SAMPLE_RATE, SFX_NUM_BUFFERS);
    audio_write_silence();
    for (size_t i = 0; i < SFX_ID_COUNT; ++i) {
        sfx_audio[i] = (int16_t*) read_dfs_raw_audio(sfx_files[i]);
    }
}

void sfx_play(sfx_id_t sfx_id) {
    if (!audio_enabled) return;

    uint8_t* buf = (uint8_t*) audio_write_begin();
    memcpy(buf, sfx_audio[sfx_id], SFX_FILE_SIZE[sfx_id]);
    memset(buf + SFX_FILE_SIZE[sfx_id], 0, audio_get_buffer_length() * 4 - SFX_FILE_SIZE[sfx_id]);
    audio_write_end();
}

void sfx_toggle_audio() {
    audio_enabled = !audio_enabled;
}

int16_t* read_dfs_raw_audio(const char *const file) {
    int fp = dfs_open(file);
    int16_t* raw_audio = malloc(dfs_size(fp));
    dfs_read(raw_audio, 1, dfs_size(fp), fp);
    dfs_close(fp);
    return raw_audio;
}