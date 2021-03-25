/* Copyright 2021 3araht
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _WEB,
    _COPY,
    _FN
};

enum custom_keycodes {
    BASEUP = SAFE_RANGE,
    BASEDN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT_default( \
        BASEUP,                                      \
                          MI_Db_3,        MI_Eb_3,      \
        BASEDN,   MI_C_3,        MI_D_3,     MI_E_3  \
    ),
    [_WEB] = LAYOUT_default( \
        LGUI(KC_T),                                    \
                           LGUI(KC_MINS), LGUI(KC_EQL),      \
        LGUI(KC_N), LGUI(KC_LEFT), LGUI(KC_R), LGUI(KC_RIGHT)  \
    ),
    [_COPY] = LAYOUT_default( \
        LGUI(KC_O),                                         \
                           LGUI(KC_A),    LGUI(KC_F),        \
        LGUI(KC_Z), LGUI(KC_X),    LGUI(KC_C), LGUI(KC_V)  \
    ),
    [_FN] = LAYOUT_default( \
        _______,                                         \
                           RGB_MOD,    RGB_TOG,        \
        _______, DF(_BASE),    DF(_WEB),       DF(_COPY)  \
    )
};

enum combos {
  BASE_FN,
  WEB_FN,
  COPY_FN
};

const uint16_t PROGMEM base_combo[] = {BASEUP,     BASEDN,     COMBO_END};
const uint16_t PROGMEM web_combo[]  = {LGUI(KC_T), LGUI(KC_N), COMBO_END};
const uint16_t PROGMEM copy_combo[] = {LGUI(KC_O), LGUI(KC_Z), COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [BASE_FN] = COMBO_ACTION(base_combo),
  [WEB_FN]  = COMBO_ACTION(web_combo),
  [COPY_FN] = COMBO_ACTION(copy_combo)
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch(combo_index) {
        case BASE_FN:
        case WEB_FN:
        case COPY_FN:
            if (pressed) {
                default_layer_set(1UL << _FN);
            }
            break;
    }
}


void keyboard_post_init_user(void) {
    default_layer_set(1UL << _BASE);
};

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case BASEUP:
            process_midi(MI_BENDU, record);
            break;
        case BASEDN:
            process_midi(MI_BENDD, record);
            break;
    }
    return true;
}
