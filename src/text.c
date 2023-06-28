/**
 * sm64bljtrainer-N64 - text.c
 *
 * Copyright 2023, Coby Walters
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE.txt file in the root directory of this source tree.
 */

#include "text.h"

struct font_data_t {
    sprite_t *sprite;
    uint8_t char_widths[128];
};

struct font_data_t fonts[2];
enum Font current_font = 0;
int line_height = 11;

void load_font(struct font_data_t *fontdata, const char sprite_path[], const char charwidth_path[]) {
    fontdata->sprite = read_dfs_sprite(sprite_path);
    int f = dfs_open(charwidth_path);
    dfs_read(fontdata->char_widths, sizeof(fontdata->char_widths), 1, f);
    dfs_close(f);
}

void text_init() {
    load_font(&fonts[FONT_MEDIUM], "font/medium.sprite", "font/medium_charwidths.bin");
    load_font(&fonts[FONT_BOLD], "font/bold.sprite", "font/bold_charwidths.bin");
    text_set_font(FONT_MEDIUM);
    text_set_line_height(11);
}

void text_set_font(enum Font f) {
    current_font = f;
    graphics_set_font_sprite(fonts[f].sprite);
}

void text_set_line_height(int h) {
    line_height = h;
}

int text_get_line_width(const char s[]) {
    const char* s_ = s;
    int w = 0;
    for (; *s_ != 0 && *s_ != '\n'; s_++) {
        w += fonts[current_font].char_widths[(int) *s_];
    }
    return w;
}

int text_get_word_width(const char s[]) {
    const char* s_ = s;
    int w = 0;
    for (; *s_ != 0 && *s_ != '\n' && *s_ != ' '; s_++) {
        w += fonts[current_font].char_widths[(int) *s_];
    }
    return w;
}

/* Draws part of the text, as if the rest of the letters were invisible */
void text_draw_partial(int x, int y, const char s[], enum TextAlign align, int start, int end) {

    int w = text_get_line_width(s);
    int align_offset = (align == ALIGN_LEFT ? 0 : (align == ALIGN_RIGHT? -w : -w/2));
    int x_offset = align_offset;
    int y_offset = 0;

    for (int i = 0; s[i] != 0 && i < end; ++i) {
        if (s[i] == '\n') {
            x_offset = align_offset;
            y_offset += line_height;
            continue;
        } else if (s[i] != ' ' && i >= start) {
            graphics_draw_character(gfx->disp, x + x_offset, y + y_offset, s[i]);
        }
        x_offset += fonts[current_font].char_widths[(int) s[i]];
    }
}

/* Draws the whole text */
void text_draw(int x, int y, const char s[], enum TextAlign align) {
    text_draw_partial(x, y, s, align, 0, INT_MAX);
}

void text_draw_wordwrap(int x, int y, int w, const char s[]) {
    
    int space_width = fonts[current_font].char_widths[(int) ' '];
    int x_offset = 0;
    int y_offset = 0;

    for (int i = 0; s[i] != '\0'; ++i) {
        if (s[i] == '\n') {
            x_offset = 0;
            y_offset += line_height;
            continue;
        } else if (s[i] == ' ') {
            int word_width = text_get_word_width(&s[i + 1]);
            int remaining_width = w - x_offset - space_width;

            if (word_width > remaining_width) {
                x_offset = 0;
                y_offset += line_height;
                continue;
            }
        }

        int char_width = fonts[current_font].char_widths[(int)s[i]];
        int remaining_width = w - x_offset;

        if (char_width > remaining_width) {
            x_offset = 0;
            y_offset += line_height;
        }

        graphics_draw_character(gfx->disp, x + x_offset, y + y_offset, s[i]);
        x_offset += char_width;
    }
}