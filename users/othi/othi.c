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
