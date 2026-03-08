// =============================================
//  Gab's Hackpad — config.h
//  RP2040 | 6 switches | encoder | OLED | RGB
// =============================================

#pragma once

// ── USB Identity ──────────────────────────
#define VENDOR_ID    0x6C62   // "lb" (Gab's initials placeholder)
#define PRODUCT_ID   0x6861   // "ha" for hackpad
#define DEVICE_VER   0x0001
#define MANUFACTURER "Gabouin"
#define PRODUCT      "Gab's Hackpad"

// ── Matrix (direct pins, no diodes needed) ─
#define MATRIX_ROWS 1
#define MATRIX_COLS 6
// Pins: GP0..GP5 declared in info.json

// ── Encoder button (press = mute) ──────────
#define ENCODER_BUTTON_PIN GP8

// ── OLED (SSD1306 via I2C) ─────────────────
#define I2C_DRIVER       I2CD1
#define I2C1_SDA_PIN     GP14
#define I2C1_SCL_PIN     GP15
#define OLED_DISPLAY_128X32
#define OLED_TIMEOUT     30000   // ms — turns off after 30s idle

// ── RGB (WS2812B) ──────────────────────────
#define RGB_DI_PIN       GP16
#define RGBLED_NUM       6
#define RGBLIGHT_LIMIT_VAL 150  // brightness cap (0-255)
#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_BREATHING
#define RGBLIGHT_DEFAULT_HUE  85   // green-ish (Spotify vibe)
#define RGBLIGHT_DEFAULT_SAT  255
#define RGBLIGHT_DEFAULT_VAL  80

// ── Tapping / debounce ─────────────────────
#define TAPPING_TERM     200
#define DEBOUNCE         5

// ── Encoder resolution ─────────────────────
#define ENCODER_RESOLUTION 4

// ── Key repeat ─────────────────────────────
#define FORCE_NKRO
