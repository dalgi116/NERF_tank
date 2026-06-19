#include "Motor.h"
#include "pinout.h"
#include "config.h"
#include <Servo.h>

Motor LBM(LRBM_PIN_S, LBM_PIN_A, LBM_PIN_B);    // Left belt motor
Motor RBM(LRBM_PIN_S, RBM_PIN_A, RBM_PIN_B);    // Right belt motor
Motor HM (HM_PIN_S, HM_PIN_A, HM_PIN_B);        // Horizontal motor
Motor VM (VM_PIN_S, VM_PIN_A, VM_PIN_B);        // Vertical motor
Servo LS;                                       // Load servo

void    stop_all_motors();
uint8_t read_serial_value();