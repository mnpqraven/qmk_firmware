#include "othi.h"
void dance_CTL_NM_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
	set_oneshot_mods(MOD_LCTL);
  } else {
    register_code (KC_LCTL);
	layer_on(NM_MODE);
  }
}

void dance_CTL_NM_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_LCTL);
  } else {
    unregister_code (KC_LCTL);
	layer_off(NM_MODE);
  }
}

void dance_GUI_NM_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
	register_code (KC_LGUI);
	_delay_ms(LIGHT_DEBOUNCE);
    rgblight_sethsv_noeeprom_magenta(); rgblight_mode_noeeprom(1);
  } else {
    register_code (KC_LGUI);
	layer_on(NM_MODE);
  }
}

void dance_GUI_NM_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_LGUI);
    rgblight_sethsv_noeeprom(OTHI_DEFAULT_R, OTHI_DEFAULT_G, OTHI_DEFAULT_B); rgblight_mode_noeeprom(1);
  } else {
    unregister_code (KC_LGUI);
	layer_off(NM_MODE);
  }
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
 [CTL_NM] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_CTL_NM_finished, dance_CTL_NM_reset),
 [GUI_NM] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_GUI_NM_finished, dance_GUI_NM_reset),
 [ALT_NM] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_ALT_NM_finished, dance_ALT_NM_reset),
 [SFT_NM] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_SFT_NM_finished, dance_SFT_NM_reset),
 [LANG_IN] = ACTION_TAP_DANCE_FN_ADVANCED (dance_LANG_IN_each, dance_LANG_IN_finished, dance_LANG_IN_reset)
};

