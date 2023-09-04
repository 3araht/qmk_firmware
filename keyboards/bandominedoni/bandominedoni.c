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

#include "bandominedoni.h"
#include "version.h"

static uint8_t midi_sub_ch = DEFAULT_SUB_CH_NUMBER;       //  By default, DEFAULT_SUB_CH_NUMBER is used for sub ch.

//  By default( when use_alt_ch_gr == false), DEFAULT ch group (DEFAULT_MAIN_CH_NUMBER for entirely, or right side when separated, DEFAULT_SUB_CH_NUMBER for left side) is used.
//  When false, ALT ch group (ALT_MAIN_CH_NUMBER for entirely, or right side when separated, ALT_SUB_CH_NUMBER for left side) is used.
static bool use_alt_ch_gr = false;

static uint8_t my_tone_status[MY_TONE_COUNT];

static void st_process_midi4single_note(uint8_t channel, uint16_t keycode, keyrecord_t *record, uint8_t *my_tone_status) {
    uint8_t  mytone    = keycode - MY_TONE_MIN;
    uint16_t mykeycode = mytone + MIDI_TONE_MIN;
    // uint16_t mykeycode = keycode - MY_TONE_MIN;
    // uint8_t  mytone    = mykeycode - MIDI_TONE_MIN;
    uint8_t  velocity  = midi_config.velocity;
    // uprintf("keycode=%u,mykeycode=%u,mytone =%u,velo = %u\n", keycode, mykeycode, mytone, velocity);
    if (record->event.pressed) {
        if (my_tone_status[mytone] == MIDI_INVALID_NOTE) {
            uint8_t note = midi_compute_note(mykeycode);
            midi_send_noteon(&midi_device, channel, note, velocity);
            dprintf("midi noteon channel:%d note:%d mytone:%d velocity:%d\n", channel, note, mytone, velocity);
            // uprintf("midi noteon channel:%d note:%d mytone:%d velocity:%d\n", channel, note, mytone, velocity);
            my_tone_status[mytone] = note;  // store root_note status.
        }
    } else {
        uint8_t note = my_tone_status[mytone];
        if (note != MIDI_INVALID_NOTE) {
            midi_send_noteoff(&midi_device, channel, note, velocity);
            dprintf("midi noteoff channel:%d note:%d velocity:%d\n", channel, note, velocity);
            // uprintf("midi noteoff channel:%d note:%d velocity:%d\n", channel, note, velocity);
        }
        my_tone_status[mytone] = MIDI_INVALID_NOTE;
    }
}

void my_process_midi4single_note(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case  MY_TONE_MIN ... MY_TONE_MAX:  // MY tone
            st_process_midi4single_note(midi_sub_ch, keycode, record, my_tone_status);
            break;
    }
}

void my_bellow_task(bool keys_status) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        const matrix_row_t current_row = matrix_get_row(row);

        if (!current_row) {     // If there is no key pressed, continue.
            continue;
        }

        matrix_row_t col_mask = 1;
        for (uint8_t col = 0; col < MATRIX_COLS; col++, col_mask <<= 1) {
            const bool key_pressed = current_row & col_mask;
            if (key_pressed) {
                keyrecord_t record = {.event = MAKE_KEYEVENT(row, col, keys_status)};
                uint16_t keycode = get_record_keycode(&record, true);

                // my_bellow_task runs when MYMOSWP is pressed. MYMOSWP has to be ignored here.
                // All MIDI notes will be turned ON when keys_status is KEYS_STATUS_ON, and vice versa.
                my_process_midi4single_note(keycode, &record);
                process_midi(keycode, &record);
            }
        }
    }
}

#if defined(SPLIT_HAND_MATRIX_GRID)
static uint8_t peek_matrix_intersection(pin_t out_pin, pin_t in_pin) {
    setPinInputHigh(in_pin);
    setPinOutput(out_pin);
    writePinLow(out_pin);
    // It's almost unnecessary, but wait until it's down to low, just in case.
    wait_us(1);
    uint8_t pin_state = readPin(in_pin);
    // Set out_pin to a setting that is less susceptible to noise.
    setPinInputHigh(out_pin);
    matrix_io_delay();  // Wait for the pull-up to go HIGH.
    return pin_state;
}
#endif

//  Overriding is_keyboard_left() in qmk_firmware/quantum/split_common/split_util.c to limit the handedness check only once.
//  reason: bandoMIneDonI has no space on right hand side to use "SPLIT_HAND_MATRIX_GRID".
//          However, It enables to decide the handedness by the HW by adding one condition: "not to press any keys (especially r30) dusing startup."
bool is_keyboard_left(void) {
static enum { UNKNOWN, LEFT, RIGHT } hand_side = UNKNOWN;

    // only check once, as this is called often
    if (hand_side == UNKNOWN) {
#if defined(SPLIT_HAND_PIN)
        // Test pin SPLIT_HAND_PIN for High/Low, if low it's right hand
        setPinInput(SPLIT_HAND_PIN);
        hand_side = readPin(SPLIT_HAND_PIN) ? LEFT : RIGHT;
        return (hand_side == LEFT);
#elif defined(SPLIT_HAND_MATRIX_GRID)
#    ifdef SPLIT_HAND_MATRIX_GRID_LOW_IS_RIGHT
        hand_side = peek_matrix_intersection(SPLIT_HAND_MATRIX_GRID) ? LEFT : RIGHT;
        return (hand_side == LEFT);
#    else
        hand_side = peek_matrix_intersection(SPLIT_HAND_MATRIX_GRID) ? RIGHT : LEFT;
        return (hand_side == LEFT);
#    endif
#elif defined(EE_HANDS)
        hand_side = eeconfig_read_handedness() ? LEFT : RIGHT;
        return (hand_side == LEFT);
#elif defined(MASTER_RIGHT)
        hand_side = !is_keyboard_master() ? LEFT : RIGHT;
        return (hand_side == LEFT);
#endif
        hand_side = is_keyboard_master() ? LEFT : RIGHT;
        return (hand_side == LEFT);
    } else {
        return (hand_side == LEFT);
    }
}

void my_init(void){
#ifndef VIA_ENABLE
    for (uint8_t i = 0; i < MY_TONE_COUNT; i++) {
        my_tone_status[i] = MIDI_INVALID_NOTE;
    }
#endif

    //  Set octave to 0
    midi_config.octave = QK_MIDI_OCTAVE_0 - MIDI_OCTAVE_MIN;

    // avoid using 127 since it is used as a special number in some sound sources.
    midi_config.velocity = MIDI_INITIAL_VELOCITY;
}

void eeconfig_init_kb(void) {
    midi_init();
    my_init();
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_enable();
    rgb_matrix_set_speed(RGB_MATRIX_DEFAULT_SPD);
    rgb_matrix_sethsv(HSV_BLUE);

    rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE);
    // rgb_matrix_mode(RGB_MATRIX_RAINBOW_MOVING_CHEVRON);
#endif
    eeconfig_init_user();
}

void keyboard_post_init_kb(void) {
    my_init();

#ifdef RGB_MATRIX_ENABLE
#   ifndef VIA_ENABLE
    //  party mode (for LED soldering test. Enable rainbow color effect, and disable led_indicator to check all LEDs)
    rgb_matrix_mode(RGB_MATRIX_RAINBOW_MOVING_CHEVRON);
#   else
    rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE);
#   endif
#endif

    keyboard_post_init_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case VERSION: // Output firmware info.
            if (record->event.pressed) {
                SEND_STRING(QMK_KEYBOARD ":" QMK_KEYMAP " @ " QMK_VERSION " " QMK_GIT_HASH " | " QMK_BUILDDATE);
            }
            return false;
            break;

        case TGLCHGR:
            if (record->event.pressed) {
                use_alt_ch_gr = !use_alt_ch_gr;
                if (use_alt_ch_gr) {
                    midi_sub_ch = ALT_SUB_CH_NUMBER;
                } else {  //  default
                    midi_sub_ch = DEFAULT_SUB_CH_NUMBER;
                }
            }
            return false;
            break;

        case  MY_TONE_MIN ... MY_TONE_MAX:  // MY tone
            // uprintf("keycode=%u, MY_C3=%u, MY_Db2 =%u, MY_MIN = %u, MY_MAX = %u\n", keycode, MY_C3, MY_Db2, MY_TONE_MIN, MY_TONE_MAX);
            //  DO NOT THROW BELOW into 'if (record->event.pressed) {}' STATEMENT SINCE IT IS USED IN THE FUNCTION BELOW.
            st_process_midi4single_note(midi_sub_ch, keycode, record, my_tone_status);
            return false;
            break;
    }
    return true;
}
