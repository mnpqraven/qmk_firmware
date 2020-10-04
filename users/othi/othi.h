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
extern user_config_t user_config;

//Custom Keycodes
enum my_keycodes {
  FOO = SAFE_RANGE,
  EPRM,
  RGB_LYR,
  CL_LGUI,
  F_ESC,
  DE_AE,
  DE_SS,
  DE_OE,
  DE_UE,
  TEST,
};

//Layers Definition
#define CL 0
#define GAME 1
#define NM_MODE 2
#define VI_MODE 3
#define FNUM 4
#define ACCENT 5
#define BRCKS 6
#define QTY 7

//Unicode list
//DE_AE     UC(0x00E4)
//DE_SS     UC(0x00DF)
//DE_OE     UC(0x00F6)
//DE_UE     UC(0x00FC)
//DE_AE_CAP UC(0x00C4)
//DE_OE_CAP UC(0x00D6)
//DE_UE_CAP UC(0x00DC)

//Tap Dance Keycodes
enum tap_dancers {
  CTL_NM,
  GUI_NM,
  ALT_NM,
  SFT_NM,
  R_BRC,
  S_BRC,
  A_BRC,
  QUOT,
  GRV,
  GUI,
  _T,
  _N,
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
#else
  #define LIGHT_DEBOUNCE 1
#endif
