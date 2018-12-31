/* Copyright 2018 Othi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "othi.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [CL] = LAYOUT(
      F_ESC,                  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,        KC_EQL,     KC_BSLS,    KC_DEL,
      MT(MOD_LGUI,KC_TAB),    LT(NM_MODE,KC_Q),    KC_W,    LT(ACCENT,KC_F),    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,     KC_LBRC, KC_RBRC, KC_BSPC,
      TD(CTL_NM),   KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,           KC_QUOT, KC_ENT,
      TD(SFT_NM),             KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    MT(MOD_LCTL,KC_COMM), MT(MOD_LSFT,KC_DOT),  MT(MOD_LALT,KC_SLSH),        LM(CL,MOD_LGUI|MOD_LSFT), TT(NM_MODE),
      _______, MO(BRCKS),                     TD(ALT_NM),            	KC_SPC,    LM(CL,MOD_LGUI|MOD_LALT), OSL(ACCENT)    , _______
      ),
  [NM_MODE] = LAYOUT(
      KC_GRV,           KC_MPRV,    KC_MNXT,    KC_MPLY,    KC_END,      _______,     _______,     _______,     _______,     _______,     KC_HOME,    _______,  _______,  RESET, KC_INS,
      LGUI(KC_TAB),     _______,    LCTL(KC_RGHT),  _______,    _______,    _______,    _______,    KC_UP,    KC_PGUP,    _______,    _______,     _______, TG(CL), KC_DEL,
      _______,          KC_LEFT,    _______,    KC_RGHT,      _______,    KC_PGDN,    KC_LEFT,   KC_DOWN,   KC_RGHT,     _______,    KC_ENT,  KC_QUOT, KC_LGUI,
      KC_LSFT,          _______,    _______,    _______,      _______,    LCTL(KC_LEFT),    _______,    _______,    _______,    _______,    _______,    TG(VI_MODE), TO(CL),
      _______, TD(CTL_NM),                     TD(ALT_NM),                    KC_SPC,    LM(CL,MOD_LGUI|MOD_LALT), OSL(ACCENT), _______
      ),
  [FNUM] = LAYOUT(
      _______,          KC_F1,  KC_F2, KC_F3,    KC_F4,    KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10,    KC_F11,  KC_F12,  _______, _______,
      _______,          _______,    _______,   _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,   _______,   _______, _______,
      _______,          _______,    _______,   _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,   _______,   _______,
      _______,          _______,    _______,   _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,   _______,   _______,
      _______,             _______,         _______,            _______,         _______, _______,  _______
      ),
  [VI_MODE] = LAYOUT(
      KC_GRV,           KC_MPRV,  KC_MNXT, KC_MPLY,    LSFT(KC_END),     _______,     _______,     _______,     _______,     _______,     LSFT(KC_HOME),    KC_F11,  KC_F12,  RESET, KC_INS,
      LGUI(KC_TAB),     _______,    LSFT(LCTL(KC_RGHT)),  _______,    _______,    _______,    _______,    LSFT(KC_UP),    _______,    _______,    _______,     _______, TG(CL), KC_BSPC,
      _______,          _______,    _______,    _______,      _______,    _______,    LSFT(LCTL(KC_LEFT)),   LSFT(KC_DOWN),   LSFT(KC_RGHT),     _______,    KC_SCLN,  KC_QUOT, KC_LGUI,
      KC_LSFT,          _______,  _______, _______,      _______,    LSFT(LCTL(KC_LEFT)),    _______,    _______,    _______,    _______,    KC_SLSH,    OSM(MOD_LSFT), TO(CL),
      _______, TD(CTL_NM),                     TD(ALT_NM),                 KC_SPC,    LM(CL,MOD_LGUI|MOD_LALT), OSL(ACCENT), _______
      ),
  [ACCENT] = LAYOUT(
      _______,       KC_F1,  KC_F2, KC_F3,    KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,  KC_F12,  _______, _______,
      _______,         RGB_TOG,    RGB_LYR,  RGB_RMOD,    RGB_MOD,    _______,    _______,    _______,    DE_UE,    _______,    _______,     _______, _______, _______,
      _______,            DE_AE,    _______,    DE_SS,      _______,    _______,    _______,   _______,   _______,     _______,    DE_OE,  _______, _______,
      OSL(ACCENT_CAP),     _______,  _______, _______,      _______,    _______,    _______,    _______,    _______,    _______,        _______, _______, TO(CL),
      _______,             _______,         _______,            _______,         _______, _______,  _______
      ),
  [ACCENT_CAP] = LAYOUT(
      _______,   _______,  _______, _______,    _______,          _______,     _______,     _______,     _______,     _______,     _______,    _______,  _______,  _______, _______,
      _______,      _______,    _______,  _______,    _______,    _______,    _______,    _______,    DE_UE_CAP,    _______,    _______,     _______, _______, _______,
      _______,        DE_AE_CAP,    _______,    DE_SS,      _______,    _______,    _______,   _______,   _______,     _______,    DE_OE_CAP,  _______, TO(CL),
      _______,      _______, _______,      _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______, _______, _______,
      _______,   _______,         _______,         _______,         _______,   _______,      _______
      ),
  [BRCKS] = LAYOUT(
      _______,   _______,  _______, _______,    _______,          _______,     _______,     _______,     _______,     _______,     _______,    _______,  _______,  _______, _______,
      _______,      _______,    _______,  _______,    _______,    _______,    _______,    TD(QUOT),    KC_U,    _______,    _______,     _______, _______, _______,
      _______,        _______,    _______,    _______,      _______,    _______,    _______,   TD(R_BRC),   TD(A_BRC),     TD(S_BRC),    KC_ENT,  _______,   _______,
      _______,      _______, _______,      _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______, _______, _______,
      _______,   _______,         _______,         KC_LSFT,         _______,   _______,      _______
      ),
};
