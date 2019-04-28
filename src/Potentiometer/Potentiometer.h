#include <Arduino.h>
#include "../Generic/AnalogInput.h"

#ifndef Potentiometer_h
#define Potentiometer_h

class Potentiometer: public AnalogInput
{
public:
    Potentiometer(uint8_t pin);
    int read();
    int readStep(int steps);

protected:
    int _minVal, _maxVal;
    int _mappedVal;
    int _steps;
};

#endif
