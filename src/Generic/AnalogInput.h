#include "Arduino.h"

#ifndef AnalogInput_h
#define AnalogInput_h

class AnalogInput
{
public:
    AnalogInput(uint8_t _pin);
    int read();
    boolean increasing();
    boolean decreasing();

protected:
    uint8_t pin;
    int _oldVal;
    boolean _increasing;
    boolean _decreasing;
};

#endif
