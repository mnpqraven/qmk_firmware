/* Copyright 2019 MechMerlin
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

  [CL] = LAYOUT_all(
    F_ESC,             KC_1,             KC_2,    KC_3,  KC_4,  KC_5,  KC_6,   KC_7,  KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,
    KC_TAB,            LT(NM_MODE,KC_Q), KC_W,    KC_F,  KC_P,  KC_G,  KC_J,   KC_L,  KC_U,    KC_Y,   KC_SCLN, KC_LBRC, KC_RBRC, KC_BSPC,
    KC_LCTL,           KC_A,             KC_R,    KC_S,  KC_T,  KC_D,  KC_H,   KC_N,  KC_E,    KC_I,   KC_O,    KC_QUOT, KC_ENT,  KC_ENT,
    TD(SFT_NM), KC_NO, KC_Z,             KC_X,    KC_C,  KC_V,  KC_B,  KC_K,   KC_M,  KC_COMM, KC_DOT, KC_SLSH, LM(CL,MOD_LGUI|MOD_LSFT),  MO(NM_MODE),
    KC_LCTL,           KC_LGUI,          KC_LALT,         KC_SPC,    LCTL(KC_SPC),      KC_BSPC,       LM(CL,MOD_LGUI|MOD_LALT), LGUI(KC_SPC), TG(GAME),  TO(CL)
  ),

  [GAME] = LAYOUT_all(
    KC_GESC,        KC_1,    KC_2,    KC_3,  KC_4,  KC_5,  KC_6,   KC_7,  KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,
    KC_TAB,         KC_Q,    KC_W,    KC_F,  KC_P,  KC_G,  KC_J,   KC_L,  KC_U,    KC_Y,   KC_SCLN, KC_LBRC, KC_RBRC, KC_BSPC,
    KC_LCTL,        KC_A,    KC_R,    KC_S,  KC_T,  KC_D,  KC_H,   KC_N,  KC_E,    KC_I,   KC_O,    KC_QUOT, KC_ENT,  KC_ENT,
    KC_LSFT, KC_NO, KC_Z,    KC_X,    KC_C,  KC_V,  KC_B,  KC_K,   KC_M,  KC_COMM, KC_DOT, KC_SLSH, KC_LSFT,  MO(NM_MODE),
    KC_LCTL,          KC_LGUI, KC_LALT,         KC_SPC,    LCTL(KC_SPC),      KC_BSPC,       KC_LALT, LGUI(KC_SPC), TG(GAME),  TO(CL)
  ),

  [NM_MODE] = LAYOUT_all(
    KC_TRNS, KC_MPRV, KC_MNXT, KC_MPLY, KC_END,  KC_F5,   KC_F6,   KC_F7,     KC_F8,   KC_F9,   KC_HOME,  KC_F11,  KC_F12,  KC_DEL, KC_DEL,
    KC_TRNS, KC_TRNS, LCTL(KC_RGHT),    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_UP,   KC_PGUP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_LEFT,    _______,       KC_RGHT, KC_TRNS, KC_PGDN,   KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_ENT, KC_TRNS, KC_TRNS, LCTL(KC_ENT),
    KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,          KC_SPC,  KC_SPC,      KC_SPC,               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [ACCENT] = LAYOUT_all(
    KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4,  KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL, KC_DEL,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,    KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,         KC_SPC,    KC_SPC,      KC_SPC,               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),
};
