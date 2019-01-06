#include "rgb_light.h"
void matrix_init_user(void) {
    // Call the keymap level matrix init.
    // Read the user config from EEPROM
    user_config.raw = eeconfig_read_user();
    // Set default layer, if enabled
    if (user_config.rgb_layer_change) {
        rgblight_enable_noeeprom();
        rgblight_sethsv_noeeprom(OTHI_DEFAULT_R, OTHI_DEFAULT_G, OTHI_DEFAULT_B);
        rgblight_mode_noeeprom(OTHI_DEFAULT_MODE);
    }
}
uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
        case NM_MODE:
            if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_green(); rgblight_mode_noeeprom(1); } break;
        case VI_MODE:
            if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_yellow(); rgblight_mode_noeeprom(1); } break;
        case ACCENT:
            if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_white(); rgblight_mode_noeeprom(1); } break;
        case ACCENT_CAP:
            if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_magenta(); rgblight_mode_noeeprom(1); } break;
        case FNUM: break; //FNUM does not interrult breathing
        default: //for default and other layers, to change it go to othi.h
            if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom(OTHI_DEFAULT_R, OTHI_DEFAULT_G, OTHI_DEFAULT_B);
                rgblight_mode_noeeprom(OTHI_DEFAULT_MODE); } break;
    }
    return state;
}

void matrix_scan_user(void) {

}
