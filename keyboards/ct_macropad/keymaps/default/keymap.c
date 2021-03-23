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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT_default( \
        MI_BENDU,                                      \
                          MI_Db_3,        MI_Eb_3,      \
        MI_BENDD,   MI_C_3,        MI_D_3,     MI_E_3  \
    ),
    [_WEB] = LAYOUT_default( \
        TO(_FN),                                    \
                           LGUI(KC_MINS), LGUI(KC_EQL),      \
        LGUI(KC_N), LGUI(KC_LEFT), LGUI(KC_R), LGUI(KC_RIGHT)  \
    ),
    [_COPY] = LAYOUT_default( \
        TO(_FN),                                         \
                           LGUI(KC_A),    LGUI(KC_F),        \
        LGUI(KC_Z), LGUI(KC_X),    LGUI(KC_C), LGUI(KC_V)  \
    ),
    [_FN] = LAYOUT_default( \
        _______,                                         \
                           XXXXXXX,    XXXXXXX,        \
        _______, TO(_BASE),    TO(_WEB),       TO(_COPY)  \
    )
};

const uint16_t PROGMEM test_combo[] = {MI_BENDU, MI_BENDD, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {COMBO(test_combo, TO(_FN))};
