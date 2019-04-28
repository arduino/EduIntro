#include "Button.h"
#include "EduIntro.h"

/*
   The button is considered to be using the chip's internal pull-up
   which means that by default, it should be HIGH; LOW when pressed
*/
Button::Button(uint8_t _pin) : DigitalInput(_pin, INPUT_PULLUP)
{
	_toggleState = false;
	_oldState = HIGH;
	_pressedState = false;
	_releasedState = false;
	_heldState = false;
  _heldTime = 500;
}

void Button::update() {
  boolean newState = Button::read();
  if (newState != _oldState) {
    // pressed?
    if (newState == LOW) {
      _pressedState = true;
    }
    else {
      _releasedState = true;
     _toggleState = !_toggleState;
    }

    _oldState = newState;
    delay(50); // XXX debouncing FIXME to avoid delay
  }

  else {

      int timeDiff = millis() - _millisMark;

      if(newState == LOW && _oldState == LOW && timeDiff > _heldTime) {
  		_heldState = true;
  	} else {
  		_heldState = false;
  	}
  }
}


boolean Button::readSwitch()
{
	Button::update();
	return _toggleState;
}

boolean Button::pressed()
{
	Button::update();

	if(_pressedState == true)
	{
    _millisMark = millis();
		_pressedState = false;
		return true;
	}
	else
		return false;
}

boolean Button::released()
{
	Button::update();

	if(_releasedState == true)
	{
		_releasedState = false;
		return true;
	}
	else
		return false;
}

boolean Button::held()
{
	Button::update();
	return _heldState;
}
