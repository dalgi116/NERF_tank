#include "main.hpp"

void setup() {
  // Initialize serial communication
  Serial.begin(BAUD_RATE);

  // Initialize motors and servo
  LBM.init();
  RBM.init();
  HM.init();
  VM.init();

  // Set initial speeds for motors
  LBM.set_speed(BM_SPEEDS[0]);
  RBM.set_speed(BM_SPEEDS[0]);
  HM.set_speed(HM_SPEED);
  VM.set_speed(VM_SPEED);

  // Set servo pin
  LS.attach(LS_PIN);
}

void loop() {
  static bool    EN   = 1;  // Enable serial control
  static uint8_t gear = 0;  // Belt motors gear (0, 1, 2)

  if (!Serial.available()) {
    // No command received, do nothing
    return;
  }

  //-----------------------
  // COMMAND PROCESSING
  //-----------------------
  char command = Serial.read();
  Serial.print("Command: ");
  Serial.println(command);

  if (command == '1') {
    // Enable serial control
    EN = 1;
  }

  if (!EN) {
    // Serial control is disabled, ignore commands
    return;
  }

  switch (command) {
    //-----------------------
    // Enable toggle
    //-----------------------
    case '0': // Disable serial control
      EN = 0;
      stop_all_motors();
      break;
    
    //-----------------------
    // Belt motors control
    //-----------------------
    case '2': // Stop left belt motor
      LBM.stop();
      break;
    case '3': // Stop right belt motor
      RBM.stop();
      break;
    case 'L': // Run left belt motor forward
      LBM.set_direction(1);
      LBM.run();
      break;
    case 'l': // Run left belt motor backward
      LBM.set_direction(0);
      LBM.run();
      break;
    case 'R': // Run right belt motor forward
      RBM.set_direction(1);
      RBM.run();
      break;
    case 'r': // Run right belt motor backward
      RBM.set_direction(0);
      RBM.run();
      break;
    case 'G': // Set belt motors gear
      gear = read_serial_value();
      LBM.set_speed(BM_SPEEDS[gear]);
      RBM.set_speed(BM_SPEEDS[gear]);
      break;
      
    //-----------------------
    // Turret motors control
    //-----------------------
    case '4': // Stop horizontal motor
      HM.stop();
      break;
    case '5': // Stop vertical motor
      VM.stop();
      break;
    case 'H': // Run horizontal motor right
      HM.set_direction(1);
      HM.run();
      break;
    case 'h': // Run horizontal motor left
      HM.set_direction(0);
      HM.run();
      break;
    case 'V': // Run vertical motor up
      VM.set_direction(1);
      VM.run();
      break;
    case 'v': // Run vertical motor down
      VM.set_direction(0);
      VM.run();
      break;

    //-----------------------
    // Cannon motors control
    //-----------------------
    case 'S': // Shoot
      break;
    
    default:
      break;
  }
}

void stop_all_motors() {
  LBM.stop();
  RBM.stop();
  HM.stop();
  VM.stop();
}

uint8_t read_serial_value() {
  while (!Serial.available()) {
    // Wait for a value to be available
  };
  uint8_t value = Serial.read() - '0';
  return value;
}