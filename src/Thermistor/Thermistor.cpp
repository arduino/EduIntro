#include "Thermistor.h"
#include "EduIntro.h"

Thermistor::Thermistor(uint8_t _pin) : AnalogInput(_pin) {}

float Thermistor::readCelsius()
{
	float Rthermistor = Rb * (ADCres / Thermistor::read() - 1);
	float _temperatureC = Beta / (log( Rthermistor * Ginf )) ;

	return _temperatureC - Kelvin;
}

float Thermistor::readFahrenheit()
{
	float _temperatureF = (Thermistor::readCelsius() * 9.0)/ 5.0 + 32.0; ;

	return _temperatureF;
}
