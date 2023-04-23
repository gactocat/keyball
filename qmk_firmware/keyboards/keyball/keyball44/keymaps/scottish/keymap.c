/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default
  [0] = LAYOUT_universal(
    CMD_T(KC_TAB) , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                        KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_MINS  ,
    CTL_T(KC_ESC) , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                        KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , KC_QUOT  ,
    KC_LSFT       , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                                        KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_EQL   ,
                    KC_LALT  , CMD_T(KC_LNG2) , LT(1,KC_SPC)  , LT(3,KC_LNG1) , KC_BTN1 ,           KC_BSPC , LT(2,KC_ENT) , _______  , _______  ,            KC_RSFT
  ),

  [1] = LAYOUT_universal(
         _______  , KC_1     , KC_2     , KC_3     , KC_4     , KC_5     ,                                        KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , KC_BSLS  ,
         _______  , KC_BRID  , KC_BRIU  , KC_MPRV  , KC_MPLY  , KC_MNXT  ,                                       G(KC_LBRC),C(KC_DOWN), C(KC_UP) ,G(KC_RBRC), KC_LBRC  , KC_RBRC  ,
         _______  ,  _______ , KC_MUTE  , KC_VOLD  , KC_VOLU  , _______  ,                                        _______  , KC_BTN1  , KC_BTN3  , KC_BTN2  ,SCRL_MO   , KC_GRV   ,
                     _______ , _______  ,            _______  , _______  , _______  ,                   KC_DEL  , _______  , _______  , _______  ,            _______
  ),

  [2] = LAYOUT_universal(
         _______  , S(KC_1)  , S(KC_2)  , S(KC_3)  , S(KC_4)  , S(KC_5)  ,                                        S(KC_6)  , S(KC_7)  , S(KC_8)  , S(KC_9)  , S(KC_0)  ,S(KC_BSLS),
         _______  , KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                                        KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT  ,S(KC_LBRC),S(KC_RBRC),
         _______  , KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   ,                                        KC_F11   , KC_F12   , TO(0)    , TO(1)    , TO(2)    ,S(KC_GRV) ,
                    _______  , _______  ,            _______  , _______  , _______  ,                  _______  , _______  , _______  , _______  ,            _______
  ),

  [3] = LAYOUT_universal(
         RGB_TOG  , _______  , _______  , _______  , _______  , _______  ,                                        RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN , RGB_M_K  ,
         RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , _______  , SCRL_DVI ,                                        RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW , _______  , _______  ,
         RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , _______  , SCRL_DVD ,                                        CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , _______  , KBC_SAVE ,
                       QK_BOOT    , KBC_RST  , _______  ,        _______  , _______  ,                 _______  , _______  , _______  , KBC_RST  ,            QK_BOOT
  ),

  [4] = LAYOUT_universal(
         _______  , _______  , _______  , _______  , _______  , _______  ,                                        _______  , _______  , _______  , _______  , _______  , _______  ,
         _______  , _______  , _______  , _______  , _______  , _______  ,                                        _______  , KC_BTN1  , KC_BTN3  , KC_BTN2  , MO(3)    , _______  ,
         _______  , _______  , _______  , _______  , _______  , _______  ,                                        _______  , _______  , _______  , _______  , _______  , _______  ,
                    _______  , _______  ,            _______  , _______  , _______  ,                  _______  , _______  , _______  , _______  ,            _______
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    switch(get_highest_layer(remove_auto_mouse_layer(state, true))) {
        case 3:
            // Auto enable scroll mode when the highest layer is 3
            // remove_auto_mouse_target must be called to adjust state *before* setting enable
            state = remove_auto_mouse_layer(state, false);
            set_auto_mouse_enable(false);
            keyball_set_scroll_mode(true);
            break;
        default:
            set_auto_mouse_enable(true);
            keyball_set_scroll_mode(false);
            break;
    }
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
}
#endif

void pointing_device_init_user(void) {
    set_auto_mouse_enable(true);
}
