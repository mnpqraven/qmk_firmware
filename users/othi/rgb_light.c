#include "rgb_light.h"
void matrix_init_user(void) {
    // Call the keymap level matrix init.
    // Read the user config from EEPROM
    user_config.raw = eeconfig_read_user();
    // Set default layer, if enabled
    if (user_config.rgb_layer_change) {
        rgblight_enable_noeeprom();
        rgblight_sethsv_noeeprom(OTHI_DEFAULT_R, OTHI_DEFAULT_G, OTHI_DEFAULT_B);
        rgblight_mode_noeeprom(OTHI_DEFAULT_MODE);
    }
}
void rgblight_sethsv_noeeprom_user(uint16_t hue, uint8_t sat, uint8_t val) {
  rgblight_sethsv_eeprom_helper_user(hue, sat, val, false);
}

void rgblight_sethsv_eeprom_helper_user(uint16_t hue, uint8_t sat, uint8_t val, bool write_to_eeprom) {
    if (rgblight_config.mode == RGBLIGHT_MODE_STATIC_LIGHT) {
        //OUTDATED
        //TODO where broke
      // same static color
      //LED_TYPE tmp_led;
      //sethsv(hue, sat, val, &tmp_led); //appears to be broken
      //if (strcmp(QMK_KEYBOARD, "kbd6x") != 0) {
      //rgblight_setrgb_at(tmp_led.r, tmp_led.g, tmp_led.b,0); wait_ms(1);
      //rgblight_setrgb_at(tmp_led.r, tmp_led.g, tmp_led.b,1); wait_ms(1);
      //rgblight_setrgb_at(tmp_led.r, tmp_led.g, tmp_led.b,6); wait_ms(1);
      //rgblight_setrgb_at(tmp_led.r, tmp_led.g, tmp_led.b,7); wait_ms(1);
      //rgblight_setrgb_at(tmp_led.r, tmp_led.g, tmp_led.b,8); wait_ms(1);
      //rgblight_setrgb_at(tmp_led.r, tmp_led.g, tmp_led.b,9); wait_ms(1);
      //rgblight_setrgb_at(tmp_led.r, tmp_led.g, tmp_led.b,14); wait_ms(1);
      //rgblight_setrgb_at(tmp_led.r, tmp_led.g, tmp_led.b,15); wait_ms(1);
      //}
      //} else {
      //rgblight_setrgb_at(tmp_led.r, tmp_led.g, tmp_led.b,1); wait_ms(1);
      //rgblight_setrgb_at(tmp_led.r, tmp_led.g, tmp_led.b,2); wait_ms(1);
      //rgblight_setrgb_at(tmp_led.r, tmp_led.g, tmp_led.b,3); wait_ms(1);
      //rgblight_setrgb_at(tmp_led.r, tmp_led.g, tmp_led.b,4); wait_ms(1);
      //rgblight_setrgb_at(tmp_led.r, tmp_led.g, tmp_led.b,8); wait_ms(1);
      //rgblight_setrgb_at(tmp_led.r, tmp_led.g, tmp_led.b,9); wait_ms(1);
      //rgblight_setrgb_at(tmp_led.r, tmp_led.g, tmp_led.b,10); wait_ms(1);
      //rgblight_setrgb_at(tmp_led.r, tmp_led.g, tmp_led.b,11); wait_ms(1);
      //}
        //if (strcmp(QMK_KEYBOARD, "kbd6x") != 0) {
        //    sethsv(hue, sat, val, (LED_TYPE *)&led[0]); wait_ms(1);
        //    sethsv(hue, sat, val, (LED_TYPE *)&led[1]); wait_ms(1);
        //    sethsv(hue, sat, val, (LED_TYPE *)&led[2]); wait_ms(1);
        //    sethsv(hue, sat, val, (LED_TYPE *)&led[3]); wait_ms(1);
        //    sethsv(hue, sat, val, (LED_TYPE *)&led[4]); wait_ms(1);
        //    sethsv(hue, sat, val, (LED_TYPE *)&led[5]); wait_ms(1);
        //    sethsv(hue, sat, val, (LED_TYPE *)&led[6]); wait_ms(1);
        //    sethsv(hue, sat, val, (LED_TYPE *)&led[7]); wait_ms(1);
        //    sethsv(hue, sat, val, (LED_TYPE *)&led[8]); wait_ms(1);
        //    sethsv(hue, sat, val, (LED_TYPE *)&led[9]); wait_ms(1);
        //    sethsv(hue, sat, val, (LED_TYPE *)&led[10]); wait_ms(1);
        //    sethsv(hue, sat, val, (LED_TYPE *)&led[11]); wait_ms(1);
        //} else if (strcmp(QMK_KEYBOARD, "kbd6x") != 0) {
        //    sethsv(hue, sat, val, (LED_TYPE *)&led[0]); wait_ms(1);
        //    sethsv(hue, sat, val, (LED_TYPE *)&led[7]); wait_ms(1);
        //    sethsv(hue, sat, val, (LED_TYPE *)&led[8]); wait_ms(1);
        //    sethsv(hue, sat, val, (LED_TYPE *)&led[15]); wait_ms(1);
        //}
        //} else if (strcmp(QMK_KEYBOARD, "Space65") != 0) {
        //    sethsv(hue, sat, val, (LED_TYPE *)&led[0]); wait_ms(1);
        //sethsv(hue, sat, val, (LED_TYPE *)&led[0]); wait_ms(1);
        //sethsv(hue, sat, val, (LED_TYPE *)&led[1]); wait_ms(1);
        //sethsv(hue, sat, val, (LED_TYPE *)&led[2]); wait_ms(1);
        //rgblight_set();
        if (strcmp(QMK_KEYBOARD,"gray_studio/space65") == 0) {
            //rgblight_sethsv_noeeprom(hue, sat, val);
            rgblight_sethsv_at(hue, sat, val, 0); wait_ms(1);
            rgblight_sethsv_at(hue, sat, val, 1); wait_ms(1);
            rgblight_sethsv_at(hue, sat, val, 2); wait_ms(1);
        } else if (strcmp(QMK_KEYBOARD,"dz60") == 0) {
            rgblight_sethsv_at(hue, sat, val, 0); wait_ms(1);
            rgblight_sethsv_at(hue, sat, val, 7); wait_ms(1);
            rgblight_sethsv_at(hue, sat, val, 8); wait_ms(1);
            rgblight_sethsv_at(hue, sat, val, 15); wait_ms(1);
    }
}
}
uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
        case NM_MODE:
            if (user_config.rgb_layer_change) {
                //rgblight_sethsv_noeeprom_green();
                rgblight_mode_noeeprom(1);
                rgblight_sethsv_noeeprom_user(140,255,255); //springgreen
            } break;
        case VI_MODE:
            if (user_config.rgb_layer_change) {
                rgblight_mode_noeeprom(1);
                rgblight_sethsv_noeeprom_user(39,255,255); //orange
            } break;
        case ACCENT:
            if (user_config.rgb_layer_change) {
                rgblight_mode_noeeprom(1);
                rgblight_sethsv_noeeprom_user(0,0,255); //white
            } break;
        case BRCKS:
            if (user_config.rgb_layer_change) {
                rgblight_mode_noeeprom(1);
                rgblight_sethsv_noeeprom_user(0,0,255); //magenta
            } break;
        case FNUM: break; //FNUM does not interrult breathing
        default: //for default and other layers, to change it go to othi.h
            if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom(OTHI_DEFAULT_R, OTHI_DEFAULT_G, OTHI_DEFAULT_B);
                rgblight_mode_noeeprom(OTHI_DEFAULT_MODE);
            } break;
    }
    return state;
}

//void matrix_scan_user(void) {
//
//}
