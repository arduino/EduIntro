#include "LM35.h"
#include "EduIntro.h"

LM35::LM35(uint8_t _pin) : AnalogInput(_pin) {}

float LM35::readCelsius()
{
	float _temperatureC = LM35::read() * 5 / ADCres / Acc ;

	return _temperatureC;
}

float LM35::readFahrenheit()
{
	float _temperatureF = (LM35::readCelsius() * 9.0)/ 5.0 + 32.0; ;

	return _temperatureF;
}
