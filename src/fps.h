/**
 * sm64bljtrainer-N64 - fps.h
 *
 * Copyright 2023, rollercobester
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE.txt file in the root directory of this source tree.
 */

#ifndef FPS_H
#define FPS_H

#include "system.h"
#include "text.h"

typedef int64_t ticks_t;

#define FPS_MAX             ((unsigned int) (30))
#define FPS_TICKS_PER_FRAME ((unsigned int) (TICKS_PER_SECOND / FPS_MAX))
#define FPS_TEXT_LEN        ((size_t) 11)

bool fps_tick(void);
void fps_draw(void);

#endif