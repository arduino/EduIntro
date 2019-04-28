#include <Arduino.h>
#include "../Generic/Output.h"

#ifndef LED_h
#define LED_h

class Led : public Output
{
	public:
        Led(uint8_t _pin);
        inline void brightness(int value) { write(value); }
};

#endif
