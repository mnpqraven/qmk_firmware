#pragma once
#include "othi.h"
#ifdef RGBLIGHT_ENABLE
  #include "rgblight.h"
#endif
uint32_t layer_state_set_user(uint32_t state);
void matrix_scan_user(void);
