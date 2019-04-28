#include "Arduino.h"

#ifndef AnalogInput2_h
#define AnalogInput2_h

class AnalogInput2
{
public:
    AnalogInput2(uint8_t _pinX, uint8_t _pinY);
    AnalogInput2(uint8_t _pinX, uint8_t _pinY, uint8_t _pinZ);
    int readX();
    int readY();
    int readZ();

protected:
    uint8_t pinX, pinY, pinZ;
};

#endif
