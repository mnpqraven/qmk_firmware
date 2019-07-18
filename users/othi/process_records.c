#include "othi.h"

uint16_t key_timer;
static uint8_t mods_pressed;
static uint8_t shifted;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
//        case TEST:
//            if (record->event.pressed) {
//                send_string(uni);
//            }
//            return false; break;
        case DE_AE:
            shifted = get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT));
            if (record->event.pressed) {
                if (shifted) {
                    send_unicode_hex_string("00C4");
                } else {
                    send_unicode_hex_string("00E4");
                }
            }
            return false; break;
        case DE_OE:
            shifted = get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT));
            if (record->event.pressed) {
                if (shifted) {
                    send_unicode_hex_string("00D6");
                } else {
                    send_unicode_hex_string("00F6");
                }
            }
            return false; break;
        case DE_UE:
            shifted = get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT));
            if (record->event.pressed) {
                if (shifted) {
                    send_unicode_hex_string("00DC");
                } else {
                    send_unicode_hex_string("00FC");
                }
            }
            return false; break;
        case DE_SS:
            shifted = get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT));
            if (record->event.pressed) {
                    send_unicode_hex_string("00DF");
            }
            return false; break;
        case F_ESC:
            // Check to see what mods are pressed
            mods_pressed = get_mods() & ((MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT)
                                         |MOD_BIT(KC_LGUI)|MOD_BIT(KC_RGUI)));
            if (record->event.pressed) {
                key_timer = timer_read();
                layer_on(ACCENT);
            } else {
                layer_off(ACCENT);
                if (timer_elapsed(key_timer) < TAPPING_TERM) {
                    if (mods_pressed) {
                        tap_code(KC_GRV);
                    } else {
                    tap_code(KC_ESC);
                    }
                }
            }
            return false; break;
        case CL_LGUI:
            if (record->event.pressed) {
                key_timer = timer_read();
                register_code(KC_LGUI);
                _delay_ms(LIGHT_DEBOUNCE);
#ifdef RGBLIGHT_ENABLE
                rgblight_sethsv_noeeprom_magenta(); rgblight_mode_noeeprom(1);
#endif
            } else {
                unregister_code(KC_LGUI);
#ifdef RGBLIGHT_ENABLE
                rgblight_sethsv_noeeprom(OTHI_DEFAULT_R, OTHI_DEFAULT_B, OTHI_DEFAULT_B); rgblight_mode_noeeprom(1);
#endif
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
        case TEST:
            if (record->event.pressed) {
                SEND_STRING(QMK_KEYBOARD);
            }
            return true; break;
        default:
            return true; // Process all other keycodes normally
    }
}

