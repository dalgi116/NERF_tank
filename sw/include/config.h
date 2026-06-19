#pragma once

#include <Arduino.h>

constexpr uint16_t BAUD_RATE    = 9600;             // Serial communication baud rate
constexpr uint8_t  BM_SPEEDS[3] = {200, 230, 255};  // Belt motors speeds for gears 0, 1, 2
constexpr uint8_t  HM_SPEED     = 150;              // Horizontal motor speed
constexpr uint8_t  VM_SPEED     = 150;              // Vertical motor speed
constexpr uint8_t  LS_DEF_POS   = 90;               // Load servo default position
constexpr uint8_t  LS_SHOOT_POS = 180;              // Load servo shoot position
constexpr uint16_t LS_DELAY_MS  = 500;              // Load servo delay in milliseconds