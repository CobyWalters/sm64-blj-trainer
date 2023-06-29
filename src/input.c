/**
 * sm64bljtrainer-N64 - input.c
 *
 * Copyright 2023, Coby Walters
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE.txt file in the root directory of this source tree.
 */

#include "input.h"
#include "text.h"

controllers_state_t pressed_keys;
controllers_state_t held_keys;
int stick_up_frames[4];
int stick_down_frames[4];

void input_tick(void) {
    pressed_keys = get_keys_down();
    held_keys = get_keys_held();
    for (int i = 0; i < 4; ++i) {
        stick_up_frames[i] = held_keys.c[i].y > 60 ? stick_up_frames[i] + 1 : 0;
        stick_down_frames[i] = held_keys.c[i].y < -60 ? stick_down_frames[i] + 1 : 0;
    }
}

bool a_press() {
    for (int i = 0; i < 4; ++i)
        if (pressed_keys.c[i].A)
            return true;
    return false;
}

bool b_press() {
    for (int i = 0; i < 4; ++i)
        if (pressed_keys.c[i].B)
            return true;
    return false;
}

bool dpad_up() {
    for (int i = 0; i < 4; ++i)
        if (pressed_keys.c[i].up)
            return true;
    return false;
}

bool dpad_down() {
    for (int i = 0; i < 4; ++i)
        if (pressed_keys.c[i].down)
            return true;
    return false;
}

bool stick_up() {
    for (int i = 0; i < 4; ++i)
        if (stick_up_frames[i] == 1 || (stick_up_frames[i] > 10 && stick_up_frames[i] % 4 == 0))
            return true;
    return false;
}

bool stick_down() {
    for (int i = 0; i < 4; ++i)
        if (stick_down_frames[i] == 1 || (stick_down_frames[i] > 10 && stick_down_frames[i] % 4 == 0))
            return true;
    return false;
}