#include "Potentiometer.h"
#include "EduIntro.h"

Potentiometer::Potentiometer(uint8_t _pin) : AnalogInput(_pin)

{
	pin = _pin;
	_minVal = 1023;
	_maxVal = 0;
}

int Potentiometer::read()
{

    int val = AnalogInput::read();

	if (val < _minVal) {_minVal = val;}
	if (val > _maxVal) {_maxVal = val;}

	_mappedVal = map(val, _minVal, _maxVal, 0, 1023);
	_mappedVal = constrain(_mappedVal, 0, 1023);

	return _mappedVal;
}

int Potentiometer::readStep(int steps) {

	_steps = steps;

	int step  = floor(map(read(), 0, 1023, 0, _steps));

	return step;
}
