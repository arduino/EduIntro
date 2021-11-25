#include <Arduino.h>
#include "../Generic/Output.h"

#ifndef LED_h
#define LED_h

class Led : public Output
{
	public:
        Led(uint8_t _pin);
        Led(uint8_t _pin, uint8_t _logic);
        inline void brightness(int value) { write(value); }
};

#endif
