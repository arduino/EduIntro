#include "Output.h"
#include "EduIntro.h"

Output::Output(uint8_t _pin)
{
  pin = _pin;
	_state = LOW;
	pinMode(pin, OUTPUT);
}

boolean Output::isPWM()
{
  //XXX this is just for the UNO board, needs fix
  if (pin == D11 || pin == D10 || pin == D9 || pin == D6 || pin == D5 || pin == D3)
    return true;
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
    write(1023);
    _state = HIGH;
}

void Output::off() {
    write(0);
    _state = LOW;
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
