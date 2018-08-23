/*
  Makes a Servo change angle when pressing a Button.

  This example code is in the public domain.

  created in Aug 2018 by D. Cuartielles

  based on  http://www.arduino.cc/en/Tutorial/Button
 */

// include the EduIntro library
#include <EduIntro.h>

Button button(D7);	// creating the object 'button' on pin D7

ServoMotor servo(D10);		// creating the object 'servo' on pin D10


void setup() {
//nothing here
}

void loop()
{
  // check the switchState of the button
  // each time it is pressed, it toggles the servo's position
  // when LOW, light should go on
  if (button.readSwitch() == LOW) {
    servo.write(90);
  }
  else {
    servo.write(0);
  }
}
