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
    _SHIFT,
    _FLIPBASE,
    _FLIPSHIFT,
    _FN
};

#ifdef RGB_MATRIX_ENABLE

#define BASE_LAYER_COLOR  RGB_GOLDENROD
#define SHIFT_LAYER_COLOR RGB_ORANGE
#define FLIPB_LAYER_COLOR RGB_BLUE
#define FLIPS_LAYER_COLOR RGB_PURPLE

//  Don't change the DEFAULT_SCALE_COL value below. It must be 0.
#define DEFAULT_SCALE_COL 0
static uint8_t scale_indicator_col = DEFAULT_SCALE_COL;

//  use led indicator or not.
static bool led_indicator_enable = true;

// Defines names for use in _FN layer to specify which column to be used to turn on the LEDs.
// use this with led_fn_indicator[37][3], ex. led_fn_indicator[_FN_C2][0].
enum fn_key_names {
    _FN_K01= 0,
    _FN_K02,
    _FN_K03,
    _FN_K04,
    _FN_K05,
    _FN_K06,
    _FN_K07,
    _FN_K08,
    _FN_K09,
    _FN_K10,
    _FN_K11,
    _FN_K12,
    _FN_K13,
    _FN_K14,
    _FN_K15,
    _FN_K16,
    _FN_K17,
    _FN_K18,
    _FN_K19,
    _FN_K20,
    _FN_K21,
    _FN_K22,
    _FN_K23,
    _FN_K24,
    _FN_K25,
    _FN_K26,
    _FN_K27,
    _FN_K28,
    _FN_K29,
    _FN_K30,
    _FN_K31,
    _FN_K32,
    _FN_K33,
    _FN_K34,
    _FN_K35,
    _FN_K36,
    _FN_K37,
};
#endif  //  RGB_MATRIX_ENABLE

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    SHIFTDN = SAFE_RANGE,
    SHIFTUP,
    TGLINDI,  //  ToGgLeINDIcator

    L_BASE,
    L_SHIFT,
    L_FLIPB,
    L_FLIPS
};

// Long press: go to _FN layer, tap: MUTE
#define FN_MUTE LT(_FN, KC_MUTE)

// Used to set octave to MI_OCT_0
extern midi_config_t midi_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT( \
            FN_MUTE,                                                                                                                                                                             \
            MI_BENDU,                                                                                                                                                                            \
        MI_TRNSD, MI_TRNSU,  MI_C_1, MI_D_1, MI_E_1,  MI_Fs_1, MI_Ab_1, MI_Bb_1, MI_C_2, MI_D_2, MI_E_2, MI_Fs_2, MI_Ab_2, MI_Bb_2, MI_C_3,  MI_D_3,  MI_E_3, MI_Fs_3, MI_Ab_3, MI_Bb_3, MI_C_4, \
            MI_BENDD,           MI_Db_1, MI_Eb_1, MI_F_1,  MI_G_1,  MI_A_1,  MI_B_1, MI_Db_2, MI_Eb_2, MI_F_2,  MI_G_2, MI_A_2,  MI_B_2, MI_Db_3, MI_Eb_3, MI_F_3,  MI_G_3,  MI_A_3,  MI_B_3     \
    ),
    /* Shift   This layer must locate 1 layer above _BASE layer. */
    [_SHIFT] = LAYOUT( \
            _______,                                                                                                                                                                                     \
            _______,                                                                                                                                                                                     \
        SHIFTDN, SHIFTUP,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
            _______,               _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______      \
    ),

    /* Flip Base */
    [_FLIPBASE] = LAYOUT( \
            FN_MUTE,                                                                                                                                                                             \
            MI_BENDU,                                                                                                                                                                            \
        MI_TRNSU, MI_TRNSD,  MI_C_4, MI_Bb_3, MI_Ab_3,  MI_Fs_3, MI_E_3, MI_D_3, MI_C_3, MI_Bb_2, MI_Ab_2, MI_Fs_2, MI_E_2, MI_D_2, MI_C_2,  MI_Bb_1,  MI_Ab_1, MI_Fs_1, MI_E_1, MI_D_1, MI_C_1, \
            MI_BENDD,           MI_B_3, MI_A_3, MI_G_3,  MI_F_3,  MI_Eb_3,  MI_Db_3, MI_B_2, MI_A_2, MI_G_2,  MI_F_2, MI_Eb_2,  MI_Db_2, MI_B_1, MI_A_1, MI_G_1,  MI_F_1,  MI_Eb_1,  MI_Db_1     \
    ),
    /* Flip Shift   This layer must locate 1 layer above _FLIPBASE layer. */
    [_FLIPSHIFT] = LAYOUT( \
            _______,                                                                                                                                                                                     \
            _______,                                                                                                                                                                                     \
        SHIFTUP, SHIFTDN,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
            _______,               _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______      \
    ),

    [_FN] =  LAYOUT( \
            _______,                                                                                                                                                                                     \
            MI_VELU,                                                                                                                                                                                     \
        MI_OCTD, MI_OCTU,     L_BASE,  L_FLIPB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_SAI, RGB_HUI, RGB_SPI, RGB_VAI, RGB_MOD, RGB_TOG, \
            MI_VELD,               L_SHIFT, L_FLIPS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_SAD, RGB_HUD, RGB_SPD, RGB_VAD, RGB_RMOD, TGLINDI      \
    )
};

void keyboard_post_init_user(void) {
    //  Set otave to MI_OCT_0
    midi_config.octave = MI_OCT_0 - MIDI_OCTAVE_MIN;

    default_layer_set(1UL << _BASE);
};

void shift_led_indicator_left(void){
    if (scale_indicator_col > 0) {
        scale_indicator_col--;
    } else {
        scale_indicator_col = 11;
    }
}
void shift_led_indicator_right(void){
    if (scale_indicator_col < 11) {
        scale_indicator_col++;
    } else {
        scale_indicator_col = 0;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t layer = biton32(layer_state);

    switch (keycode) {

        case L_BASE:
            //  reset transpose value and scale_indicator_col to default.
            midi_config.transpose = 0;
            scale_indicator_col = DEFAULT_SCALE_COL;
            default_layer_set(1UL << _BASE);
            break;

        case L_SHIFT:
            //  reset transpose value and scale_indicator_col to default.
            midi_config.transpose = 0;
            scale_indicator_col = DEFAULT_SCALE_COL;
            default_layer_set(1UL << _SHIFT);
            break;

        case L_FLIPB:
            //  reset transpose value and scale_indicator_col to default.
            midi_config.transpose = 0;
            scale_indicator_col = DEFAULT_SCALE_COL;
            default_layer_set(1UL << _FLIPBASE);
            break;

        case L_FLIPS:
            //  reset transpose value and scale_indicator_col to default.
            midi_config.transpose = 0;
            scale_indicator_col = DEFAULT_SCALE_COL;
            default_layer_set(1UL << _FLIPSHIFT);
            break;

        //  SHIFTDN and SHIFTUP can be pressed only when layer is _SHIFT or _FLIPSHIFT.
        case SHIFTDN:
            if (record->event.pressed) {
                switch (layer) {
                    case _SHIFT:
                        shift_led_indicator_left();
                        break;

                    case _FLIPSHIFT:
                        shift_led_indicator_right();
                        break;
                }
            }
            break;
        case SHIFTUP:
            if (record->event.pressed) {
                switch (layer) {
                    case _SHIFT:
                        shift_led_indicator_right();
                        break;

                    case _FLIPSHIFT:
                        shift_led_indicator_left();
                        break;
                }
            }
            break;

        case TGLINDI:
            led_indicator_enable = !led_indicator_enable;
            break;
    }
    return true;
}

void set_led_scale_indicator(uint8_t r, uint8_t g, uint8_t b) {
    uint8_t max_scale_indicator_led_loop;
    uint8_t i;
    if (led_indicator_enable) {  //  turn on indicators when enabled.
        max_scale_indicator_led_loop = scale_indicator_col = DEFAULT_SCALE_COL ? 12 : 9;
        for (i = 0; i < max_scale_indicator_led_loop; i++) {
            rgb_matrix_set_color(led_scale_indicator[scale_indicator_col][i], r, g, b);
        }
    }
}

#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_indicators_user(void) {
    // uint32_t mode = rgblight_get_mode();

    if (rgb_matrix_is_enabled()) {  // turn the lights on when it is enabled.

        uint8_t layer = biton32(layer_state);
        // uint8_t max_scale_indicator_led_loop;
        uint8_t i;

        switch (layer) {
            case _BASE:
                //  midi_config.transpose range: -6..+6.
                //  scale_indicator_col   range: 0..11
                //  at the base layer, scale indicator has to move the opposite way.
                if ( midi_config.transpose <= 0 ) {  // 0 is included.
                  scale_indicator_col = -1 * midi_config.transpose;
                } else {  // 0 can't be included here since max scale_indicator_col is 11.
                  scale_indicator_col = 12 - midi_config.transpose;
                }
                set_led_scale_indicator(BASE_LAYER_COLOR);
                break;

            case _FLIPBASE:
                //  midi_config.transpose range: -6..+6.
                //  scale_indicator_col   range: 0..11
                //  at the flipped base layer, scale indicator has to move the same way.
                if ( midi_config.transpose < 0 ) {  // 0 is excluded.
                  scale_indicator_col = 12 + midi_config.transpose;
                } else {  // 0 is included.
                  scale_indicator_col = midi_config.transpose;
                }
                set_led_scale_indicator(FLIPB_LAYER_COLOR);
                break;

            case _SHIFT:
                set_led_scale_indicator(SHIFT_LAYER_COLOR);
                break;

            case _FLIPSHIFT:
                set_led_scale_indicator(FLIPS_LAYER_COLOR);
                break;

            case _FN:
                for (i = 1; i < 5; i++) {
                    rgb_matrix_set_color(i, RGB_SPRINGGREEN);  //  up(1) down(4) left(3) right(2)  keys
                }
                for (i = 0; i < 3; i++) {
                    rgb_matrix_set_color(led_fn_indicator[_FN_K01][i], BASE_LAYER_COLOR);    //  L_BASE
                    rgb_matrix_set_color(led_fn_indicator[_FN_K02][i], SHIFT_LAYER_COLOR);   //  L_SHIFT
                    rgb_matrix_set_color(led_fn_indicator[_FN_K03][i], FLIPB_LAYER_COLOR);   //  L_FLIPB
                    rgb_matrix_set_color(led_fn_indicator[_FN_K04][i], FLIPS_LAYER_COLOR);   //  L_FLIPS
                }

                for (i = _FN_K26; i <= _FN_K37; i++){
                    // turn on the bottom row only to keep the visibility of the RGB MATRIX effects.
                    rgb_matrix_set_color(led_fn_indicator[i][0], RGB_SPRINGGREEN);  //       //  LED related settings.
                }
                break;
        }
    }
}
#endif

#ifdef ENCODER_ENABLE
void encoder_update_user(int8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
}
#endif  // ENCODER_ENABLE
