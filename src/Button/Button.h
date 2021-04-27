#include <Arduino.h>
#include "../Generic/DigitalInput.h"

#ifndef Button_h
#define Button_h

#define PULL_DOWN 0
#define PULL_UP 1

class Button: public DigitalInput
{
	public:
		Button(uint8_t _pin);
		Button(uint8_t _pin, uint8_t pulltype);
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
				int _debounceTime;
				int _millisDebounceMark;
        int _pulltype;

		void update();
};

#endif
