# Education Introduction Library - a.k.a. EduIntro

## Description

Arduino library for short introduction training workshops run by Arduino Education. This library is originally made for TinkerKit. It simplifies the use of sensors and actuators when connected to an Arduino board. The goal is to plan and conduct a simple one or two hours of training workshop where users will still have the opportunity to model meaningful interactions using discrete electronic components. It consists of already implemented basic functions for electronic components. In order to use its functions, it only requires to import this library and then call its functions.

## Installation

### First Method

1. In the Arduino IDE, navigate to Sketch > Include Library > Manage Libraries
1. Then the Library Manager will open and you will find a list of libraries that are already installed or ready for installation.
1. Then search for EduIntro using the search bar.
1. Click on the text area and then select the specific version and install it.

### Second Method

1. Navigate to the Releases page.
1. Download the latest release.
1. Extract the zip file
1. In the Arduino IDE, navigate to Sketch > Include Library > Add .ZIP Library

## Features

- ### Self contained

    EduIntro doesn’t depend on any library.

- ### Easy to use

    It is simple, basic and very easy to understand. The user only needs to import the library in his code and start using its functions.

- ### Complete package for small workshops

    Basic functions of discrete electronic components have already been implemented in this library. For a small one or two hours workshop, the user does not have to implement all the basic functions for the electronic component from scratch.

- ### Function calls

    Basic functions of the electronic components have been implemented in this library. There's no need to re-implement these basic functions from scratch. The user simply has to import the library in the project and can use any of its functions by just calling it.

- ### Intuitive syntax

    EduIntro has a simple and intuitive syntax to handle variables and functions.

- ### Give back

    EduIntro is free for everyone. Everyone can download and use it in their projects, assignments or anywhere for free.

## Components and functions

- ### Button

  - readSwitch()
  - pressed()
  - released()
  - held()
  - *Note: construct a button with Button NAME(PIN) or Button NAME(PIN,PULL_UP | PULL_DOWN), by default buttons are considered to use internal pull-ups* 

- ### DHT11

  - update()
  - readCelsius()
  - readFahrenheit()
  - readHumidity()

- ### Generic

  - ### For analog inputs

    - readX()
    - readY()
    - readZ()
    - read()
    - increasing()
    - decreasing()

  - ### For digital inputs

    - read()

  - ### For outputs (this extends to LEDs)

    - isPWM()
    - write()
    - on()
    - off()
    - blink()
    - state()
  - *Note: construct an output with e.g. Led NAME(PIN) or Led NAME(PIN,NORMAL | INVERTED), this helps with common cathode LEDs* 

- ### IMU

  - begin()
  - readAcceleration()
  - readGyroscope()
  - read()

- ### LED (besides all of the output functions)

  - brightness()

- ### LM35

  - readCelsius()
  - readFahrenheit()

- ### PIR

  - update()
  - hadActivity()
  - resetActivity()
  - readSwitch()
  - activated()
  - deactivated()
  - active()

- ### Piezo

  - beep()
  - noBeep()
  - play()
  - getMelodySize()

- ### Potentiometer

  - read()
  - readRange()
  - readStep()

- ### ServoMotor

  - write()

- ### Thermistor

  - readCelsius()
  - readFahrenheit()

- ### WiFiComm

  - init()
  - getSSID()
  - getIP()
  - getStatus()
  - getClient()

## Examples

There are many examples implemented in this library. Below are shown some of the examples.

  - ### Blink
    Turns on an LED on for one second, then off for one second, repeatedly

``` C++
#include <EduIntro.h>

Led led(D10);

void loop()
{
  led.on();
  delay(1000);
  led.off();
  delay(1000);
}
```

  - ### Button
    Changes the behavior between on and off an LED when pressing a button.

``` C++
#include <EduIntro.h>

Button button(D7);
Led led(D10);

void loop()
{
  if (button.readSwitch() == LOW) {
    led.on();
  }
  else {
    led.off();
  }
}
```

## Versions

### v0.0.16 (Current stable version)

#### November, 2021

* Fixed an issue with the Potentiometer class in mbed (Nano 33 BLE Sense)
* Added readRange() method for the Potentiometer
* Added inverted logic for outputs and the constructor to have e.g. *Led led(PIN, NORMAL | INVERTED)* 

### v0.0.13 

#### April, 2021

* Eliminated delays in button handling
* Added second constructor for Button, choose pull_up or down

### v0.0.12 

#### December 16, 2019

* Added library dependencies

### v0.0.11

#### December 9, 2019

* Added Nano Every by separating the two possible MEGAAVR boards (Nano Every + Uno WiFi rev2).
* Included a noBeep() function
* Added the new README with basic API description

### v0.0.10

#### August 28, 2019

The previous release included a non-functional WiFiComm file. It has been revised and made beautification in some of the code. It has been made sure that the Classic boards work fine as it got broken in the previous release.

### v0.0.9

#### August 27, 2019

Added support for the WiFi REV2 board and fixed the incompatibilities with servo and piezo.

### v0.0.8

#### May 01, 2019

All classes were separated to allow adding new classes by simply copy-pasting and modifying template examples.

### v0.0.7

#### April 17, 2019

General bug fixing: servo library not-two-servos fixed, added a new two-melodies example, fixed the button-pressed-by-default bug. Thanks to D. Spikol for bug catching and S. Mistry for reminding me that C++ inheritance is not always doing the things you expect.

### v0.0.6

#### February 10, 2019

For a course at Aalborg University, CPH, we added the humidity and temperature sensor DHT11, the LM35 temperature sensor, a PIR sensor, and a couple more examples to the courseware.

### v0.0.5

#### January 27, 2019

Sabas came all the way from Mexico to Malmo and made a fresh pull request. Now the library works with MKR boards!

### v0.0.4

#### January 25, 2019

See possible results of the workshop [here](https://photos.app.goo.gl/G9B4KmBHX7FQGdYNA)

## Contributing

If you want to contribute to this project:

- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell others about this library
- Contribute new protocols

Please read [CONTRIBUTING.md](https://github.com/arduino/EduIntro/blob/master/CONTRIBUTING.md) for details on our code of conduct, and the process for submitting pull requests to us.

## Credits

The Library created and maintained by D. Cuartielles, Malmo, 2018 - 2019
WiFi REV2 compatibility by C. Rodriguez (IMU + WiFi), and D. Cuartielles (servo), Malmo, 2019
MKR compatibility by A. Sabas, Malmo, 2019

Based on previous work by:

- D. Mellis, Milano, 2006
- T. Igoe, New York, 2008 - 2010
- S. Fitzgerald, New York, 2010
- D. Gomba, Torino, 2010
- F. Vanzati, Torino, 2011
- M. Loglio, London, 2013
- G. Hadjikyriacou (DHT11 lib originator), ??
- SimKard (DHT11), 2010
- R. Tillaart (DHT11), 2011 - 2013
- A. Dalton (DHT11), 2013
- [Arduino community](https://www.arduino.cc)

## Current stable version

**number:** v0.0.16

**codename:** ananas

## License

This library is licensed under [GPLv3](https://www.gnu.org/licenses/quick-guide-gplv3.html).
