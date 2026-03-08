# =============================================
#  Gab's Hackpad — rules.mk
# =============================================

MCU            = RP2040
BOOTLOADER     = rp2040

# Core features
ENCODER_ENABLE    = yes
ENCODER_MAP_ENABLE = yes
OLED_ENABLE       = yes
OLED_DRIVER       = ssd1306
RGBLIGHT_ENABLE   = yes
EXTRAKEY_ENABLE   = yes   # Media keys (play, volume, etc.)
NKRO_ENABLE       = yes
BOOTMAGIC_ENABLE  = yes
MOUSEKEY_ENABLE   = no
CONSOLE_ENABLE    = no
COMMAND_ENABLE    = no
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE  = no

# Custom OLED rendering
SRC += oled_display.c
