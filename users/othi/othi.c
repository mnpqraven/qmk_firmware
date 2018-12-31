/*
Copyright 2017 Truong Hoang Tung <mnpq.raven@gmail.com> @mnpqraven

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "othi.h"

void eeconfig_init_users(void) {
#if (defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE))
  #define OTHI_UNICODE_MODE UC_LNX
#else
  #define OTHI_UNICODE_MODE 1
#endif

void eeconfig_init_user(void) {
  #if (defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE))
    set_unicode_input_mode(OTHI_UNICODE_MODE);
    get_unicode_input_mode();
  #else
    eeprom_update_byte(EECONFIG_UNICODEMODE, OTHI_UNICODE_MODE);
  #endif // (defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE))

    user_config.rgb_layer_change = true; // We want this enabled by default
    eeconfig_update_user(user_config.raw); // Write default value to EEPROM now
    // use the non noeeprom versions, to write these values to EEPROM too
#ifdef RGBLIGHT_ENABLE
    rgblight_enable(); // Enable RGB by default
        rgblight_sethsv(OTHI_DEFAULT_R, OTHI_DEFAULT_G, OTHI_DEFAULT_B);
        rgblight_mode(OTHI_DEFAULT_MODE);
    //rgblight_mode(1); // set to solid by default
#endif
}

//void dance_CTL_NM_finished (qk_tap_dance_state_t *state, void *user_data) {
//  if (state->count == 1) {
//	set_oneshot_mods(MOD_LCTL);
//  } else {
//    register_code (KC_LCTL);
//	layer_on(NM_MODE);
//  }
//}
//
//void dance_CTL_NM_reset (qk_tap_dance_state_t *state, void *user_data) {
//  if (state->count == 1) {
//    unregister_code (KC_LCTL);
//  } else {
//    unregister_code (KC_LCTL);
//	layer_off(NM_MODE);
//  }
//}
//
//void dance_GUI_NM_finished (qk_tap_dance_state_t *state, void *user_data) {
//  if (state->count == 1) {
//	register_code (KC_LGUI);
//  } else {
//    register_code (KC_LGUI);
//	layer_on(NM_MODE);
//  }
//}
//
//void dance_GUI_NM_reset (qk_tap_dance_state_t *state, void *user_data) {
//  if (state->count == 1) {
//    unregister_code (KC_LGUI);
//  } else {
//    unregister_code (KC_LGUI);
//	layer_off(NM_MODE);
//  }
//}
//
//void dance_ALT_NM_finished (qk_tap_dance_state_t *state, void *user_data) {
//  if (state->count == 1) {
//	register_code (KC_LALT);
//  } else {
//    register_code (KC_LALT);
//	layer_on(NM_MODE);
//  }
//}
//
//void dance_ALT_NM_reset (qk_tap_dance_state_t *state, void *user_data) {
//  if (state->count == 1) {
//    unregister_code (KC_LALT);
//  } else {
//    unregister_code (KC_LALT);
//	layer_off(NM_MODE);
//  }
//}
//
//void dance_SFT_NM_finished (qk_tap_dance_state_t *state, void *user_data) {
//  if (state->count == 1) {
//	register_code (KC_LSFT);
//	set_oneshot_mods(MOD_LSFT);
//  } else {
//    register_code (KC_LSFT);
//	layer_on(NM_MODE);
//  }
//}
//
//void dance_SFT_NM_reset (qk_tap_dance_state_t *state, void *user_data) {
//  if (state->count == 1) {
//    unregister_code (KC_LSFT);
//  } else {
//    unregister_code (KC_LSFT);
//	layer_off(NM_MODE);
//  }
//}
//
//qk_tap_dance_action_t tap_dance_actions[] = {
// [CTL_NM] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_CTL_NM_finished, dance_CTL_NM_reset),
// [GUI_NM] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_GUI_NM_finished, dance_GUI_NM_reset),
// [ALT_NM] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_ALT_NM_finished, dance_ALT_NM_reset),
// [SFT_NM] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_SFT_NM_finished, dance_SFT_NM_reset)
//};
//
