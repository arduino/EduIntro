/*
  PIRStates

  Test the different PIR methods: activated, deactivated, active,
  readSwitch, hadActivity, and resetActivity

  This example code is in the public domain.

  created in Feb 2019 by D. Cuartielles
  based on work by F. Vanzati (2011) and M. Loglio (2013)
*/

#include <EduIntro.h>

PIR pir(D7);

void setup()
{
  // we are going to use the serial communication as a
  // way to see on the PC what is happening on the Arduino
  Serial.begin(9600);
}

void loop()
{
  if(pir.activated())
    Serial.println("activited");
  if(pir.active())
    Serial.println("still active");
  if(pir.deactivated()) {
    Serial.println("deactivated");
    Serial.print("switch: ");
    Serial.println(pir.readSwitch());
  }
  if(!pir.activated() && pir.hadActivity()) {
    Serial.print("had activity: ");
    Serial.println(pir.hadActivity());
    pir.resetActivity();
  }

  delay(500);
}
