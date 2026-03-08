// oled_display.h
#pragma once
#include QMK_KEYBOARD_H

oled_rotation_t oled_init_user(oled_rotation_t rotation);
bool oled_task_user(void);
