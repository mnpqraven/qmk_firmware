#pragma once
#include "othi.h"
#ifdef RGBLIGHT_ENABLE
  #include "rgblight.h"
#endif
extern rgblight_config_t rgblight_config;
uint32_t layer_state_set_user(uint32_t state);
void matrix_scan_user(void);
void rgblight_sethsv_eeprom_helper_user(uint16_t hue, uint8_t sat, uint8_t val, bool write_to_eeprom);
void rgblight_sethsv_noeeprom_user(uint16_t hue, uint8_t sat, uint8_t val);
