#include "main.hpp"
#include "pinout.h"

constexpr uint8_t belt_motor_speeds[3] = {150, 200, 255};
constexpr uint8_t horizontal_motor_speed = 150;
constexpr uint8_t vertical_motor_speed = 150;

Motor left_belt_motor(COMMON_BELT_MOTOR_SPEED_PIN, LEFT_BELT_MOTOR_A_PIN, LEFT_BELT_MOTOR_B_PIN);
Motor right_belt_motor(COMMON_BELT_MOTOR_SPEED_PIN, RIGHT_BELT_MOTOR_A_PIN, RIGHT_BELT_MOTOR_B_PIN);
Motor horizontal_motor(HORIZONTAL_MOTOR_SPEED_PIN, HORIZONTAL_MOTOR_A_PIN, HORIZONTAL_MOTOR_B_PIN);
Motor vertical_motor(VERTICAL_MOTOR_SPEED_PIN, VERTICAL_MOTOR_A_PIN, VERTICAL_MOTOR_B_PIN);

void setup() {
  Serial.begin(9600);

  left_belt_motor.init();
  right_belt_motor.init();
  horizontal_motor.init();
  vertical_motor.init();

  left_belt_motor.set_speed(belt_motor_speeds[0]);
  right_belt_motor.set_speed(belt_motor_speeds[0]);
  horizontal_motor.set_speed(horizontal_motor_speed);
  vertical_motor.set_speed(vertical_motor_speed);
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
      // ON-OFF control
      case '0':
        ON = 0;
        left_belt_motor.stop();
        right_belt_motor.stop();
        horizontal_motor.stop();
        vertical_motor.stop();
        break;

      // Belt motors control
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
        left_belt_motor.set_speed(belt_motor_speeds[gear]);
        right_belt_motor.set_speed(belt_motor_speeds[gear]);
        break;

      // Turret motors control
      case '4':
        horizontal_motor.stop();
        break;
      case '5':
        vertical_motor.stop();
        break;
      case 'H':
        horizontal_motor.set_direction(1);
        horizontal_motor.run();
        break;
      case 'h':
        horizontal_motor.set_direction(0);
        horizontal_motor.run();
        break;
      case 'V':
        vertical_motor.set_direction(1);
        vertical_motor.run();
        break;
      case 'v':
        vertical_motor.set_direction(0);
        vertical_motor.run();
        break;
      
      default:
        break;
      }
    }
  }
}