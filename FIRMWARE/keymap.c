// =============================================
//  Gab's Hackpad — keymaps/default/keymap.c
//  Spotify controls + encoder volume
// =============================================

#include QMK_KEYBOARD_H

// ── Layer definitions ─────────────────────
enum hackpad_layers {
    _SPOTIFY = 0,   // Default: Spotify controls
    _MACRO,         // Layer 1: Custom macros (hold SW6 to access)
    _RGB,           // Layer 2: RGB control (hold SW5 to access)
};

// ── Custom keycodes ───────────────────────
enum hackpad_keycodes {
    SP_SHUF = SAFE_RANGE,  // Spotify shuffle  (Ctrl+Shift+S)
    SP_LIKE,               // Spotify like      (Alt+Shift+B)
    SP_SRCH,               // Spotify search    (Ctrl+L)
    RGB_TOG_LAYER,         // Toggle RGB layer indicator
};

// ── Keymap ────────────────────────────────
//
//   ┌───────┬───────┬───────┐
//   │  SW1  │  SW2  │  SW3  │
//   │ Play  │ Prev  │ Next  │
//   ├───────┼───────┼───────┤
//   │  SW4  │  SW5  │  SW6  │
//   │ Stop  │Shuffle│ Like  │
//   └───────┴───────┴───────┘
//   Encoder CW  = Vol+
//   Encoder CCW = Vol-
//   Encoder BTN = Mute
//
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_SPOTIFY] = LAYOUT(
        KC_MPLY,   KC_MPRV,   KC_MNXT,
        KC_MSTP,   SP_SHUF,   SP_LIKE
    ),

    [_MACRO] = LAYOUT(
        LCTL(KC_C),   LCTL(KC_V),   LCTL(KC_Z),
        LCTL(KC_S),   LCTL(KC_A),   LCTL(KC_F4)
    ),

    [_RGB] = LAYOUT(
        RGB_TOG,   RGB_MOD,   RGB_RMOD,
        RGB_HUI,   RGB_SAI,   RGB_VAI
    ),
};

// ── Encoder map ───────────────────────────
// Encoder 0: CW = Vol+, CCW = Vol-, each layer
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_SPOTIFY] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_MACRO]   = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_RGB]     = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)  },
};
#endif

// ── Custom keycode processing ─────────────
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

        case SP_SHUF:  // Ctrl+Shift+S — Spotify shuffle toggle
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_LSFT);
                tap_code(KC_S);
                unregister_code(KC_LSFT);
                unregister_code(KC_LCTL);
            }
            return false;

        case SP_LIKE:  // Alt+Shift+B — Save/like current track
            if (record->event.pressed) {
                register_code(KC_LALT);
                register_code(KC_LSFT);
                tap_code(KC_B);
                unregister_code(KC_LSFT);
                unregister_code(KC_LALT);
                // Flash RGB red briefly as visual feedback
                rgblight_setrgb_range(255, 0, 80, 0, RGBLED_NUM);
            }
            return false;

        case SP_SRCH:  // Ctrl+L — Spotify search bar
            if (record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_L);
                unregister_code(KC_LCTL);
            }
            return false;

        default:
            return true;
    }
}

// ── Encoder button (GP8) via matrix or direct ──
// If you wire ENC_BTN to a direct pin outside the matrix,
// handle it here as a custom pin callback:
bool encoder_update_user(uint8_t index, bool clockwise) {
    // Handled by encoder_map above; this is a fallback hook.
    return false;
}

// ── RGB layer indicator ───────────────────
// Flash different hues when changing layers
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _SPOTIFY:
            rgblight_sethsv_noeeprom(85, 255, 80);   // green
            break;
        case _MACRO:
            rgblight_sethsv_noeeprom(170, 255, 80);  // blue
            break;
        case _RGB:
            rgblight_sethsv_noeeprom(0, 255, 80);    // red
            break;
        default:
            rgblight_sethsv_noeeprom(85, 255, 80);
            break;
    }
    return state;
}
