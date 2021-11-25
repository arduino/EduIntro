#include "Potentiometer.h"
#include "EduIntro.h"

Potentiometer::Potentiometer(uint8_t _pin) : AnalogInput(_pin)
{
	pin = _pin;
	_minVal = 1023;
	_maxVal = 0;
}

/*
	The potentiometer readRange function includes a filter to determine
        the potentiometer range interactively. This allows for the use of sensors
	which are not getting the full range 0..1023
*/
int Potentiometer::readRange()
{

    int val = AnalogInput::read();

	if (val < _minVal) {_minVal = val;}
	if (val > _maxVal) {_maxVal = val;}

	float __mappedVal = 0;
	if (_minVal != _maxVal) 
	{
		__mappedVal = map(val, _minVal, _maxVal, 0, 1023);
		_mappedVal = constrain(__mappedVal, 0, 1023);
	} 

	return _mappedVal;
}

int Potentiometer::readStep(int steps) {

	_steps = steps;

	int step  = floor(map(AnalogInput::read(), 0, 1023, 0, _steps));

	return step;
}
