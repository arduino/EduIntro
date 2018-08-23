/*
  Servo

  Makes a Servo change angle after some time.

  This example code is in the public domain.

  created in Aug 2018 by D. Cuartielles

  based on  http://www.arduino.cc/en/Tutorial/Button
 */

// include the EduIntro library
#include <EduIntro.h>

ServoMotor servo(D10);		// creating the object 'servo' on pin D10


void setup() {
//nothing here
}

void loop()
{
  servo.write(90);
  delay (1000);   // wait for a second
  servo.write(0);
  delay (1000);   // wait for a second
}
