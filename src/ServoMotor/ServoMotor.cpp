#include "ServoMotor.h"
#include "../EduIntro.h"

ServoMotor::ServoMotor(uint8_t _pin)
{
  Servo();
  pin = _pin;
  _attached = false;
}

int ServoMotor::write(uint8_t _value)
{
  if (!_attached) {
    attach(pin);
    _attached = true;
    }
  Servo::write(_value);
}
