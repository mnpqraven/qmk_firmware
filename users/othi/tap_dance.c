#include "othi.h"
#ifdef RGBLIGHT_ENABLE
#include "rgb_light.h"
#endif

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

// Tapping order init
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

// CTL_NM
void dance_CTL_NM_finished (qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_LCTL); break;
        case SINGLE_HOLD: register_code(KC_LCTL);
#ifdef RGBLIGHT_ENABLE
                          rgblight_mode_noeeprom(1);
                          rgblight_sethsv_noeeprom_user(186,102,255);
#endif
                          break;
        case DOUBLE_HOLD: register_code (KC_LCTL);
                          layer_on(NM_MODE); break;
    }
}
void dance_CTL_NM_each (qk_tap_dance_state_t *state, void *user_data) {
    //version 1: 1st backspace starts at double tap
    //if (state->count >= 2) {
    //    tap_code(KC_BSPC);
    //}
    //version2: double tap produces 2 backspaces, so muscle memory remains but you might have to retype a character
    if (state->count == 2) {
    tap_code(KC_BSPC);
    tap_code(KC_BSPC);
    } else if (state->count > 2) {
    tap_code(KC_BSPC);
    }
}
void dance_CTL_NM_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP: unregister_code(KC_LCTL); break;
        case SINGLE_HOLD: unregister_code(KC_LCTL);
#ifdef RGBLIGHT_ENABLE
            rgblight_sethsv_noeeprom(OTHI_DEFAULT_R, OTHI_DEFAULT_G, OTHI_DEFAULT_B); rgblight_mode_noeeprom(OTHI_DEFAULT_MODE);
#endif
                          break;
        default: unregister_code(KC_LCTL);
                 layer_off(NM_MODE); break;
    }
    xtap_state.state = 0;
}

// GUI_NM
void dance_GUI_NM_finished (qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP:
            tap_code(KC_TAB); break;
        case SINGLE_HOLD:
            register_code(KC_LGUI);
#ifdef RGBLIGHT_ENABLE
            rgblight_mode_noeeprom(1);
            rgblight_sethsv_noeeprom_user(300,255,255);
#endif
            break;
        case DOUBLE_TAP: //before SINGLE_HOLD to avoid light flicker
            register_code (KC_LGUI);
            tap_code(KC_TAB); break;
        case DOUBLE_HOLD:
            register_code (KC_LGUI);
#ifdef RGBLIGHT_ENABLE
            rgblight_mode_noeeprom(1);
            rgblight_sethsv_noeeprom_user(300,255,255);
#endif
            break;
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
        default:
            unregister_code (KC_LGUI);
            layer_off(NM_MODE); break;
    }
    xtap_state.state = 0;
}
void dance_GUI_NM_each (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 3) {
        tap_code(KC_TAB);
        tap_code(KC_TAB);
    }
    if (state->count > 3) {
        tap_code(KC_TAB);
    }
}

// ALT_NM
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
            rgblight_mode_noeeprom(1);
            rgblight_sethsv_noeeprom_user(39,255,255); //orange
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
        default:
            unregister_code (KC_LALT);
            unregister_code (KC_LCTL);
            layer_off(NM_MODE);
    }
    xtap_state.state = 0;
}

// SFT_NM
void dance_SFT_NM_finished (qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP:
            register_code (KC_LSFT);
//#ifdef RGBLIGHT_ENABLE
//            rgblight_sethsv_noeeprom_orange(); rgblight_mode_noeeprom(1);
//#endif
            break;
        case SINGLE_HOLD:
            register_code (KC_LSFT);
#ifdef RGBLIGHT_ENABLE
            rgblight_mode_noeeprom(1);
            rgblight_sethsv_noeeprom_user(39,255,255); //orange
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
            rgblight_mode_noeeprom(1);
            rgblight_sethsv_noeeprom_user(60,255,255); //yellow
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
        default:
            unregister_code(KC_LSFT);
            layer_off(NM_MODE);
    }
    xtap_state.state = 0;
}

// A_BRC abbv. arrow backets {}
void dance_A_BRC_finished(qk_tap_dance_state_t *state, void *user_data) {
    shift_pressed = get_mods() & ((MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT)));
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_LSFT); register_code(KC_LBRC); break;
        case DOUBLE_TAP: tap_code(KC_LBRC); tap_code(KC_RBRC);
                         if (shift_pressed) {
                             clear_keyboard();
                         }
                         tap_code(KC_LEFT);
                         break;
    }
}
void dance_A_BRC_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP: unregister_code(KC_LSFT); unregister_code(KC_LBRC); break;
        case DOUBLE_TAP: unregister_code(KC_LBRC); unregister_code(KC_RBRC); unregister_code(KC_LEFT); break;
    }
    xtap_state.state = 0;
    //switches back to layer 0
    //layer_off(BRCKS);
}

// S_BRC abbv. square brackets []
void dance_S_BRC_finished(qk_tap_dance_state_t *state, void *user_data) {
    shift_pressed = get_mods() & ((MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT)));
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_LBRC); break;
        case DOUBLE_TAP: tap_code(KC_LBRC); tap_code(KC_RBRC);
                         if (shift_pressed) {
                             clear_keyboard();
                         }
                         tap_code(KC_LEFT);
                         break;
    }
}
void dance_S_BRC_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP: unregister_code(KC_LBRC); break;
        case DOUBLE_TAP: unregister_code(KC_LBRC); unregister_code(KC_RBRC); unregister_code(KC_LEFT); break;
    }
    xtap_state.state = 0;
    //switches back to layer 0
    //layer_off(BRCKS);
}

// R_BRC abbv. round brackets ()
void dance_R_BRC_finished(qk_tap_dance_state_t *state, void *user_data) {
    shift_pressed = get_mods() & ((MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT)));
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_LSFT); register_code(KC_9); break;
        case DOUBLE_TAP: register_code(KC_LSFT); register_code(KC_9); register_code(KC_0);
                         if (shift_pressed) {
                             clear_keyboard();
                         }
                         unregister_code(KC_LSFT);
                         tap_code(KC_LEFT);
                         break;
    }
}
void dance_R_BRC_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP: unregister_code(KC_LSFT); unregister_code(KC_9); break;
        case DOUBLE_TAP: unregister_code(KC_9); unregister_code(KC_0); unregister_code(KC_LEFT); break;
    }
    xtap_state.state = 0;
    //switches back to layer 0
    //layer_off(BRCKS);
}

// QUOT abbv. quotation marks '' ""
void dance_QUOT_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    shift_pressed = get_mods() & ((MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT)));
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_QUOT); break;
        case DOUBLE_TAP: tap_code(KC_QUOT); tap_code(KC_QUOT);
                         if (shift_pressed) { //checks if Shift is held
                             //unregister_mods(MOD_BIT(KC_LSFT)); //this doesn't work, further testing required
                             //this is to remove the currently held mod key so pressing left won't select the right quote
                             clear_keyboard();
                         }
                         tap_code(KC_LEFT);
                         break;
    }
}
void dance_QUOT_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP: unregister_code(KC_LSFT); unregister_code(KC_QUOT); break;
    }
    xtap_state.state = 0;
    if (shift_pressed) {
        //goes back to shifted as we are still holding down SFT_NM
        register_code(KC_LSFT);
    }
    //switches back to layer 0
    //layer_off(BRCKS);
}

//GRV abbv. grave marks `` ~~
void dance_GRV_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    shift_pressed = get_mods() & ((MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT)));
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_GRV); break;
        case DOUBLE_TAP: tap_code(KC_GRV); tap_code(KC_GRV);
                         if (shift_pressed) { //checks if Shift is held
                             //unregister_mods(MOD_BIT(KC_LSFT)); //this doesn't work, further testing required
                             //this is to remove the currently held mod key so pressing left won't select the right quote
                             clear_keyboard();
                         }
                         tap_code(KC_LEFT);
                         break;
    }
}
void dance_GRV_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP: unregister_code(KC_LSFT); unregister_code(KC_GRV); break;
    }
    xtap_state.state = 0;
    if (shift_pressed) {
        //goes back to shifted as we are still holding down SFT_NM
        register_code(KC_LSFT);
    }
    //switches back to layer 0
    //layer_off(BRCKS);
}

//GUI: i3 workshop swap, GUI + Shift on DOUBLE_HOLD, else GUI
void dance_GUI_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    shift_pressed = get_mods() & ((MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT)));
    switch (xtap_state.state) {
        case SINGLE_TAP:
            register_code(KC_TAB);
            break;
        case DOUBLE_TAP: register_code(KC_LGUI);
                         tap_code(KC_TAB);
                         unregister_code(KC_LGUI);
                         break;
        case DOUBLE_HOLD:
                         register_code(KC_LGUI);
                         //register_code(KC_LSFT);
#ifdef RGBLIGHT_ENABLE
                 rgblight_mode_noeeprom(1);
                 rgblight_sethsv_noeeprom_user(39,255,255); //orange
#endif
                         break;
        default: register_code(KC_LGUI);
#ifdef RGBLIGHT_ENABLE
                 rgblight_mode_noeeprom(1);
                 rgblight_sethsv_noeeprom_user(300,255,255); //magenta
#endif
                 break;

    }
}
void dance_GUI_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_TAB);
        case DOUBLE_HOLD:
            unregister_code(KC_LGUI);
            //unregister_code(KC_LSFT);
#ifdef RGBLIGHT_ENABLE
            rgblight_sethsv_noeeprom(OTHI_DEFAULT_R, OTHI_DEFAULT_G, OTHI_DEFAULT_B); rgblight_mode_noeeprom(OTHI_DEFAULT_MODE);
#endif
            break;
        default:
            unregister_code(KC_LGUI);
#ifdef RGBLIGHT_ENABLE
            rgblight_sethsv_noeeprom(OTHI_DEFAULT_R, OTHI_DEFAULT_G, OTHI_DEFAULT_B); rgblight_mode_noeeprom(OTHI_DEFAULT_MODE);
#endif
            break;
    }
    xtap_state.state = 0;
}

// _T abbv.
void dance_T_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_T); break;
        case DOUBLE_TAP: tap_code(KC_T); register_code(KC_T); break;
        case DOUBLE_SINGLE_TAP: tap_code(KC_T); register_code(KC_T); break;
        case DOUBLE_HOLD: layer_on(BRCKS); break;
    }
}
void dance_T_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        default: unregister_code(KC_T); break;
    }
    xtap_state.state = 0;
    layer_off(BRCKS);
}
void dance_T_each(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 3) {
        tap_code(KC_T);
        tap_code(KC_T);
    }
    if (state->count > 2) {
        tap_code(KC_T);
    }
}
// _N abbv.
void dance_N_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_N); break;
        case DOUBLE_TAP: tap_code(KC_N); register_code(KC_N); break;
        case DOUBLE_SINGLE_TAP: tap_code(KC_N); register_code(KC_N); break;
        case DOUBLE_HOLD: layer_on(BRCKS); break;
    }
}
void dance_N_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        default: unregister_code(KC_N); break;
    }
    xtap_state.state = 0;
    layer_off(BRCKS);
}
void dance_N_each(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 3) {
        tap_code(KC_N);
        tap_code(KC_N);
    }
    if (state->count > 2) {
        tap_code(KC_N);
    }
}
qk_tap_dance_action_t tap_dance_actions[] = {
    [CTL_NM] = ACTION_TAP_DANCE_FN_ADVANCED (dance_CTL_NM_each, dance_CTL_NM_finished, dance_CTL_NM_reset),
    [GUI_NM] = ACTION_TAP_DANCE_FN_ADVANCED (dance_GUI_NM_each, dance_GUI_NM_finished, dance_GUI_NM_reset),
    [ALT_NM] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_ALT_NM_finished, dance_ALT_NM_reset),
    [SFT_NM] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_SFT_NM_finished, dance_SFT_NM_reset),
    [A_BRC]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL,dance_A_BRC_finished, dance_A_BRC_reset),
    [S_BRC]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL,dance_S_BRC_finished, dance_S_BRC_reset),
    [R_BRC]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL,dance_R_BRC_finished, dance_R_BRC_reset),
    [QUOT]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_QUOT_finished, dance_QUOT_reset),
    [GRV]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_GRV_finished, dance_GRV_reset),
    [GUI]  = ACTION_TAP_DANCE_FN_ADVANCED(dance_GUI_NM_each, dance_GUI_finished, dance_GUI_reset),
    [_T]  = ACTION_TAP_DANCE_FN_ADVANCED(dance_T_each,dance_T_finished, dance_T_reset),
    [_N]  = ACTION_TAP_DANCE_FN_ADVANCED(dance_N_each,dance_N_finished, dance_N_reset)
};

