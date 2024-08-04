/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

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

#include QMK_KEYBOARD_H

int enc_mode = 0;

enum my_keycodes {
  MY_RGB0 = SAFE_RANGE,
  MY_RGB1,
  MY_RGB2,
  MY_RGB3,
  MY_RGB4,
  MY_RGB5,
  MY_RGB6,
  MY_RGB7,
  MY_RGB8,
  MY_RGB9,
  MY_ENHU,
  MY_ENBR,
  MY_ENSP,
  MY_ENSA,
  MY_ENMD,
  MYM_NAZ,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the RESET key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    //
    // This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
    // Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
    // Press Fn+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [1] = LAYOUT(
        KC_SLEP, KC_MSEL, KC_VOLD, KC_VOLU, KC_MUTE, KC_MSTP, KC_MPRV, KC_MPLY, KC_MNXT, KC_MYCM, KC_WHOM, KC_CALC, KC_F24,  KC_F23,           RGB_TOG,
        _______, KC_F21,  KC_F22,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  _______, _______, _______,          RGB_VAI,
        _______, MY_RGB0, MY_RGB1, MY_RGB2, MY_RGB3, MY_RGB4, MY_RGB5, MY_RGB6, MY_RGB7, MY_RGB8, MY_RGB9, _______, _______, QK_BOOT,          RGB_SPI,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_SAI,          _______,          RGB_HUI,
        _______,          _______, _______, _______, _______, _______, MYM_NAZ, _______, KC_WBAK, KC_WFWD, _______,          _______, MY_ENHU, RGB_MOD,
        _______, _______, _______,                            _______,                            _______,   _______, MY_ENMD, MY_ENSP, MY_ENBR, MY_ENSA
    ),

};
// clang-format on

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (clockwise) {
    switch (enc_mode) {
      case 1:
        rgb_matrix_increase_hue();
        break;
      case 2:
        rgb_matrix_increase_val();
        break;
      case 3:
        rgb_matrix_increase_speed();
        break;
      case 4:
        rgb_matrix_increase_sat();
        break;
      case 5:
        rgb_matrix_step();
        break;

      default:
        return true;
    }
  } else {
    switch (enc_mode) {
      case 1:
        rgb_matrix_decrease_hue();
        break;
      case 2:
        rgb_matrix_decrease_val();
        break;
      case 3:
        rgb_matrix_decrease_speed();
        break;
      case 4:
        rgb_matrix_decrease_sat();
        break;
      case 5:
        rgb_matrix_step_reverse();
        break;
      default:
        return true;
    }
  }
  return true;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MY_RGB0:
      rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);          // Can use RGB_M_P built-in keycode instead.
      break;
    case MY_RGB1:
      rgb_matrix_mode(RGB_MATRIX_SOLID_MULTISPLASH);
      break;
    case MY_RGB2:
      rgb_matrix_mode(RGB_MATRIX_MULTISPLASH);
      break;
    case MY_RGB3:
      rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_SIMPLE);
      break;
    case MY_RGB4:
      rgb_matrix_mode(RGB_MATRIX_ALPHAS_MODS);
      break;
    case MY_RGB5:
      rgb_matrix_mode(RGB_MATRIX_HUE_BREATHING);
      break;
    case MY_RGB6:
      rgb_matrix_mode(RGB_MATRIX_GRADIENT_UP_DOWN);
      break;
    case MY_RGB7:
      rgb_matrix_mode(RGB_MATRIX_JELLYBEAN_RAINDROPS);
      break;
    case MY_RGB8:
      rgb_matrix_mode(RGB_MATRIX_DIGITAL_RAIN);
      break;
    case MY_RGB9:
      rgb_matrix_mode(RGB_MATRIX_TYPING_HEATMAP);
      break;

    case MY_ENHU:
      if (record->event.pressed) {
        enc_mode = 1;
      } else {
        enc_mode = 0;
      }
      break;
    case MY_ENBR:
      if (record->event.pressed) {
        enc_mode = 2;
      } else {
        enc_mode = 0;
      }
      break;
    case MY_ENSP:
      if (record->event.pressed) {
        enc_mode = 3;
      } else {
        enc_mode = 0;
      }
      break;
    case MY_ENSA:
      if (record->event.pressed) {
        enc_mode = 4;
      } else {
        enc_mode = 0;
      }
      break;
    case MY_ENMD:
      if (record->event.pressed) {
        enc_mode = 5;
      } else {
        enc_mode = 0;
      }
      break;

    case MYM_NAZ:
      if (record->event.pressed) {
        SEND_STRING("http://aei.pw/n.gif");
      } 
      break;
    
    default:
      return true;
  }
  return false;   
};
