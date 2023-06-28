/**
 * sm64bljtrainer-N64 - text.h
 *
 * Copyright 2023, Coby Walters
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE.txt file in the root directory of this source tree.
 */

#ifndef TEXT_H
#define TEXT_H

#include <libdragon.h>
#include <limits.h>
#include <stdlib.h>
#include "gfx.h"

enum Font {
    FONT_MEDIUM = 0,
    FONT_BOLD = 1,
};

enum TextAlign {
    ALIGN_LEFT,
    ALIGN_RIGHT,
    ALIGN_CENTER,
};

void text_init();
void text_set_font(enum Font f);
void text_set_line_height(int h);
int text_get_line_width(const char s[]);
void text_draw_partial(int x, int y, const char s[], enum TextAlign align, int start, int end);
void text_draw(int x, int y, const char s[], enum TextAlign align);
void text_draw_wordwrap(int x, int y, int w, const char s[]);

#endif