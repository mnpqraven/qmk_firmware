#include "othi.h"

static uint8_t shift_pressed;
enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD = 2,
    DOUBLE_TAP = 3,
    DOUBLE_HOLD = 4,
    DOUBLE_SINGLE_TAP = 5, //send two single taps
    TRIPLE_TAP = 6,
    TRIPLE_HOLD = 7,
    SPECIAL = 8
};

typedef struct {
    bool is_press_action;
    int state;
} tap;

int cur_dance (qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed)  return SINGLE_TAP;
        //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
        else return SINGLE_HOLD;
    }
    else if (state->count == 2) {
        /*
         * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
         * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
         * keystrokes of the key, and not the 'double tap' action/macro.
         */
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    //Assumes no one is trying to type the same letter three times (at least not quickly).
    //If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    //an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    }
    else return 8; //magic number. At some point this method will expand to work for more presses
}

int hold_cur_dance (qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted) {
            if (!state->pressed) return SINGLE_TAP;
            else return SINGLE_HOLD;
        }
        else {
            if (!state->pressed) return SINGLE_TAP;
            else return SINGLE_HOLD;
        }
    }
    //If count = 2, and it has been interrupted - assume that user is trying to type the letter associated
    //with single tap.
    else if (state->count == 2) {
        if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    else if (state->count == 3) {
        if (!state->pressed) return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    }
    else return SPECIAL;
}

static tap xtap_state = {
    .is_press_action = true,
    .state = 0
};

//QMK example of quad function tap dance, sends x/control/esc/alt respectively on tap/hold/double tap/double hold
void x_finished (qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_X); break;
        case SINGLE_HOLD: register_code(KC_LCTL); break;
        case DOUBLE_TAP: register_code(KC_ESC); break;
        case DOUBLE_HOLD: register_code(KC_LALT); break;
        case DOUBLE_SINGLE_TAP: register_code(KC_X); unregister_code(KC_X); register_code(KC_X);
                                //Last case is for fast typing. Assuming your key is `f`:
                                //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
                                //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
    }
}

void x_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP: unregister_code(KC_X); break;
        case SINGLE_HOLD: unregister_code(KC_LCTL); break;
        case DOUBLE_TAP: unregister_code(KC_ESC); break;
        case DOUBLE_HOLD: unregister_code(KC_LALT);
        case DOUBLE_SINGLE_TAP: unregister_code(KC_X);
    }
    xtap_state.state = 0;
}

void dance_CTL_NM_finished (qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_LCTL); break;
        case SINGLE_HOLD: register_code(KC_LCTL); break;
        case DOUBLE_HOLD: register_code (KC_LCTL);
                          layer_on(NM_MODE); break;
    }
}

void dance_CTL_NM_each (qk_tap_dance_state_t *state, void *user_data) {
    //version 1: 1st backspace starts at double tap
    if (state->count >= 2) {
        tap_code(KC_BSPC);
    }
    //version2: double tap produces 2 backspaces, so muscle memory remains but you might have to retype a character
    //if (state->count == 2) {
    //tap_code(KC_BSPC);
    //tap_code(KC_BSPC);
    //} else if (state->count > 2) {
    //tap_code(KC_BSPC);
    //}
}
void dance_CTL_NM_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP: unregister_code(KC_LCTL); break;
        case SINGLE_HOLD: unregister_code(KC_LCTL); break;
        case DOUBLE_HOLD: unregister_code(KC_LCTL);
                          layer_off(NM_MODE); break;
    }
    xtap_state.state = 0;
}

void dance_GUI_NM_finished (qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_HOLD:
            register_code(KC_LGUI);
#ifdef RGBLIGHT_ENABLE
            rgblight_sethsv_noeeprom_magenta(); rgblight_mode_noeeprom(1);
#endif
            break;
        case DOUBLE_HOLD:
            register_code (KC_LGUI);
            layer_on(NM_MODE); break;
    }
}

void dance_GUI_NM_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_HOLD:
            unregister_code(KC_LGUI);
#ifdef RGBLIGHT_ENABLE
            rgblight_sethsv_noeeprom(OTHI_DEFAULT_R, OTHI_DEFAULT_G, OTHI_DEFAULT_B); rgblight_mode_noeeprom(OTHI_DEFAULT_MODE);
#endif
            break;
        case DOUBLE_HOLD:
            unregister_code (KC_LGUI);
            layer_off(NM_MODE); break;
    }
    xtap_state.state = 0;
}

void dance_ALT_NM_finished (qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP:
            register_code (KC_LALT);
            break;
        case SINGLE_HOLD:
            register_code (KC_LALT);
            break;
        case DOUBLE_HOLD:
            register_code (KC_LALT);
            layer_on(NM_MODE);
            break;
        case TRIPLE_HOLD:
            register_code (KC_LALT);
            register_code (KC_LCTL);
            layer_on(NM_MODE);
#ifdef RGBLIGHT_ENABLE
            rgblight_sethsv_noeeprom_orange(); rgblight_mode_noeeprom(1);
#endif //RGBLIGHT_ENABLE
    }
}

void dance_ALT_NM_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP:
            unregister_code (KC_LALT);
            break;
        case SINGLE_HOLD:
            unregister_code (KC_LALT);
            break;
        case DOUBLE_HOLD:
            unregister_code (KC_LALT);
            layer_off(NM_MODE);
            break;
        case TRIPLE_HOLD:
            unregister_code (KC_LALT);
            unregister_code (KC_LCTL);
            layer_off(NM_MODE);
    }
    xtap_state.state = 0;
}

void dance_SFT_NM_finished (qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP:
            register_code (KC_LSFT);
#ifdef RGBLIGHT_ENABLE
            rgblight_sethsv_noeeprom_orange(); rgblight_mode_noeeprom(1);
#endif
            break;
        case SINGLE_HOLD:
            register_code (KC_LSFT);
#ifdef RGBLIGHT_ENABLE
            rgblight_sethsv_noeeprom_orange(); rgblight_mode_noeeprom(1);
#endif
            break;
        case DOUBLE_HOLD:
            layer_on(NM_MODE);
            register_code (KC_LSFT);
            break;
        case TRIPLE_HOLD:
            register_code (KC_LSFT);
            register_code (KC_LCTL);
            layer_on(NM_MODE);
#ifdef RGBLIGHT_ENABLE
            rgblight_sethsv_noeeprom_yellow(); rgblight_mode_noeeprom(1);
#endif
            break;
    }
}

void dance_SFT_NM_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP:
            unregister_code (KC_LSFT);
#ifdef RGBLIGHT_ENABLE
            rgblight_sethsv_noeeprom(OTHI_DEFAULT_R, OTHI_DEFAULT_G, OTHI_DEFAULT_B); rgblight_mode_noeeprom(OTHI_DEFAULT_MODE);
#endif
            break;
        case SINGLE_HOLD:
            unregister_code (KC_LSFT);
#ifdef RGBLIGHT_ENABLE
            rgblight_sethsv_noeeprom(OTHI_DEFAULT_R, OTHI_DEFAULT_G, OTHI_DEFAULT_B); rgblight_mode_noeeprom(OTHI_DEFAULT_MODE);
#endif
            break;
        case DOUBLE_HOLD:
            layer_off(NM_MODE);
            unregister_code (KC_LSFT);
            break;
        case TRIPLE_HOLD:
            unregister_code (KC_LSFT);
            unregister_code (KC_LCTL);
            layer_off(NM_MODE);
            break;
    }
    xtap_state.state = 0;
}

//NOT FINISHED. DO NOT USE
void dance_LANG_IN_finished (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code (KC_LGUI);
        tap_code(KC_SPC);
        //rgblight_sethsv_noeeprom_red(); rgblight_mode_noeeprom(1);
    } else {
        register_code (KC_LGUI);
    }
}

void dance_LANG_IN_reset (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code (KC_LGUI);
        //rgblight_sethsv_noeeprom(OTHI_DEFAULT_R, OTHI_DEFAULT_G, OTHI_DEFAULT_B); rgblight_mode_noeeprom(1);
    } else {
        unregister_code (KC_LGUI);
    }
}

void dance_LANG_IN_each(qk_tap_dance_state_t *state, void *user_data) {
    tap_code(KC_SPC);
}

void dance_A_BRC_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_LSFT); register_code(KC_LBRC); break;
        case DOUBLE_TAP: register_code(KC_LSFT); register_code(KC_LBRC); register_code(KC_RBRC); unregister_code(KC_LSFT); register_code(KC_LEFT); break;
    }
}
void dance_A_BRC_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP: unregister_code(KC_LSFT); unregister_code(KC_LBRC); break;
        case DOUBLE_TAP: unregister_code(KC_LBRC); unregister_code(KC_RBRC); unregister_code(KC_LEFT); break;
    }
    xtap_state.state = 0;
}
void dance_S_BRC_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_LBRC); break;
        case DOUBLE_TAP: register_code(KC_LBRC); register_code(KC_RBRC); register_code(KC_LEFT); break;
    }
}
void dance_S_BRC_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP: unregister_code(KC_LBRC); break;
        case DOUBLE_TAP: unregister_code(KC_LBRC); unregister_code(KC_RBRC); unregister_code(KC_LEFT); break;
    }
}
void dance_R_BRC_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_LSFT); register_code(KC_9); break;
        case DOUBLE_TAP: register_code(KC_LSFT); register_code(KC_9); register_code(KC_0); unregister_code(KC_LSFT); register_code(KC_LEFT); break;
    }
}
void dance_R_BRC_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP: unregister_code(KC_LSFT); unregister_code(KC_9); break;
        case DOUBLE_TAP: unregister_code(KC_9); unregister_code(KC_0); unregister_code(KC_LEFT); break;
    }
    xtap_state.state = 0;
}
void dance_QUOT_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    shift_pressed = get_mods() & ((MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT)));
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_QUOT); break;
        case DOUBLE_TAP: register_code(KC_QUOT); unregister_code(KC_QUOT); register_code(KC_QUOT);
                         if (shift_pressed) { //checks if Shifted
                             unregister_mods(MOD_BIT(KC_LSFT));
                             SEND_STRING("not supposed to be shifted");
                         }
                         register_code(KC_LEFT); break;
    }
}
void dance_QUOT_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP: unregister_code(KC_LSFT); unregister_code(KC_QUOT); break;
        case DOUBLE_TAP: unregister_code(KC_LSFT); unregister_code(KC_QUOT); unregister_code(KC_LEFT); break;
    }
    xtap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [CTL_NM] = ACTION_TAP_DANCE_FN_ADVANCED (dance_CTL_NM_each, dance_CTL_NM_finished, dance_CTL_NM_reset),
    [GUI_NM] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_GUI_NM_finished, dance_GUI_NM_reset),
    [ALT_NM] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_ALT_NM_finished, dance_ALT_NM_reset),
    [SFT_NM] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_SFT_NM_finished, dance_SFT_NM_reset),
    [LANG_IN] = ACTION_TAP_DANCE_FN_ADVANCED (dance_LANG_IN_each, dance_LANG_IN_finished, dance_LANG_IN_reset),
    [A_BRC]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL,dance_A_BRC_finished, dance_A_BRC_reset),
    [S_BRC]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL,dance_S_BRC_finished, dance_S_BRC_reset),
    [R_BRC]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL,dance_R_BRC_finished, dance_R_BRC_reset),
    [QUOT]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_QUOT_finished, dance_QUOT_reset)
};

