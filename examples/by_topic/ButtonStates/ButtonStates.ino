/*
  ButtonStates

  Test the different Button methods: pressed, released, held
  and getSwitch.

  This example code is in the public domain.

  created in Aug 2018 by D. Cuartielles
  based on work by F. Vanzati (2011) and M. Loglio (2013)
*/

#include <EduIntro.h>

Button btn(D7);

void setup()
{
  // we are going to use the serial communication as a
  // way to see on the PC what is happening on the Arduino
  Serial.begin(9600);
}

void loop()
{
  if(btn.pressed())
    Serial.println("pressed");
  if(btn.held())
    Serial.println("held");
  if(btn.released()) {
    Serial.println("released");
    Serial.print("switch: ");
    Serial.println(btn.readSwitch());
  }

  delay(50);
}
