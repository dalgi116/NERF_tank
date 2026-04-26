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
    void set(uint8_t, bool);
    void stop();
};

Motor::Motor(uint8_t speed_pin, uint8_t a_pin, uint8_t b_pin) {
    this->speed_pin = speed_pin;
    this->a_pin = a_pin;
    this->b_pin = b_pin;
};

void Motor::init() {
    pinMode(this->speed_pin, OUTPUT);
    pinMode(this->a_pin, OUTPUT);
    pinMode(this->b_pin, OUTPUT);
};

void Motor::set(uint8_t speed, bool direction) {
    this->speed = speed;
    this->direction = direction;
    digitalWrite(this->a_pin, direction);
    digitalWrite(this->b_pin, !direction);
    analogWrite(this->speed_pin, speed);
}

void Motor::stop() {
    digitalWrite(this->a_pin, LOW);
    digitalWrite(this->b_pin, LOW);
    analogWrite(this->speed_pin, 0);
};