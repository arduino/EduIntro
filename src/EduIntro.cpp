#include "EduIntro.h"

#if USB_VID == 0x2341 && USB_PID == 0x803C
#include <Esplora.h>
#endif

/*
-----------------------------------------------------------------------------
                                   Definitions
-----------------------------------------------------------------------------
*/

/* for DHT11 serialized input */

#define BITS_IN(object) (8 * sizeof((object)))

enum {
    /*
     * Time required to signal the DHT11 to switch from low power mode to
     * running mode.  18 ms is the minimal, add a few extra ms to be safe.
     */
    START_SIGNAL_WAIT = 20,

    /*
     * Once the start signal has been sent, we wait for a response.  The doc
     * says this should take 20-40 us, we wait 5 ms to be safe.
     */
    RESPONSE_WAIT =  30,

    /*
     * The time threshold between a 0 bit and a 1 bit in the response.  Times
     * greater than this (in ms) will be considered a 1; otherwise they'll be
     * considered a 0.
     */
    ONE_THRESHOLD = 40,

    /*
     * The number of bytes we expect from the sensor.  This consists of one
     * byte for the integral part of the humidity, one byte for the fractional
     * part of the humidity, one byte for the integral part of the temperature,
     * one byte for the fractional part of the temperature, and one byte for
     * a checksum.  The DHT11 doesn't capture the fractional parts of the
     * temperature and humidity, but it doesn't transmit data during those
     * times.
     */
    RESPONSE_SIZE =  5,

    /*
     * The number of bits in a bytes.
     */
    BITS_PER_BYTE =  8,

    /*
     * The 0-base most significant bit in a byte.
     */
    BYTE_MS_BIT =  7,

    /*
     * The index in the response where the humidity reading is stored.
     */
    HUMIDITY_INDEX =  0,

    /*
     * The index in the response where the temperature is stored.
     */
    TEMPERATURE_INDEX =  2,

    /*
     * The index in the response where the checksum is stored.
     */
    CHECKSUM_INDEX =  4,
};

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

/*      PIR      */
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

/* DHT 11 temperature sensor */

DHT11::DHT11(uint8_t _pin) : DigitalInput(_pin, INPUT)
{
  pin = _pin;
}

DHT11::ReadStatus DHT11::update() {
    uint8_t    buffer[RESPONSE_SIZE] = { 0 };
    uint8_t    bitIndex              = BYTE_MS_BIT;
    ReadStatus status                = OK;

    // Request sample
    pinMode(this->pin, OUTPUT);
    digitalWrite(this->pin, LOW);
    delay(START_SIGNAL_WAIT);

    // Wait for response
    digitalWrite(this->pin, HIGH);
    pinMode(this->pin, INPUT);
    delayMicroseconds(RESPONSE_WAIT);

    // Acknowledge or timeout
    // Response signal should first be low for 80us...
    if ((status = this->waitForPinChange(LOW)) != OK) {
        goto done;
    }

    // ... then be high for 80us ...
    if ((status = this->waitForPinChange(HIGH)) != OK) {
        goto done;
    }

    /*
     * ... then provide 5 bytes of data that include the integral part of the
     * humidity, the fractional part of the humidity, the integral part of the
     * temperature, the fractional part of the temperature, and a checksum
     * that is the sum of the integral parts of humidity and temperature.
     */
    for (size_t i = 0; i < BITS_IN(buffer); i++) {
        if ((status = this->waitForPinChange(LOW)) != OK) {
            goto done;
        }

        unsigned long highStart = micros();

        if ((status = this->waitForPinChange(HIGH)) != OK) {
            goto done;
        }

        // 26-28 us = 0, 50 us = 1.  40 us is a good threshold between 0 and 1
        if ((micros() - highStart) > ONE_THRESHOLD) {
            buffer[i / BITS_PER_BYTE] |= (1 << bitIndex);
        }

        // Decrement or reset bitIndex
        bitIndex = (bitIndex > 0) ? bitIndex - 1 : BYTE_MS_BIT;
    }

    // Check the checksum.  Only if it's good, record the new values.
     if (buffer[CHECKSUM_INDEX] == (  buffer[0] + buffer[1]
                                    + buffer[2] + buffer[3])) {
        this->humidity    = buffer[HUMIDITY_INDEX];
        this->temperatureC = buffer[TEMPERATURE_INDEX];
        this->temperatureF = (this->temperatureC * 9.0)/ 5.0 + 32.0; ;
    } else {
        status = ERROR_CHECKSUM;
    }

done:
    return status;
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

// Thermistor
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

// LM35
LM35::LM35(uint8_t _pin) : AnalogInput(_pin) {}

float LM35::readCelsius()
{
	float _temperatureC = LM35::read() * 5 / ADCres / Acc ;

	return _temperatureC;
}

float LM35::readFahrenheit()
{
	float _temperatureF = (LM35::readCelsius() * 9.0)/ 5.0 + 32.0; ;

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

int ServoMotor::write(uint8_t _value)
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
