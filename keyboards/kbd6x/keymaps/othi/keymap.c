#include QMK_KEYBOARD_H
#include "othi.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [CL] = LAYOUT(
      F_ESC,                  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,        KC_EQL,     KC_BSLS,    KC_DEL,
      TD(GUI),    LT(NM_MODE,KC_Q),    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,     KC_LBRC, KC_RBRC, KC_BSPC,
      TD(CTL_NM),   KC_A,    KC_R,    KC_S,    TD(_T),    KC_D,    KC_H,    TD(_N),    KC_E,    KC_I,    KC_O,           KC_QUOT, KC_ENT,
      TD(SFT_NM),             KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    MT(MOD_LCTL,KC_COMM), MT(MOD_LSFT,KC_DOT),  MT(MOD_LALT,KC_SLSH),        LM(CL,MOD_LGUI|MOD_LSFT), TT(NM_MODE),
      _______, TG(BRCKS),                     TD(ALT_NM),            	KC_SPC,    LM(CL,MOD_LGUI|MOD_LALT), OSL(ACCENT)    , _______
      ),
  [NM_MODE] = LAYOUT(
      KC_GRV,           KC_MPRV,    KC_MNXT,    KC_MPLY,    KC_END,      _______,     _______,     _______,     _______,     _______,     KC_HOME,    _______,  _______,  RESET, KC_INS,
      KC_TAB,     _______,    LCTL(KC_RGHT),  _______,    _______,    _______,    _______,    KC_UP,    KC_PGUP,    _______,    _______,     _______, TG(CL), KC_DEL,
      _______,          KC_LEFT,    _______,    KC_RGHT,      _______,    KC_PGDN,    KC_LEFT,   KC_DOWN,   KC_RGHT,     _______,    KC_ENT,  KC_QUOT, KC_LGUI,
      KC_LSFT,          _______,    _______,    _______,      _______,    LCTL(KC_LEFT),    _______,    _______,    _______,    _______,    _______,    TG(VI_MODE), TO(CL),
      _______, TD(CTL_NM),                     TD(ALT_NM),                    KC_SPC,    LM(CL,MOD_LGUI|MOD_LALT), OSL(ACCENT), _______
      ),
  [VI_MODE] = LAYOUT(
      KC_GRV,           KC_MPRV,  KC_MNXT, KC_MPLY,    LSFT(KC_END),     _______,     _______,     _______,     _______,     _______,     LSFT(KC_HOME),    KC_F11,  KC_F12,  RESET, KC_INS,
      LGUI(KC_TAB),     _______,    LSFT(LCTL(KC_RGHT)),  _______,    _______,    _______,    _______,    LSFT(KC_UP),    _______,    _______,    _______,     _______, TG(CL), KC_BSPC,
      _______,          _______,    _______,    _______,      _______,    _______,    LSFT(LCTL(KC_LEFT)),   LSFT(KC_DOWN),   LSFT(KC_RGHT),     _______,    KC_SCLN,  KC_QUOT, KC_LGUI,
      KC_LSFT,          _______,  _______, _______,      _______,    LSFT(LCTL(KC_LEFT)),    _______,    _______,    _______,    _______,    KC_SLSH,    OSM(MOD_LSFT), TO(CL),
      _______, TD(CTL_NM),                     TD(ALT_NM),                 KC_SPC,    LM(CL,MOD_LGUI|MOD_LALT), OSL(ACCENT), _______
      ),
  [ACCENT] = LAYOUT(
<<<<<<< HEAD
<<<<<<< HEAD
      _______,       KC_F1,  KC_F2, KC_F3,    KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,  KC_F12,  _______, _______,
<<<<<<< HEAD
      _______,         RGB_TOG,    RGB_MODE_PLAIN,  _______,    _______,    _______,    _______,    _______,    DE_UE,    _______,    _______,     _______, _______, _______,
      _______,            DE_AE,    UC_Z,    DE_SS,      _______,    _______,    _______,   _______,   _______,     _______,    DE_OE,  _______, _______,
=======
      _______,         RGB_TOG,    RGB_LYR,  RGB_RMOD,    RGB_MOD,    _______,    _______,    _______,    DE_UE,    _______,    _______,     _______, _______, _______,
      _______,            DE_AE,    _______,    DE_SS,      _______,    _______,    _______,   _______,   _______,     _______,    DE_OE,  _______, _______,
>>>>>>> fixed some lines, better rgb calls, now default layer color can be
      OSL(ACCENT_CAP),     _______,  _______, _______,      _______,    _______,    _______,    _______,    _______,    _______,        _______, _______, TO(CL),
=======
      _______,       KC_F1,  KC_F2, KC_F3,    KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,  KC_F12,  _______, KC_CAPS,
=======
      _______,       KC_F1,  KC_F2, KC_F3,    KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,  KC_F12,  KC_CAPS, _______,
>>>>>>> new tap dance on T and N for easier bracket layer
      _______,         RGB_TOG,    RGB_LYR,  RGB_RMOD,    RGB_MOD,    _______,    _______,    _______,    DE_UE,    _______,    _______,     _______, _______, _______,
      _______,            DE_AE,    _______,    DE_SS,      _______,    _______,    _______,   _______,   _______,     _______,    DE_OE,  _______, _______,
      KC_LSFT,     _______,  _______, _______,      _______,    _______,    _______,    _______,    _______,    _______,        _______, _______, TO(CL),
>>>>>>> update unicode and clean up process_records
      _______,             _______,         _______,            _______,         _______, _______,  _______
      ),
  [BRCKS] = LAYOUT(
      _______,   _______,  _______, _______,    _______,          _______,     _______,     _______,     _______,     _______,     _______,    _______,  _______,  _______, _______,
      _______,      _______,    _______,  _______,    _______,    _______,    _______,    TD(QUOT),    TD(GRV),    _______,    _______,     _______, _______, _______,
      _______,        _______,    _______,    _______,      _______,    _______,    _______,   TD(R_BRC),   TD(A_BRC),     TD(S_BRC),    KC_ENT,  _______,   _______,
      _______,      _______, _______,      _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______, _______, TO(CL),
      _______,   _______,         _______,         KC_LSFT,         _______,   _______,      _______
      ),
};
