#pragma once

#include <Arduino.h>

class Motor
{
private:
    uint8_t speed_pin;
    uint8_t a_pin;
    uint8_t b_pin;
    uint8_t speed;
    bool direction; // 1 forward, 0 backward
public:
    Motor(uint8_t, uint8_t, uint8_t);
    void init();
    void set_speed(uint8_t);
    void set_direction(bool);
    void run();
    void stop();
};

Motor::Motor(uint8_t speed_pin, uint8_t a_pin, uint8_t b_pin) {
    this->speed_pin = speed_pin;
    this->a_pin = a_pin;
    this->b_pin = b_pin;
}

void Motor::init() {
    pinMode(this->speed_pin, OUTPUT);
    pinMode(this->a_pin, OUTPUT);
    pinMode(this->b_pin, OUTPUT);
}

void Motor::set_speed(uint8_t speed) {
    this->speed = speed;
}

void Motor::set_direction(bool direction) {
    this->direction = direction;
}

void Motor::run() {
    digitalWrite(this->a_pin, this->direction);
    digitalWrite(this->b_pin, !this->direction);
    analogWrite(this->speed_pin, this->speed);
}

void Motor::stop() {
    digitalWrite(this->a_pin, LOW);
    digitalWrite(this->b_pin, LOW);
    analogWrite(this->speed_pin, 0);
}