#include <Arduino.h>
#include "../Generic/AnalogInput.h"

#ifndef LightSensor_h
#define LightSensor_h

class LightSensor : public AnalogInput
{
    public:
        LightSensor(uint8_t _pin);
};

#endif
