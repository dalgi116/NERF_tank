#pragma once

#include <Arduino.h>

class Motor
{
private:
    uint8_t pin_s;  // Speed pin
    uint8_t pin_a;  // Direction pin A
    uint8_t pin_b;  // Direction pin B
    uint8_t speed;  // Speed value
    bool direction; // 1 forward, 0 backward
public:
    Motor(uint8_t, uint8_t, uint8_t);
    void init();
    void set_speed(uint8_t);
    void set_direction(bool);
    void run();
    void stop();
};

Motor::Motor(uint8_t pin_s, uint8_t pin_a, uint8_t pin_b) {
    this->pin_s = pin_s;
    this->pin_a = pin_a;
    this->pin_b = pin_b;
}

void Motor::init() {
    pinMode(this->pin_s, OUTPUT);
    pinMode(this->pin_a, OUTPUT);
    pinMode(this->pin_b, OUTPUT);
}

void Motor::set_speed(uint8_t speed) {
    this->speed = speed;
}

void Motor::set_direction(bool direction) {
    this->direction = direction;
}

void Motor::run() {
    digitalWrite(this->pin_a, this->direction);
    digitalWrite(this->pin_b, !this->direction);
    analogWrite(this->pin_s, this->speed);
}

void Motor::stop() {
    digitalWrite(this->pin_a, LOW);
    digitalWrite(this->pin_b, LOW);
    analogWrite(this->pin_s, 0);
}