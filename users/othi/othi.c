#include "othi.h"

user_config_t user_config;

void eeconfig_init_users(void) {
#if (defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE))
  #define OTHI_UNICODE_MODE UC_LNX
#else
  #define OTHI_UNICODE_MODE 1
#endif
}

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
