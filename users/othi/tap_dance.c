#include "othi.h"

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
    case SINGLE_HOLD: register_code(KC_LCTRL); break;
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
    case SINGLE_HOLD: unregister_code(KC_LCTRL); break;
    case DOUBLE_TAP: unregister_code(KC_ESC); break;
    case DOUBLE_HOLD: unregister_code(KC_LALT);
    case DOUBLE_SINGLE_TAP: unregister_code(KC_X);
  }
  xtap_state.state = 0;
}
// Send `. ~. ```
void tap_dance_grave_finished(qk_tap_dance_state_t *state, void *user_data) {
  switch(state->count) {
    case 1:
      SEND_STRING("`");
      break;
    case 2:
      SEND_STRING("~");
      break;
  }
}

void tap_dance_grave_each(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 3) {
    SEND_STRING("```");
  } else if (state->count > 3) {
    SEND_STRING("`");
  }
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
    //if (state->count == 2) {
    if (state->count >= 2) {
    tap_code(KC_BSPC);
    //tap_code(KC_BSPC);
    //} else if (state->count > 2) {
    //tap_code(KC_BSPC);
    }
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
            rgblight_sethsv_noeeprom_magenta(); rgblight_mode_noeeprom(1);
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
            rgblight_sethsv_noeeprom(OTHI_DEFAULT_R, OTHI_DEFAULT_G, OTHI_DEFAULT_B); rgblight_mode_noeeprom(1);
            break;
        case DOUBLE_HOLD:
            unregister_code (KC_LGUI);
            layer_off(NM_MODE); break;
    }
    xtap_state.state = 0;
}

void dance_ALT_NM_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
	register_code (KC_LALT);
  } else {
    register_code (KC_LALT);
	layer_on(NM_MODE);
  }
}

void dance_ALT_NM_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_LALT);
  } else {
    unregister_code (KC_LALT);
	layer_off(NM_MODE);
  }
}

void dance_SFT_NM_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_LSFT);
	_delay_ms(LIGHT_DEBOUNCE);
    //rgblight_sethsv_noeeprom_orange(); rgblight_mode_noeeprom(1);
  } else {
    register_code (KC_LSFT);
	layer_on(NM_MODE);
  }
}

void dance_SFT_NM_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_LSFT);
    rgblight_sethsv_noeeprom(OTHI_DEFAULT_R, OTHI_DEFAULT_G, OTHI_DEFAULT_B); rgblight_mode_noeeprom(1);
  } else {
    unregister_code (KC_LSFT);
	layer_off(NM_MODE);
  }
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



qk_tap_dance_action_t tap_dance_actions[] = {
 [CTL_NM] = ACTION_TAP_DANCE_FN_ADVANCED (dance_CTL_NM_each, dance_CTL_NM_finished, dance_CTL_NM_reset),
 [GUI_NM] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_GUI_NM_finished, dance_GUI_NM_reset),
 [ALT_NM] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_ALT_NM_finished, dance_ALT_NM_reset),
 [SFT_NM] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_SFT_NM_finished, dance_SFT_NM_reset),
 [LANG_IN] = ACTION_TAP_DANCE_FN_ADVANCED (dance_LANG_IN_each, dance_LANG_IN_finished, dance_LANG_IN_reset),
 [TD_GRAVE] = ACTION_TAP_DANCE_FN_ADVANCED(tap_dance_grave_each, tap_dance_grave_finished, NULL),
 [X_CTL]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL,x_finished, x_reset)
};

