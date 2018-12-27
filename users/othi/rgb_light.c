#include "rgb_light.h"
void matrix_init_user(void) {
    // Call the keymap level matrix init.
    // Read the user config from EEPROM
    user_config.raw = eeconfig_read_user();
    // Set default layer, if enabled
    if (user_config.rgb_layer_change) {
        rgblight_enable_noeeprom();
        rgblight_sethsv_noeeprom_cyan();
        rgblight_mode_noeeprom(1);
    }
}
uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
        case NM_MODE:
            if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_green(); rgblight_mode_noeeprom(1); }
            break;
        case VI_MODE:
            if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_yellow(); rgblight_mode_noeeprom(1); }
            break;
        case ACCENT:
            if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_white(); rgblight_mode_noeeprom(1); }
            break;
        case ACCENT_CAP:
            if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_magenta(); rgblight_mode_noeeprom(1); }
            break;
        default: //  for any other layers, or the default layer
            if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_cyan(); rgblight_mode_noeeprom(1); }
            break;
    }
    return state;
}

void matrix_scan_user(void) {

}

uint16_t key_timer;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MT(MOD_LGUI,KC_TAB):
            if (record->event.pressed) {
                key_timer = timer_read();
                register_code(KC_LGUI);
                rgblight_sethsv_noeeprom_magenta(); rgblight_mode_noeeprom(1);
            } else {
                unregister_code(KC_LGUI);
                rgblight_sethsv_noeeprom_cyan(); rgblight_mode_noeeprom(1);
                if (timer_elapsed(key_timer) < TAPPING_TERM) {
                   tap_code(KC_TAB);
                }
            }
            return false; break;
        case MT(MOD_LCTL,KC_BSPC):
            if (record->event.pressed) {
                key_timer = timer_read();
                register_code(KC_LCTL);
                rgblight_sethsv_noeeprom_white(); rgblight_mode_noeeprom(1);
            } else {
                unregister_code(KC_LCTL);
                rgblight_sethsv_noeeprom_cyan(); rgblight_mode_noeeprom(1);
                if (timer_elapsed(key_timer) < TAPPING_TERM) {
                    tap_code(KC_BSPC);
                }
            }
            return false; break;
        case CL_LGUI:
            if (record->event.pressed) {
                key_timer = timer_read();
                register_code(KC_LGUI);
                rgblight_sethsv_noeeprom_magenta(); rgblight_mode_noeeprom(1);
            } else {
                unregister_code(KC_LGUI);
                rgblight_sethsv_noeeprom_cyan(); rgblight_mode_noeeprom(1);
            }
            return true; break;
        case EPRM:
            if (record->event.pressed) {
                eeconfig_init(); // resets the EEPROM to default
            }
            return false;
        case RGB_LYR:  // This allows me to use underglow as layer indication, or as normal
            if (record->event.pressed) {
                user_config.rgb_layer_change ^= 1; // Toggles the status
                eeconfig_update_user(user_config.raw); // Writes the new status to EEPROM
                if (user_config.rgb_layer_change) { // if layer state indication is enabled,
                    layer_state_set(layer_state);   // then immediately update the layer color
                }
            }
            return false; break;
        case RGB_MODE_FORWARD ... RGB_MODE_GRADIENT: // For any of the RGB codes (see quantum_keycodes.h, L400 for reference)
            if (record->event.pressed) { //This disables layer indication, as it's assumed that if you're changing this ... you want that disabled
                if (user_config.rgb_layer_change) {        // only if this is enabled
                    user_config.rgb_layer_change = false;  // disable it, and
                    eeconfig_update_user(user_config.raw); // write the setings to EEPROM
                }
            }
            return true; break;
        default:
            return true; // Process all other keycodes normally
    }
}

//uint32_t layer_state_set_user(uint32_t state) {
//    switch (biton32(state)) {
//    case NM_MODE:
//        rgblight_setrgb (0x00,  0x66, 0x00);
//        break;
//    case VI_MODE:
//        rgblight_setrgb (0x66,  0x66, 0x00);
//        break;
//    case ACCENT:
//        rgblight_setrgb (0x7A,  0x00, 0xFF);
//        break;
//    case ACCENT_CAP:
//        rgblight_setrgb (0x7A,  0xFF, 0xFF);
//        break;
//    default: //  for any other layers, or the default layer
//        rgblight_setrgb (0x00,  0x00, 0xFF);
//        break;
//    }
//  return state;
//}
