#include "main.hpp"
#include "pinout.h"

uint8_t speeds[3] = {50, 120, 255};

Motor left_belt_motor(COMMON_BELT_MOTOR_SPEED_PIN, LEFT_BELT_MOTOR_A_PIN, LEFT_BELT_MOTOR_B_PIN);
Motor right_belt_motor(COMMON_BELT_MOTOR_SPEED_PIN, RIGHT_BELT_MOTOR_A_PIN, RIGHT_BELT_MOTOR_B_PIN);

void setup() {
  Serial.begin(9600);
  left_belt_motor.init();
  right_belt_motor.init();
}

void loop() {
  static bool ON = 0;
  static uint8_t gear = 0;

  if (Serial.available()) {
    char command = Serial.read();
    Serial.print("Received command: ");
    Serial.println(command);

    if (command == '1') {
      ON = 1;
    }

    if (ON) {
      switch (command)
      {
      case '0':
        ON = 0;
        left_belt_motor.stop();
        right_belt_motor.stop();
        break;
      case '2':
        left_belt_motor.stop();
        break;
      case '3':
        right_belt_motor.stop();
        break;
      case 'L':
        left_belt_motor.set_direction(1);
        left_belt_motor.run();
        break;
      case 'l':
        left_belt_motor.set_direction(0);
        left_belt_motor.run();
        break;
      case 'R':
        right_belt_motor.set_direction(1);
        right_belt_motor.run();
        break;
      case 'r':
        right_belt_motor.set_direction(0);
        right_belt_motor.run();
        break;
      case 'G':
        while (!Serial.available());
        gear = Serial.read() - '0';
        left_belt_motor.set_speed(speeds[gear]);
        right_belt_motor.set_speed(speeds[gear]);
        break;
      
      default:
        break;
      }
    }
  }
}