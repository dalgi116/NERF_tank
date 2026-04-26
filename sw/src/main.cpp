#include "main.hpp"

#define LEFT_MOTOR_SPEED_PIN  7
#define LEFT_MOTOR_A_PIN      8
#define LEFT_MOTOR_B_PIN      9
#define RIGHT_MOTOR_SPEED_PIN 10
#define RIGHT_MOTOR_A_PIN     11
#define RIGHT_MOTOR_B_PIN     12

uint8_t speeds[3] = {100, 150, 255};

Motor left_motor(LEFT_MOTOR_SPEED_PIN, LEFT_MOTOR_A_PIN, LEFT_MOTOR_B_PIN);
Motor right_motor(RIGHT_MOTOR_SPEED_PIN, RIGHT_MOTOR_A_PIN, RIGHT_MOTOR_B_PIN);

void setup() {
  Serial.begin(9600);
  left_motor.init();
  right_motor.init();
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
        left_motor.set(0, 0);
        right_motor.set(0, 0);
        break;
      case '2':
        left_motor.stop();
        break;
      case '3':
        right_motor.stop();
        break;
      case 'L':
        left_motor.set(speeds[gear], 1);
        break;
      case 'l':
        left_motor.set(speeds[gear], 0);
        break;
      case 'R':
        right_motor.set(speeds[gear], 1);
        break;
      case 'r':
        right_motor.set(speeds[gear], 0);
        break;
      case 'G':
        while (!Serial.available());
        gear = Serial.read() - '0';
        break;
      
      default:
        break;
      }
    }
  }
}