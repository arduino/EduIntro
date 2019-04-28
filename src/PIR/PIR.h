#include <Arduino.h>
#include "../Generic/DigitalInput.h"

#ifndef PIR_h
#define PIR_h

class PIR: public DigitalInput
{
	public:
    PIR(uint8_t _pin);
    PIR(uint8_t _pin, uint8_t _mode);
		boolean hadActivity();   // was it active since last reset?
    boolean resetActivity(); // reset activity variable
    boolean readSwitch();
    boolean activated();
		boolean active();
		boolean deactivated();

	protected:
		boolean _toggleState, _oldState;
		boolean _pressedState, _releasedState;
		boolean _heldState, _activityState;
        int _heldTime;
        int _millisMark;
        int _mode;

		void update();
};

#endif
