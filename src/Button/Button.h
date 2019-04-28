#include <Arduino.h>
#include "../Generic/DigitalInput.h"

#ifndef Button_h
#define Button_h

class Button: public DigitalInput
{
	public:
		Button(uint8_t _pin);
		boolean readSwitch();
		boolean pressed();
		boolean held();
		boolean released();

	protected:
		boolean _toggleState, _oldState;
		boolean _pressedState, _releasedState;
		boolean _heldState;
        int _heldTime;
        int _millisMark;

		void update();
};

#endif
