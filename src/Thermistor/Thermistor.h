#include <Arduino.h>
#include "../Generic/AnalogInput.h"

#ifndef Thermistor_h
#define Thermistor_h

class Thermistor : public AnalogInput
{
public:
    Thermistor(uint8_t _pin);
    float readCelsius();
    float readFahrenheit();

protected:
    constexpr static float ADCres = 1023.0;
    constexpr static int Beta = 3950;			// Beta parameter
    constexpr static float Kelvin = 273.15;	// 0°C = 273.15 K
    constexpr static int Rb = 10000;			// 10 kOhm
    constexpr static float Ginf = 120.6685;	// Ginf = 1/Rinf
    // Rinf = R0*e^(-Beta/T0) = 4700*e^(-3950/298.15)
};

#endif
