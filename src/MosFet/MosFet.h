#include <Arduino.h>
#include "../Generic/Output.h"

#ifndef MosFet_h
#define MosFet_h

class MosFet : public Output
{
	public:
		MosFet(uint8_t _pin);
};

#endif
