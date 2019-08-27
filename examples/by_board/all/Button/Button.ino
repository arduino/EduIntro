/*
  Button

  Changes the behavior between on and off an LED when pressing a Button.

  This example code is in the public domain.

  created in Aug 2018 by D. Cuartielles
  based on work by F. Vanzati (2011) and M. Loglio (2013)

  based on  http://www.arduino.cc/en/Tutorial/Button
 */

// include the EduIntro library
#include <EduIntro.h>

Button button(D7);	// creating the object 'button' on pin D7

Led led(D10);		// creating the object 'led' on pin D10


void setup() {
//nothing here
}

void loop()
{
  // check the switchState of the button
  // each time it is pressed, it toggles the LED
  // when LOW, light should go on
  if (button.readSwitch() == LOW) {
    led.on();
  }
  else {
    led.off();
  }
}
