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
#pragma once
#include "quantum.h"
#include "eeprom.h"
#include "process_records.h"

//i don't think i need this ?
//TODO: test rgb without this snippet
//#ifdef RGBLIGHT_ENABLE
//#include "rgblight.h"
//#endif

//uncomment the line for board being flashed
//#define KBD6X //specific boards are KBD6X

typedef union {
  uint32_t raw;
  struct {
    bool     rgb_layer_change :1;
  };
} user_config_t;
user_config_t user_config;

//Custom Keycodes
enum my_keycodes {
  FOO = SAFE_RANGE,
  EPRM,
  RGB_LYR,
  CL_LGUI,
  F_ESC,
};

//Layers Definition
#define CL 0
#define NM_MODE 2
#define VI_MODE 3
#define FNUM 4
#define ACCENT 5
#define ACCENT_CAP 6
#define BRCKS 7

//Unicode Definitions
#define DE_AE     UC(0x00E4)
#define DE_SS     UC(0x00DF)
#define DE_OE     UC(0x00F6)
#define DE_UE     UC(0x00FC)
#define DE_AE_CAP UC(0x00C4)
#define DE_OE_CAP UC(0x00D6)
#define DE_UE_CAP UC(0x00DC)

//Tap Dance Keycodes
enum tap_dancers {
  CTL_NM,
  GUI_NM,
  ALT_NM,
  SFT_NM,
  LANG_IN,
  R_BRC,
  S_BRC,
  A_BRC,
  QUOT,
  GRV,
};

//Default RGB Color
#ifdef RGBLIGHT_ENABLE
//azure 186, 102, 255
//blue 240, 255, 255
//red 0, 255, 255
  #define LIGHT_DEBOUNCE 75

  #define OTHI_DEFAULT_R 240
  #define OTHI_DEFAULT_G 255
  #define OTHI_DEFAULT_B 255
  #define OTHI_DEFAULT_MODE RGBLIGHT_MODE_STATIC_LIGHT
#endif
