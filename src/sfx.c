/**
 * sm64bljtrainer-N64 - sfx.c
 *
 * Copyright 2023, Coby Walters
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE.txt file in the root directory of this source tree.
 */

#include "sfx.h"

#define SFX_SAMPLE_RATE 44100
#define SFX_NUM_BUFFERS 8

static bool audio_enabled;

low_latency_wav64_t sfx_audio[SFX_ID_COUNT];

/* This array must line up with sfx_id_t */
static const char *const sfx_files[SFX_ID_COUNT] = {
    "sfx/16bitclick.wav64",
    "sfx/select.wav64"
};

void sfx_init(void) {
    audio_enabled = true;
    audio_init(SFX_SAMPLE_RATE, SFX_NUM_BUFFERS);
    audio_write_silence();
    mixer_init(SFX_ID_COUNT * 2);
    /* Load the sound effects cache */
    for (size_t i = 0; i < SFX_ID_COUNT; i++) {
        wav64_open(&sfx_audio[i].data, sfx_files[i]);
        waveform_t wave = sfx_audio[i].data.wave;
        float duration = (float) (16 * wave.len) / (wave.bits * wave.frequency);
        int buffers_per_second = SFX_SAMPLE_RATE / audio_get_buffer_length();
        sfx_audio[i].buffers_needed = ceil(buffers_per_second * duration);
        //assertf(1 == 0, "1: %f 2: %d 3: %d", duration, buffers_per_second, buffers_needed);
    }
}

void sfx_play(sfx_id_t sfx_id) {
    if (!audio_enabled) return;
    mixer_ch_play(sfx_id, &sfx_audio[sfx_id].data.wave);
    sfx_audio[sfx_id].buffers_remaining = sfx_audio[sfx_id].buffers_needed;
    // Either of these give roughly the same result
    //wav64_play(&sfx_cache[sfx_id], sfx_id);
}

void sfx_buffer_sound_effects() {
    if (audio_should_write()) {
        short *const buf = audio_write_begin();
        mixer_poll(buf, audio_get_buffer_length());
        audio_write_end();
    }
}

void sfx_toggle_audio() {
    audio_enabled = !audio_enabled;
}

bool audio_should_write() {
    if (!audio_can_write()) return false;

    bool buffers_found = false;
    for (size_t i = 0; i < SFX_ID_COUNT; i++) {
        if (sfx_audio[i].buffers_remaining > 0) {
            buffers_found = true;
            sfx_audio[i].buffers_remaining--;
        }
    }

    return buffers_found;
}

int16_t *read_dfs_raw_audio(const char *const file) {
    int fp = dfs_open(file);
    int16_t *raw_audio = malloc(dfs_size(fp));
    dfs_read(raw_audio, 1, dfs_size(fp), fp);
    dfs_close(fp);
    return raw_audio;
}