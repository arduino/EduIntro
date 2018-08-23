/*
  Blink

  based on Blink, Arduino's "Hello World!"
  Turns on an LED on for one second, then off for one second, repeatedly.

  created in Aug 2018 by D. Cuartielles
  based on work by F. Vanzati (2011)

  This example code is in the public domain.
 */

// include the EduIntro library
#include <EduIntro.h>

Led led(D10);	// creating the object 'led' on pin D10

void setup() {
//nothing here
}

void loop()
{
  led.on();       // set the LED on
  delay(1000);    // wait for a second
  led.off();      // set the LED off
  delay(1000);    // wait for a second
}
