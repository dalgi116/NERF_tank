#pragma once

#include <Arduino.h>

constexpr uint8_t belt_motor_speeds[3]      = {200, 230, 255};
constexpr uint8_t horizontal_motor_speed    = 150;
constexpr uint8_t vertical_motor_speed      = 150;
constexpr uint8_t load_servo_default_pos    = 90;
constexpr uint8_t load_servo_shoot_pos      = 180;
constexpr uint16_t load_servo_delay_ms      = 500;