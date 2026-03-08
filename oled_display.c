// =============================================
//  Gab's Hackpad — oled_display.c
//  SSD1306 128x32 — custom render
// =============================================

#include QMK_KEYBOARD_H
#include "oled_display.h"

// ── Logo (32x32 pixels, 1-bit, stored in flash) ───────────
// Simple "G" logo splash — replace with your own via
// QMK logo generator: https://joric.github.io/qle/
static const char PROGMEM hackpad_logo[] = {
    // 128x32 px bitmap (512 bytes) — blank placeholder
    // To generate: convert a 128x32 PNG to QMK byte array
    0x00, 0x00, 0x00, 0x00,  // row 0  (truncated for readability)
    // ... (fill with your actual logo bytes)
    0x00
};

// ── Layer name strings ─────────────────────
static const char *layer_names[] = {
    "SPOTIFY",
    "MACROS ",
    "RGB    ",
};

// ── WPM / idle counter (optional) ─────────
static uint16_t idle_timer = 0;
static bool     oled_off   = false;

// ── Main render callback ──────────────────
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_0;  // 128x32, landscape
}

bool oled_task_user(void) {
    // Auto-off after OLED_TIMEOUT (set in config.h)
    if (last_input_activity_elapsed() > OLED_TIMEOUT) {
        oled_off_user();
        return false;
    }

    // ── Top line: keyboard name ──────────────
    oled_set_cursor(0, 0);
    oled_write_P(PSTR("Gab's Hackpad"), false);

    // ── Bottom line: current layer ───────────
    oled_set_cursor(0, 1);
    oled_write_P(PSTR("Layer: "), false);

    uint8_t layer = get_highest_layer(layer_state);
    if (layer < (sizeof(layer_names) / sizeof(layer_names[0]))) {
        oled_write(layer_names[layer], false);
    } else {
        oled_write_P(PSTR("???????"), false);
    }

    // ── Bottom right: encoder indicator ──────
    oled_set_cursor(14, 1);
    oled_write_P(PSTR("ENC"), false);

    return false;
}
