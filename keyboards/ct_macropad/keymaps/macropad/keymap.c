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

#define SPOTLGT LGUI(KC_SPC)
#define CHARACT LGUI(LCTL(KC_SPC))
#define TOGFSCR LGUI(LCTL(KC_F))
#define SCRSHOT SGUI(KC_5)
#define SCRLOCK LGUI(LCTL(KC_Q))

#define WEBUP LGUI(KC_T)
#define WEBDN LGUI(KC_N)
#define COPYUP LGUI(KC_O)
#define COPYDN LGUI(KC_Z)
#define MEETUP C(S(KC_M))
#define MEETDN C(KC_F)

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _WEB,
    _COPY,
    _MEET,
    _FN
};

enum custom_keycodes {
    BASEUP = SAFE_RANGE,
    BASEDN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT_macropad( \
        BASEUP,   MI_C_3, MI_Db_3, MI_D_3, MI_Eb_3, MI_E_3, \
                          MI_Db_3,         MI_Eb_3,         \
        BASEDN,   MI_C_3,          MI_D_3,          MI_E_3  \
    ),
    // https://osxdaily.com/2012/04/03/safari-keyboard-shortcuts/
    [_WEB] = LAYOUT_macropad( \
        WEBUP, LGUI(KC_L),    RCS(KC_TAB),   LCTL(KC_TAB), S(KC_SPC),    KC_SPC,           \
                              LGUI(KC_MINS),               LGUI(KC_EQL),                   \
        WEBDN, LGUI(KC_LEFT),                LGUI(KC_R),                 LGUI(KC_RIGHT)    \
    ),
    // Basic shortcuts
    // https://support.apple.com/en-us/HT201236
    [_COPY] = LAYOUT_macropad( \
        COPYUP, SPOTLGT,    CHARACT,    TOGFSCR,    SCRSHOT,    SCRLOCK,   \
                            LGUI(KC_A),             LGUI(KC_F),            \
        COPYDN, LGUI(KC_X),             LGUI(KC_C),             LGUI(KC_V) \
    ),
    // Shortcuts for meetings
    // Used for OBS, Teams, etc.
    [_MEET] = LAYOUT_macropad( \
        MEETUP, LSA(KC_F6), LSA(KC_F7), LSA(KC_F8), LSA(KC_F9), LSA(KC_F10), \
                            LSA(KC_F2),             LSA(KC_F4),              \
        MEETDN, LSA(KC_F1),             LSA(KC_F3),             LSA(KC_F5)   \
    ),
    // Somehow neither TO/TG worked. DF used.
    [_FN] = LAYOUT_macropad( \
        RGB_MOD,   RGB_TOG,  RGB_VAD, RGB_VAI,   RGB_SPD, RGB_SPI,  \
                             RGB_SAD,            RGB_SAI,           \
        DF(_BASE), DF(_WEB),          DF(_COPY),          DF(_MEET) \
    )
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
    // default_layer_set(1UL << _BASE);  // this is not necessary. it returns to _BASE anyway, somehow.
#   ifdef RGB_MATRIX_ENABLE
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_REACTIVE_SIMPLE);
    rgb_matrix_sethsv_noeeprom(HSV_GOLDENROD);
#   endif
};

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case BASEUP:
            process_midi(MI_BENDU, record);
            // process_midi(MI_OCTU, record);
            break;
        case BASEDN:
            process_midi(MI_BENDD, record);
            // process_midi(MI_OCTD, record);
            break;
    }
    return true;
}
