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

#define WEBUP LGUI(KC_T)
#define WEBDN LGUI(KC_N)

#ifndef VIA_ENABLE
#    define COPY_LAYER_ENABLE
#endif

#ifdef COPY_LAYER_ENABLE
#    define COPYUP LGUI(KC_O)
#    define COPYDN LGUI(KC_Z)
#endif

#define MEETUP C(S(KC_M))
#define MEETDN C(KC_F)

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _WEB,
#ifdef COPY_LAYER_ENABLE
    _COPY,
#endif
    _MEET,
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
        WEBUP,                                    \
                              LGUI(KC_MINS),               LGUI(KC_EQL),                   \
        WEBDN, LGUI(KC_LEFT),                LGUI(KC_R),                 LGUI(KC_RIGHT)    \
    ),
#ifdef COPY_LAYER_ENABLE
// Basic shortcuts
// https://support.apple.com/en-us/HT201236
    [_COPY] = LAYOUT_default( \
        COPYUP,                                                            \
                            LGUI(KC_A),             LGUI(KC_F),            \
        COPYDN, LGUI(KC_X),             LGUI(KC_C),             LGUI(KC_V) \
    ),
#endif
    // Shortcuts for meetings
    // Used for OBS, Teams, etc.
    [_MEET] = LAYOUT_default( \
        MEETUP,                                                              \
                            LSA(KC_F2),             LSA(KC_F4),              \
        MEETDN, LSA(KC_F1),             LSA(KC_F3),             LSA(KC_F5)   \
    ),
#ifdef COPY_LAYER_ENABLE
    [_FN] = LAYOUT_default( \
        RGB_MOD,                                         \
                           RGB_TOG,             RGB_HUI,            \
        DF(_BASE), DF(_WEB),          DF(_COPY),          DF(_MEET) \
    )
#else
    [_FN] = LAYOUT_default( \
        RGB_MOD,                                         \
                           RGB_TOG,             RGB_HUI,            \
        DF(_BASE), DF(_WEB),          RGB_HUI,            DF(_MEET) \
    )
#endif
};

enum combos {
  BASE_FN,
  WEB_FN,
  COPY_FN,
  MEET_FN
};

const uint16_t PROGMEM base_combo[] = {BASEUP, BASEDN, COMBO_END};
const uint16_t PROGMEM web_combo[]  = {WEBUP,  WEBDN,  COMBO_END};
const uint16_t PROGMEM copy_combo[] = {COPYUP, COPYDN, COMBO_END};
const uint16_t PROGMEM meet_combo[] = {MEETUP, MEETDN, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [BASE_FN] = COMBO_ACTION(base_combo),
  [WEB_FN]  = COMBO_ACTION(web_combo),
  [COPY_FN] = COMBO_ACTION(copy_combo),
  [MEET_FN] = COMBO_ACTION(meet_combo)
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch(combo_index) {
        case BASE_FN:
        case WEB_FN:
        case COPY_FN:
        case MEET_FN:
            if (pressed) {
                default_layer_set(1UL << _FN);
            }
            break;
    }
}


void keyboard_post_init_user(void) {
    default_layer_set(1UL << _BASE);
#   ifdef RGB_MATRIX_ENABLE
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_REACTIVE_SIMPLE);
    rgb_matrix_sethsv_noeeprom(HSV_GOLDENROD);
#   endif
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
