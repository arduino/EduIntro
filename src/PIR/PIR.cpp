#include "PIR.h"
#include "EduIntro.h"

/*
   The PIR could be in need of the internal pull-up or not
   therefore the need of two constructors. By default: no pull-up
*/
PIR::PIR(uint8_t _pin) : DigitalInput(_pin, INPUT)
{
	_toggleState = LOW;
	_oldState = LOW;
	_pressedState = LOW;
	_releasedState = LOW;
	_heldState = LOW;
  _heldTime = 500;
  _mode = INPUT;
}

PIR::PIR(uint8_t _pin, uint8_t _mod) : DigitalInput(_pin, _mod)
{
  if(_mode == INPUT_PULLUP) {
    _toggleState = HIGH;
  	_oldState = HIGH;
  	_pressedState = HIGH;
  	_releasedState = HIGH;
  	_heldState = HIGH;
  } else {
    _toggleState = LOW;
  	_oldState = LOW;
  	_pressedState = LOW;
  	_releasedState = LOW;
  	_heldState = LOW;
  }
  _heldTime = 500;
  _mode = _mod;
}

void PIR::update() {
  boolean newState = PIR::read();
  if (newState != _oldState) {
    _activityState = true; // there was some sort of activity
    // activated?
    if(_mode == INPUT_PULLUP) {
      if (newState == LOW) {
        _pressedState = true;
      }
      else {
        _releasedState = true;
       _toggleState = !_toggleState;
      }
    } else {
      if (newState == HIGH) {
        _pressedState = true;
      }
      else {
        _releasedState = true;
       _toggleState = !_toggleState;
      }
    }
    _oldState = newState;
    //delay(50); // debouncing is unlike in the button not needed, but this is up for testing
  }

  else {

    int timeDiff = millis() - _millisMark;

    if(_mode == INPUT_PULLUP) {
      if(newState == LOW && _oldState == LOW && timeDiff > _heldTime) {
  		    _heldState = true;
  	  } else {
  		    _heldState = false;
  	  }
    } else {
      if(newState == HIGH && _oldState == HIGH && timeDiff > _heldTime) {
  		    _heldState = true;
  	  } else {
  		    _heldState = false;
  	  }
    }
  }
}

boolean PIR::hadActivity() {
  return _activityState;
}

boolean PIR::resetActivity() {
  _activityState = false;
  return _activityState;
}

boolean PIR::readSwitch()
{
	PIR::update();
	return _toggleState;
}

boolean PIR::activated()
{
	PIR::update();

	if(_pressedState == true)
	{
    _millisMark = millis();
		_pressedState = false;
		return true;
	}
	else
		return false;
}

boolean PIR::deactivated()
{
	PIR::update();

	if(_releasedState == true)
	{
		_releasedState = false;
		return true;
	}
	else
		return false;
}

boolean PIR::active()
{
	PIR::update();
	return _heldState;
}
