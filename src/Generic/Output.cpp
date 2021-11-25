#include "Output.h"
#include "EduIntro.h"

Output::Output(uint8_t _pin)
{
    pin = _pin;
	_state = LOW;
	pinMode(pin, OUTPUT);
}

Output::Output(uint8_t _pin, uint8_t _logic)
{
    pin = _pin;
    logic = _logic;
	_state = LOW;
	pinMode(pin, OUTPUT);
}

boolean Output::isPWM()
{
  //XXX this is just for the UNO board, needs fix
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)

//Code in here will only be compiled if an Arduino Uno (or older) is used.
  if (pin == D11 || pin == D10 || pin == D9 || pin == D6 || pin == D5 || pin == D3)
    return true;

#endif

#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega16U4__)

//Code in here will only be compiled if an Arduino Leonardo is used.
  if (pin == D13 || pin == D11 || pin == D10 || pin == D9 || pin == D6 || pin == D5 || pin == D3)
    return true;

#endif

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)

//Code in here will only be compiled if an Arduino Mega is used.
  if (pin == D13 || pin == D12  || pin == D11 || pin == D10 || pin == D9 || pin == D8  || pin == D7 || pin == D6 || pin == D5  || pin == D4 || pin == D3 || pin == D2 || pin == D1 || pin == D0)
    return true;

#endif

#if defined(ARDUINO_ARCH_SAMD)

//Code in here will only be compiled if an Arduino MKR and Nano IoT is used.
  if (pin == D19 || pin == D18  || pin == D12 || pin == D10 || pin == D8  || pin == D7 || pin == D6 || pin == D5  || pin == D4 || pin == D3 || pin == D2 || pin == D1 || pin == D0)
    return true;

#endif

#if defined(ARDUINO_ARCH_MBED)

//Code in here will only be compiled if an Arduino Nano BLE is used.
  if (pin == D21 || pin == D20 || pin == D19 || pin == D18 || pin == D17 || pin == D16 || pin == D15 || pin == D14 || pin == D13 || pin == D12  || pin == D11 || pin == D10 || pin == D9 || pin == D8  || pin == D7 || pin == D6 || pin == D5  || pin == D4 || pin == D3 || pin == D2 || pin == D1 || pin == D0)
    return true;

#endif

  return false;
}

void Output::write(int value)
{
  if (isPWM())
    if( value <= ANALOG_MAX && value >= 0 )
        analogWrite(pin, value * 0.25); // make sure the value is constrained between 0..255
    else
        return;
  else
    if ( value > ANALOG_MAX * 0.5 )
      digitalWrite(pin, HIGH);
    else
      digitalWrite(pin, LOW);
}

void Output::on() {
    if (logic == NORMAL) {
        write(1023);
        _state = HIGH;
    } else {
        write(0);
        _state = LOW;
    }
}

void Output::off() {
    if (logic == NORMAL) {
        write(0);
        _state = LOW;
    } else {
        write(1023);
        _state = HIGH;
    }
}


void Output::blink(int del)
{
    on();
    delay(del);
    off();
    delay(del);
}

void Output::blink(int del1, int del2)
{
    on();
    delay(del1);
    off();
    delay(del2);
}
