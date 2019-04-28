#include "Arduino.h"

#ifndef DigitalInput_h
#define DigitalInput_h

class DigitalInput
{
public:
    DigitalInput(uint8_t _pin);
    DigitalInput(uint8_t _pin, uint8_t _mode);
    boolean read();

protected:
    uint8_t pin;
};

#endif
