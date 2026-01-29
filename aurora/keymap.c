/*
 * Copyright (c) 2017 Your Name <you@example.com>
 * Copyright (c) 2020 Another Author <author@example.com>
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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */   

#include "keymap_danish.h"
#include "keymap.h"
//
// Declare functions or variables related to tap dance keys
 //Our custom tap dance keys; add any other tap dance keys to this enum
enum {
    TD_DELETE,
    TD_BSPACE,
    TD_AE_ENTER,
    TD_AA_DK,
    TD_OE_DK,
    TD_APP_TAB,
    TD_HOME_P,
    TD_END_N,
    TD_ESC_TM,
    TD_NEXT_T,
    TD_PREV_T,
    ALT_OSL1,
    TD_OSM_SCAW,
    TD_LEFT_SKIP,
    TD_RIGHT_SKIP
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP,
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    bool recording;
    td_state_t state;
} td_tap_t;

// Declare functions
td_state_t cur_dance(tap_dance_state_t *state);
void td_delete(tap_dance_state_t *state, void *user_data);
void td_bspace(tap_dance_state_t *state, void *user_data);
void td_ae_enter(tap_dance_state_t *state, void *user_data);
void td_aa(tap_dance_state_t *state, void *user_data);
void td_oe(tap_dance_state_t *state, void *user_data);
void td_apptab_switch(tap_dance_state_t *state, void *user_data);
void td_home_prev(tap_dance_state_t *state, void *user_data);
void td_end_next(tap_dance_state_t *state, void *user_data);
void td_esc_tm(tap_dance_state_t *state, void *user_data);
void td_next_tab(tap_dance_state_t *state, void *user_data);
void td_prev_tab(tap_dance_state_t *state, void *user_data);
void td_osm_sft_ctl_alt(tap_dance_state_t *state, void *user_data);
void td_left_skip_each_tap(tap_dance_state_t *state, void *user_data);
void td_left_skip_finished(tap_dance_state_t *state, void *user_data);
void td_left_skip_reset(tap_dance_state_t *state, void *user_data);
void td_right_skip_each_tap(tap_dance_state_t *state, void *user_data);
void td_right_skip_finished(tap_dance_state_t *state, void *user_data);
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record);
uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record);


// define the various layers
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
    // Base key input layer------------------- 			------------------------------------------------
    TD(TD_ESC_TM), KC_W, KC_E, KC_R, KC_T,/*split */ 			KC_Y, KC_U, KC_I, TD(TD_OE_DK), KC_P,
    //----------------------------------------- 		-----------------------------------------------
    TD(TD_AA_DK), MT(MOD_LSFT,KC_S), MT(MOD_LALT,KC_D), MT(MOD_LCTL,KC_F), MT(MOD_LGUI,KC_G),/*split*/ MT(MOD_RGUI,KC_H),MT(MOD_RCTL,KC_J), MT(MOD_RALT,KC_K), MT(MOD_RSFT,KC_L), TD(TD_AE_ENTER),
    //----------------------------------------- 		-----------------------------------------------
    KC_Z, KC_X , KC_C, KC_V, TD(TD_DELETE),/*split*/ 		KC_B, KC_N, KC_M, KC_COMM, KC_DOT,
    //-----------------------------------------                                     -----------------------------------------------
                TO(_QWERTY), MT(MOD_LSFT, KC_SPC), /*split*/                             OSL(_SYMB), TD(TD_OSM_SCAW)
    ),

    [_SYMB] = LAYOUT(
    // Signs and symbols layer, from layer 0 --                                     ----------------------------------------
    LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_4), LSFT(KC_5), /*split*/            LSFT(KC_6), LSFT(KC_7), KC_NO, KC_SLSH, LSFT(KC_SLSH),
    // ----------------------------------------                                     ----------------------------------------------
    KC_EQL, LSFT(KC_EQL), LSFT(KC_2), KC_NUHS, KC_PAST, /*split*/                   LSFT(KC_1), LSFT(KC_8), LSFT(KC_9), LSFT(KC_MINS), ALGR(KC_EQL),
    // ----------------------------------------                                     ----------------------------------------------
    KC_NUBS, LSFT(KC_NUBS), ALGR(KC_RBRC), KC_RBRC, ALGR(KC_NUBS), /*split*/              ALGR(KC_8), ALGR(KC_7), ALGR(KC_0), ALGR(KC_9), TO(_NAV),
    // ----------------------------------------                                     ----------------------------------------------
                            KC_TRNS, KC_TRNS, /*split*/                            TO(_NMPAD), KC_TRNS
    ),

    [_NMPAD] = LAYOUT(
    // Numpad layer, from layer 1 ----------                                     ---------------------------------------------
    KC_TRNS, KC_NO, LSFT(KC_0), KC_PPLS, KC_PMNS, /*split*/                                  KC_COMM, KC_7, KC_8, KC_9, TD(TD_BSPACE),
    // ----------------------------------------                                     ---------------------------------------------
    TD(TD_APP_TAB),MT(MOD_LSFT,KC_NO), MT(MOD_LALT,KC_NO),MT(MOD_LCTL,KC_PSLS), MT(MOD_LGUI,KC_PAST), /*split*/                                KC_PERC, KC_4, KC_5, KC_6, KC_ENT,
    // ----------------------------------------                                     ---------------------------------------------
    KC_LSFT, KC_LCTL, KC_LGUI, KC_LALT, KC_TRNS, /*split*/                                   KC_0, KC_1, KC_2, KC_3, KC_DOT,
    // ----------------------------------------                                     ---------------------------------------------
                                KC_TRNS, KC_TRNS, /*split*/                                  TO(_FKEY), KC_TRNS
    ),

    [_NAV] = LAYOUT(
    // Navigation layer, from base layer 0 ---                                     --------------------------------------------
    TD(TD_ESC_TM), MS_WHLL, MS_UP, MS_WHLR, MS_WHLU, /*split*/                             TD(TD_HOME_P), TD(TD_PREV_T), TD(TD_NEXT_T), TD(TD_END_N), TD(TD_BSPACE),
    // ----------------------------------------                                     --------------------------------------------
    TD(TD_APP_TAB), MS_LEFT, MS_DOWN, MS_RGHT, MS_WHLD, /*split*/                            TD(TD_LEFT_SKIP), KC_DOWN, KC_UP, TD(TD_RIGHT_SKIP), KC_ENT,
    // ----------------------------------------                                     --------------------------------------------
    MS_BTN2, LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), TD(TD_DELETE), /*split*/                    MS_ACL0, MS_ACL1, MS_ACL2, KC_PGDN, KC_PGUP,
    // ----------------------------------------                                     --------------------------------------------
                            KC_TRNS, KC_TRNS, /*split*/                                      MS_BTN1, TD(TD_OSM_SCAW)
    ),

    [_FKEY] = LAYOUT(
    // F Key layer, from _NMPAD layer ---------                                   --------------------------------------------
    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, /*split*/                                    KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,
    // ----------------------------------------                                     ---------------------------------------------
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, /*split*/                                    KC_NO, KC_NO, KC_NO, KC_F11, KC_F12,
    // ----------------------------------------                                     ---------------------------------------------
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, /*split*/                                    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    // ----------------------------------------                                     ---------------------------------------------
                                KC_TRNS, KC_TRNS, /*split*/                         KC_NO, KC_TRNS
    ),
};

// commented for troubleshoot reasons
/* Defining all macros for oneshot layers
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_TRNS:
    case KC_NO:
      // Always cancel one-shot layer when another key gets pressed
      if (record->event.pressed && is_oneshot_layer_active()){
      clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
      return true;
      }
    case QK_BOOTLOADER:
      // Don't allow reset from oneshot layer state
      if (record->event.pressed && is_oneshot_layer_active()){
        clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
        return false;
      }
      return true;
    default:
      return true;
  }
  return true;
}
*/



/*
uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(TD_LEFT_SKIP):
            return QUICK_TAP_TERM - 20;
        default:
            return QUICK_TAP_TERM;
    }
}
*/

// old code from here

// -------------------------------------------------------------------------------------
// ONESHOT MOD INITIALISATION
// -------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------
// MACRO INITIALISATION
// -------------------------------------------------------------------------------------



#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
//
// create a global instance of the tapdance state type
static td_tap_t tap_state = {.state = TD_NONE};


// -------------------------------------------------------------------------------------
// TAP DANCE INITIALISATION
//------------------------------------------------------------------------------------
// initiate handlers to define the types of taps


// general function to define what type of tap to handle
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else
            return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted)
            return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed)
            return TD_DOUBLE_HOLD;
        else
            return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed)
            return TD_TRIPLE_TAP;
        else
            return TD_TRIPLE_HOLD;
    } else
        return TD_UNKNOWN;
}

// example of a full tap dance function structure
void td_send_success_strings(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            SEND_STRING("key tapped once");
            break;
        case TD_DOUBLE_TAP:
            SEND_STRING("key tapped twice");
            break;
        case TD_SINGLE_HOLD:
            SEND_STRING("key held once");
            break;
        case TD_DOUBLE_HOLD:
            SEND_STRING("key held twice");
            break;
        case TD_TRIPLE_TAP:
            SEND_STRING("key tapped thrice");
            break;
        case TD_TRIPLE_HOLD:
            SEND_STRING("key held thrice");
            break;
        default:
            break;
    }
}

// defining DK å
void td_aa(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_A);
            break;
        case TD_DOUBLE_TAP:
            tap_code(KC_A);
            tap_code(KC_A);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            tap_code(KC_A);
            tap_code(KC_A);
            break;
        case TD_SINGLE_HOLD:
            tap_code(KC_LBRC);
            break;
        default:
            break;
    }
}

// defining temporary ø
void td_oe(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_O);
            break;
        case TD_DOUBLE_TAP:
            tap_code(KC_O);
            tap_code(KC_O);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            tap_code(KC_O);
            tap_code(KC_O);
            break;
        case TD_SINGLE_HOLD:
            tap_code(KC_QUOT);
            break;
        default:
            break;
    }
}

// defining delete key macro
void td_delete(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_DEL);
            break;
        case TD_SINGLE_HOLD:
            SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_DEL) SS_UP(X_LCTL));
            break;
        case TD_DOUBLE_HOLD:
            SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_END) SS_TAP(X_DEL) SS_UP(X_LSFT) SS_UP(X_END));
            break;
        default:
            break;
    }
}

// defining backspace key macro
void td_bspace(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_BSPC);
            break;
        case TD_DOUBLE_TAP:
            tap_code(KC_BSPC);
            tap_code(KC_BSPC);
            break;
        case TD_TRIPLE_TAP:
            tap_code(KC_BSPC);
            tap_code(KC_BSPC);
            tap_code(KC_BSPC);
            break;
        case TD_SINGLE_HOLD:
            SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_BSPC) SS_UP(X_LCTL));
            break;
        case TD_DOUBLE_HOLD:
            SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_HOME) SS_TAP(X_BSPC) SS_UP(X_LSFT) SS_UP(X_HOME));

            break;
        default:
            break;
    }
}

// enable keyboard reset key
// CURRENTLY NOT IN USE
void safe_reset(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_HOLD:
            SEND_STRING("keyboard should be reset now");
            reset_keyboard();
            break;
        default:
            break;
    }
}

// defining app and tab switcher tapdance key
void td_apptab_switch(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_TAB);
            break;
        case TD_DOUBLE_TAP:
            tap_code(KC_TAB);
            tap_code(KC_TAB);
            break;
        case TD_TRIPLE_TAP:
            tap_code(KC_TAB);
            tap_code(KC_TAB);
            tap_code(KC_TAB);
            break;
        case TD_SINGLE_HOLD:
            SEND_STRING(SS_DOWN(X_LALT) SS_DOWN(X_LCTL) SS_TAP(X_TAB) SS_UP(X_LALT) SS_UP(X_LCTL) );
            break;
        case TD_DOUBLE_HOLD:
            SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_TAB) SS_UP(X_LCTL));
        break;
        case TD_TRIPLE_HOLD:
            SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_TAB) SS_UP(X_LGUI));
        default:
            break;
    }
}

// defining esc and task manager tapdance key
    void td_esc_tm(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_ESCAPE);
            break;
        case TD_DOUBLE_HOLD:
            SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_LALT) SS_TAP(X_DEL) SS_UP(X_LCTL) SS_UP(X_LALT));
            break;
        default:
            break;
    }
}

// defining ae and enter tapdance
void td_ae_enter(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_SCLN);
            break;
        case TD_DOUBLE_TAP:
            tap_code(KC_ENT);
            break;
        default:
            reset_tap_dance(state);
            break;
    }
}

// defining previous tab tapdance key
void td_prev_tab(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_LSFT) SS_TAP(X_TAB) SS_UP(X_LCTL) SS_UP(X_LSFT));
            break;
        default:
            break;
    }
}

// defining next tab tapdance key
void td_next_tab(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_TAB) SS_UP(X_LCTL));
            break;
        default:
            break;
    }
}

// defining home and previous desktop tapdance key
void td_home_prev(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_HOME);
            break;
        case TD_DOUBLE_TAP:
            SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_LEFT) SS_UP(X_LCTL));
            break;
        case TD_SINGLE_HOLD:
            SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_LEFT) SS_UP(X_LALT));
            break;
        default:
            break;
    }
}

// defining end and next desktop tapdance key
void td_end_next(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_END);
            break;
        case TD_DOUBLE_TAP:
            SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_RIGHT) SS_UP(X_LCTL));
            break;
        case TD_SINGLE_HOLD:
            SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_RIGHT) SS_UP(X_LALT));
        default:
            break;
    }
}

// defining one shot mod shift-ctrl-alt and next desktop tapdance key
void td_osm_sft_ctl_alt(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            set_oneshot_mods(MOD_LSFT);
            break;
        case TD_DOUBLE_TAP:
	    //this should ideally be caps word toggle but is currently difficult to implement
            set_oneshot_mods(MOD_LCTL);
            break;
        case TD_TRIPLE_TAP:
            set_oneshot_mods(MOD_LALT);
            break;
        case TD_SINGLE_HOLD:
            set_oneshot_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT));
            break;
        case TD_DOUBLE_HOLD:
            set_oneshot_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_LGUI));
            break;
        case TD_TRIPLE_HOLD:
            set_oneshot_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT) | MOD_BIT(KC_LALT));
            break;
        default:
            break;
    }
}

void td_left_skip_each_tap(tap_dance_state_t *state, void *user_data) {
    tap_code(KC_LEFT);
}

void td_left_skip_finished(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_HOLD:
            register_code(KC_LEFT);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LCTL);
            register_code(KC_LEFT);
            break;
        default:
            break;
    }
}

void td_left_skip_reset(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_HOLD:
//          unregister_code(KC_LEFT);
            SEND_STRING("left skip single reset");
            break;
        case TD_DOUBLE_HOLD:
//            unregister_code(KC_LCTL);
//            unregister_code(KC_LEFT);
            SEND_STRING("left skip double reset");
            break;

        default:
            break;
    }
    tap_state.state = TD_NONE;
    unregister_code(KC_LCTL);
    unregister_code(KC_LEFT);

}

void td_right_skip_each_tap(tap_dance_state_t *state, void *user_data) {
    tap_code(KC_RIGHT);
}

void td_right_skip_finished(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_RIGHT);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LCTL);
            register_code(KC_RIGHT);
            break;
        default:
            break;
    }
}

void td_right_skip_reset(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_HOLD:
            break;
        default:
            break;
    }
    tap_state.state = TD_NONE;
    unregister_code(KC_LCTL);
    unregister_code(KC_RIGHT);
}

// define per key tapping term
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        /*case TD(TD_OSM_SCAW):
            return 150;*/
        case TD(TD_BSPACE):
            return 150;
        case TD(TD_DELETE):
            return 150;
        default:
            return TAPPING_TERM;
    }
}

//Associate our tap dance key with its functionality
tap_dance_action_t tap_dance_actions[] = {
    [TD_DELETE] = ACTION_TAP_DANCE_FN(td_delete),
    [TD_BSPACE] = ACTION_TAP_DANCE_FN(td_bspace),
    [TD_AE_ENTER] = ACTION_TAP_DANCE_FN(td_ae_enter),
    [TD_AA_DK] = ACTION_TAP_DANCE_FN(td_aa),
    [TD_OE_DK] = ACTION_TAP_DANCE_FN(td_oe),
    [TD_APP_TAB] = ACTION_TAP_DANCE_FN(td_apptab_switch),
    [TD_HOME_P] = ACTION_TAP_DANCE_FN(td_home_prev),
    [TD_END_N] = ACTION_TAP_DANCE_FN(td_end_next),
    [TD_ESC_TM] = ACTION_TAP_DANCE_FN(td_esc_tm),
    [TD_NEXT_T] = ACTION_TAP_DANCE_FN(td_next_tab),
    [TD_PREV_T] = ACTION_TAP_DANCE_FN(td_prev_tab),
    //[ALT_OSL1]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL,alt_finished, alt_reset), // skipped because function is not finished yet
    [TD_OSM_SCAW] = ACTION_TAP_DANCE_FN(td_osm_sft_ctl_alt),
    [TD_LEFT_SKIP] = ACTION_TAP_DANCE_FN_ADVANCED(td_left_skip_each_tap, td_left_skip_finished, td_left_skip_reset),
    [TD_RIGHT_SKIP] = ACTION_TAP_DANCE_FN_ADVANCED(td_right_skip_each_tap, td_right_skip_finished, td_right_skip_reset),
};
