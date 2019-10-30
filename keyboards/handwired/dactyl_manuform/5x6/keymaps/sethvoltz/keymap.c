/* A standard layout for the Dactyl Manuform 5x6 Keyboard */

#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum custom_keycodes {
  RAISE = SAFE_RANGE,
  LOWER
};

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_5x6(
    KC_GRAVE, KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                                 KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINUS,
    KC_ESC,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                                 KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_EQUAL,
    KC_LSFT,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                                 KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
    KC_LCTL,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,                                 KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_BSLASH,
                        _______,  _______,                                                                      KC_LBRC,  KC_RBRC,
                                                      RAISE,    KC_SPC,           KC_ENT,   LOWER,
                                                      KC_LALT,  KC_LGUI,          KC_RGUI,  KC_RALT,
                                                      KC_LCTL,  KC_TAB,           KC_TAB,   KC_RCTL
  ),

  [_LOWER] = LAYOUT_5x6(
    KC_TILD,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,                              KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_UNDS,
    _______,  _______,  _______,  KC_PGUP,  _______,  KC_LBRC,                              KC_RBRC,  KC_P7,    KC_P8,    KC_P9,    _______,  _______,
    _______,  _______,  KC_HOME,  KC_PGDN,  KC_END ,  KC_LPRN,                              KC_RPRN,  KC_P4,    KC_P5,    KC_P6,    _______,  _______,
    _______,  _______,  _______,  _______,  _______,  KC_MINS,                              KC_UNDS,  KC_P1,    KC_P2,    KC_P3,    _______,  _______,
                        _______,  _______,                                                                      _______,  KC_P0,
                                                      _______,  _______,          KC_DEL,   _______,
                                                      _______,  _______,          _______,  _______,
                                                      _______,  _______,          _______,  _______

  ),

  [_RAISE] = LAYOUT_5x6(
    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,                                KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,
    _______,  _______,  _______,  KC_UP  ,  _______,  KC_LBRC,                              KC_RBRC,  _______,  KC_NLCK,  KC_INS,   KC_SLCK,  KC_VOLU,
    _______,  _______,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_LPRN,                              KC_RPRN,  KC_MPRV,  KC_MPLY,  KC_MNXT,  _______,  KC_VOLD,
    _______,  _______,  _______,  _______,  _______,  KC_MINS,                              KC_UNDS,  _______,  _______,  _______,  _______,  KC_MUTE,
                        _______,  _______,                                                                      _______,  _______,
                                                      _______,  _______,          KC_BSPC,  _______,
                                                      _______,  _______,          _______,  _______,
                                                      _______,  _______,          _______,  _______
  ),
};

static bool is_raised = false;
static bool is_lowered = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RAISE:
      if (record->event.pressed) {
        if (is_lowered) {
          layer_off(_LOWER);
          register_mods(MOD_HYPR);
        } else {
          layer_on(_RAISE);
        }
        is_raised = true;
      } else {
        if (is_lowered) {
          unregister_mods(MOD_HYPR);
          layer_on(_LOWER);
        } else {
          layer_off(_RAISE);
        }
        is_raised = false;
      }
      return false; // Skip all further processing of this key
    case LOWER:
      if (record->event.pressed) {
        if (is_raised) {
          layer_off(_RAISE);
          register_mods(MOD_HYPR);
        } else {
          layer_on(_LOWER);
        }
        is_lowered = true;
      } else {
        if (is_raised) {
          unregister_mods(MOD_HYPR);
          layer_on(_RAISE);
        } else {
          layer_off(_LOWER);
        }
        is_lowered = false;
      }
      return false; // Skip all further processing of this key
    default:
      return true; // Process all other keycodes normally
  }
}
