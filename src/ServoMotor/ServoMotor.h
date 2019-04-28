#include <Arduino.h>
#include "Servo.h"

#ifndef ServoMotor_h
#define ServoMotor_h

class ServoMotor : public Servo
{
  public:
    ServoMotor(uint8_t _pin);
    int write(uint8_t _value);
  private:
    int pin;
    boolean _attached;
};

#endif
