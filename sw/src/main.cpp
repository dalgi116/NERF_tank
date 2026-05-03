#include "Motor.h"
#include "pinout.h"
#include "config.h"
#include <Servo.h>

Motor left_belt_motor(COMMON_BELT_MOTOR_SPEED_PIN, LEFT_BELT_MOTOR_A_PIN, LEFT_BELT_MOTOR_B_PIN);
Motor right_belt_motor(COMMON_BELT_MOTOR_SPEED_PIN, RIGHT_BELT_MOTOR_A_PIN, RIGHT_BELT_MOTOR_B_PIN);
Motor horizontal_motor(HORIZONTAL_MOTOR_SPEED_PIN, HORIZONTAL_MOTOR_A_PIN, HORIZONTAL_MOTOR_B_PIN);
Motor vertical_motor(VERTICAL_MOTOR_SPEED_PIN, VERTICAL_MOTOR_A_PIN, VERTICAL_MOTOR_B_PIN);
Servo load_servo;

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

  load_servo.attach(LOAD_SERVO_PIN);
}

void loop() {
  static bool ON = 1;
  static uint8_t gear = 0;
  static uint64_t load_servo_timer = 0;

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
        Serial.print("Setting gear to: ");
        Serial.println(gear);
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

      // Cannon motors control
      case 'S':
        load_servo.write(load_servo_shoot_pos);
        load_servo_timer = millis();
        break;
      
      default:
        break;
      }   
    }
  }

  // Prepare for the next shot
  if (millis() - load_servo_timer > load_servo_delay_ms) {
    load_servo.write(load_servo_default_pos);
  }

}