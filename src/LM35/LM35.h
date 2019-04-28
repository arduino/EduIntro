#include <Arduino.h>
#include "../Generic/AnalogInput.h"

#ifndef LM35_h
#define LM35_h

class LM35 : public AnalogInput
{
public:
    LM35(uint8_t _pin);
    float readCelsius();
    float readFahrenheit();

protected:
    constexpr static float ADCres = 1023.0;
    constexpr static float Acc = 0.01;			// Accuracy mV/C
};

#endif
