#include QMK_KEYBOARD_H
#include "leaf60_universal.h"
#include "othi.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [CL] = LAYOUT(
      F_ESC,                  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,        KC_EQL,     KC_BSLS,    KC_DEL,
      TD(GUI),    LT(NM_MODE,KC_Q),    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,     KC_LBRC, KC_RBRC, KC_BSPC,
      TD(CTL_NM),   KC_A,    KC_R,    KC_S,    LT(BRCKS, KC_T),    KC_D,    KC_H,    LT(BRCKS, KC_N),    KC_E,    KC_I,    KC_O,           KC_QUOT, KC_ENT,
      TD(SFT_NM),  _______,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    MT(MOD_LCTL,KC_COMM), MT(MOD_LSFT,KC_DOT),  MT(MOD_LALT,KC_SLSH),        LM(CL,MOD_LGUI|MOD_LSFT), TT(NM_MODE),
      _______, TG(BRCKS),                     TD(ALT_NM),            _______,	KC_SPC, _______,   _______, LM(CL,MOD_LGUI|MOD_LALT), OSL(ACCENT)    , _______
      ),
  [NM_MODE] = LAYOUT(
      KC_GRV,           KC_MPRV,    KC_MNXT,    KC_MPLY,    KC_END,      _______,     _______,     _______,     _______,     _______,     KC_HOME,    _______,  _______,  RESET, KC_INS,
      KC_TAB,     TG(QTY),    LCTL(KC_RGHT),  _______,    _______,    _______,    _______,    KC_UP,    KC_PGUP,    _______,    _______,     _______, TG(CL), KC_DEL,
      _______,          KC_LEFT,    _______,    KC_RGHT,      _______,    KC_PGDN,    KC_LEFT,   KC_DOWN,   KC_RGHT,     _______,    KC_ENT,  KC_QUOT, KC_LGUI,
      KC_LSFT,  _______,        _______,    _______,    _______,      _______,    LCTL(KC_LEFT),    _______,    _______,    _______,    _______,    _______,    TG(VI_MODE), TO(CL),
      _______, TD(CTL_NM),                     TD(ALT_NM),              _______, KC_SPC,    _______, LM(CL,MOD_LGUI|MOD_LALT), OSL(ACCENT), _______, _______
      ),
  [VI_MODE] = LAYOUT(
      KC_GRV,           KC_MPRV,  KC_MNXT, KC_MPLY,    LSFT(KC_END),     _______,     _______,     _______,     _______,     _______,     LSFT(KC_HOME),    KC_F11,  KC_F12,  RESET, KC_INS,
      LGUI(KC_TAB),     _______,    LSFT(LCTL(KC_RGHT)),  _______,    _______,    _______,    _______,    LSFT(KC_UP),    _______,    _______,    _______,     _______, TG(CL), KC_BSPC,
      _______,          _______,    _______,    _______,      _______,    _______,    LSFT(LCTL(KC_LEFT)),   LSFT(KC_DOWN),   LSFT(KC_RGHT),     _______,    KC_SCLN,  KC_QUOT, KC_LGUI,
      KC_LSFT,  _______,        _______,  _______, _______,      _______,    LSFT(LCTL(KC_LEFT)),    _______,    _______,    _______,    _______,    KC_SLSH,    OSM(MOD_LSFT), TO(CL),
      _______, TD(CTL_NM),                     TD(ALT_NM),        _______,         KC_SPC,  _______,  LM(CL,MOD_LGUI|MOD_LALT), OSL(ACCENT), _______, _______
      ),
  [ACCENT] = LAYOUT(
      _______,       KC_F1,  KC_F2, KC_F3,    KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,  KC_F12,  _______, KC_CAPS,
      _______,         RGB_TOG,    RGB_LYR,  RGB_RMOD,    RGB_MOD,    _______,    _______,    _______,    DE_UE,    _______,    _______,     _______, _______, _______,
      _______,            DE_AE,    _______,    DE_SS,      _______,    _______,    _______,   _______,   _______,     _______,    DE_OE,  _______, _______,
      KC_LSFT,   _______,  UC_M_LN,  UC_M_WI, _______,      EPRM,    _______,    _______,    _______,    _______,    _______,        _______, _______, TO(CL),
      _______,             _______,         _______,       _______,     _______,   _______,      _______, _______,  _______, _______
      ),
  [BRCKS] = LAYOUT(
      _______,   _______,  _______, _______,    _______,          _______,     _______,     _______,     _______,     _______,     _______,    _______,  _______,  _______, _______,
      _______,      _______,    _______,  _______,    _______,    _______,    _______,    TD(QUOT),    TD(GRV),    _______,    _______,     _______, _______, _______,
      _______,        _______,    KC_SLSH,    KC_COMM,      KC_DOT,    _______,    _______,   TD(R_BRC),   TD(A_BRC),     TD(S_BRC),    KC_ENT,  _______,   _______,
      _______,    _______,  _______, _______,      _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______, _______, TO(CL),
      _______,   _______,         _______,      _______,   KC_LSFT,    _______,     _______,   _______,      _______, _______
      ),
  [QTY] = LAYOUT(
      F_ESC,                  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,        KC_EQL,     KC_BSLS,    KC_DEL,
      TD(GUI),    LT(NM_MODE,KC_Q),    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC, KC_RBRC, KC_BSPC,
      TD(CTL_NM),   KC_A,    KC_S,    KC_D,    LT(BRCKS, KC_F),    KC_G,    KC_H,    LT(BRCKS, KC_J),    KC_K,    KC_L,    KC_QUOT,     KC_SCLN, KC_ENT,
      TD(SFT_NM),  _______,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    MT(MOD_LCTL,KC_COMM), MT(MOD_LSFT,KC_DOT),  MT(MOD_LALT,KC_SLSH),        LM(CL,MOD_LGUI|MOD_LSFT), TG(QTY),
      _______, TG(BRCKS),                     TD(ALT_NM),            _______,	KC_SPC, _______,   _______, LM(CL,MOD_LGUI|MOD_LALT), OSL(ACCENT)    , _______
      ),
};


//bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//	return true;
//}

void led_set_user(uint8_t usb_led) {

    if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
        DDRE |= (1 << 6); PORTE &= ~(1 << 6);
    } else {
        DDRE &= ~(1 << 6); PORTE &= ~(1 << 6);
    }

}
