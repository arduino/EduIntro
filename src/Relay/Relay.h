#include <Arduino.h>
#include "../Generic/Output.h"

#ifndef Relay_h
#define Relay_h

class Relay : public Output
{
	public:
		Relay(uint8_t _pin);
};

#endif
