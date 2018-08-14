#include "EduIntro.h"

#if USB_VID == 0x2341 && USB_PID == 0x803C
#include <Esplora.h>
#endif

/*
 -----------------------------------------------------------------------------
                                    Generals
 -----------------------------------------------------------------------------
*/

/*      Digital Input       */

DigitalInput::DigitalInput(uint8_t _pin)
{
    pin = _pin;
    pinMode(pin, INPUT);
}

DigitalInput::DigitalInput(uint8_t _pin, uint8_t _mode)
{
    pin = _pin;
    pinMode(pin, _mode);
}

boolean DigitalInput::read() {

    boolean val;

    #if USB_VID == 0x2341 && USB_PID == 0x803C
        int value = Esplora.readTK(pin);
        if (value < 128)
            val = 0;
        else
            val = 1;
    #else
        val = digitalRead(pin);
    #endif

    return val;
}


/*      Analog Input        */

AnalogInput::AnalogInput(uint8_t _pin)
{
    pin = _pin;
}

int AnalogInput::read() {

    int val;

    #if USB_VID == 0x2341 && USB_PID == 0x803C
        val = Esplora.readTK(pin);
    #else
        val = analogRead(pin);
    #endif

    if (val > _oldVal)
    {
      _increasing = true;
      _decreasing = false;
    }

    if (val < _oldVal)
    {
      _increasing = false;
      _decreasing = true;
    }

    _oldVal = val;

    return val;
}

boolean AnalogInput::increasing() {
    AnalogInput::read();
    return _increasing;
}

boolean AnalogInput::decreasing() {
    AnalogInput::read();
    return _decreasing;
}

/*      Analog Input with two connectors       */

AnalogInput2::AnalogInput2(uint8_t _pinX, uint8_t _pinY)
{
    pinX = _pinX;
    pinY = _pinY;
}

AnalogInput2::AnalogInput2(uint8_t _pinX, uint8_t _pinY, uint8_t _pinZ)
{
    pinX = _pinX;
    pinY = _pinY;
    pinZ = _pinZ;
}

int AnalogInput2::readX() {

    int val;

    #if USB_VID == 0x2341 && USB_PID == 0x803C
        val = Esplora.readTK(pinX);
    #else
        val = analogRead(pinX);
    #endif

    return val;
}

int AnalogInput2::readY() {

    int val;

    #if USB_VID == 0x2341 && USB_PID == 0x803C
        val = Esplora.readTK(pinY);
    #else
        val = analogRead(pinY);
    #endif

    return val;
}

int AnalogInput2::readZ() {

    int val;

    #if USB_VID == 0x2341 && USB_PID == 0x803C
        val = Esplora.readTK(pinZ);
    #else
        val = analogRead(pinZ);
    #endif

    return val;
}

/*      Output       */

Output::Output(uint8_t _pin)
{
  pin = _pin;
	_state = LOW;
	pinMode(pin, OUTPUT);
}

boolean Output::isPWM()
{
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

/*
 -----------------------------------------------------------------------------
                                Digital Inputs
 -----------------------------------------------------------------------------
 */

/*      Button      */
/*
   The button is considered to be using the chip's internal pull-up
   which means that by default, it should be HIGH; LOW when pressed
*/
Button::Button(uint8_t _pin) : DigitalInput(_pin, INPUT_PULLUP)
{
	_toggleState = HIGH;
	_oldState = HIGH;
	_pressedState = HIGH;
	_releasedState = HIGH;
	_heldState = HIGH;
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
    delay(50); // debouncing
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


/*
 -----------------------------------------------------------------------------
                                Analog Inputs
 -----------------------------------------------------------------------------
 */

/*      Potentiometer       */

Potentiometer::Potentiometer(uint8_t _pin) : AnalogInput(_pin)

{
	pin = _pin;
	_minVal = 1023;
	_maxVal = 0;
}

int Potentiometer::read()
{

    int val = AnalogInput::read();

	if (val < _minVal) {_minVal = val;}
	if (val > _maxVal) {_maxVal = val;}

	_mappedVal = map(val, _minVal, _maxVal, 0, 1023);
	_mappedVal = constrain(_mappedVal, 0, 1023);

	return _mappedVal;
}

int Potentiometer::readStep(int steps) {

	_steps = steps;

	int step  = floor(map(read(), 0, 1023, 0, _steps));

	return step;
}


/*      Light Sensor        */

LightSensor::LightSensor(uint8_t _pin) : AnalogInput(_pin){}

/*      Temperature Sensor       */

Thermistor::Thermistor(uint8_t _pin) : AnalogInput(_pin) {}

float Thermistor::readCelsius()
{
	float Rthermistor = Rb * (ADCres / Thermistor::read() - 1);
	float _temperatureC = Beta / (log( Rthermistor * Ginf )) ;

	return _temperatureC - Kelvin;
}

float Thermistor::readFahrenheit()
{
	float _temperatureF = (Thermistor::readCelsius() * 9.0)/ 5.0 + 32.0; ;

	return _temperatureF;
}

/*
-----------------------------------------------------------------------------
                                        Outputs
-----------------------------------------------------------------------------
*/

/* LED */

Led::Led(uint8_t _pin) : Output(_pin) {}


/* MosFet */

MosFet::MosFet(uint8_t _pin) : Output(_pin) {}


/* Relay */

Relay::Relay(uint8_t _pin) : Output(_pin) {}

/* ServoMotor */

ServoMotor::ServoMotor(uint8_t _pin)
{
  Servo _servo;
  _servo.attach(_pin);
}

ServoMotor::write(uint8_t _value)
{
  _servo.write(_value);
}

/* Piezo */

Piezo::Piezo(uint8_t _pin) : Output(_pin) {}

void Piezo::beep(int _tone)
{
  if (_tone > SILENCE)
    tone(pin, _tone);
}

void Piezo::beep(int _tone, int _duration)
{
  if (_tone > SILENCE)
    tone(pin, _tone, _duration);
}

void Piezo::play(int melody[])
{
  //size_t n = sizeof(melody)/sizeof(melody[0]);
  int n = getMelodySize(melody);
  for (int i = 0; i < n; i+=2) {
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / melody[i+1];
    beep(melody[i], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
  }
  noTone(pin);
}

void Piezo::play(int n, int melody[])
{
  for (int i = 0; i < n; i+=2) {
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / melody[i+1];
    beep(melody[i], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
  }
  noTone(pin);
}

int Piezo::getMelodySize(int melody[])
{
  int count = 0;
  while (melody[count] != NULL)
    count++;
  return count;
}
