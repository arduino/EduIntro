/*
 Relay

 Turns on and off a Relay connected to D10, when pressing a
 Button attached to D7.

 This example code is in the public domain.

 created in Aug 2018 by D. Cuartielles
 based on work by F. Vanzati (2011) and M. Loglio (2013)

 This example code is in the public domain.
 */

// include the EduIntro library
#include <EduIntro.h>

Button btn(D7);    // creating the object 'button' on pin D7

Relay relay(D10);  // creating the object 'relay' on pin D10

void setup() {
  // nothing to add here
}

void loop()
{
  // check the switch state
  if(btn.readSwitch() == HIGH) {
    relay.on();
  }
  else{
    relay.off();
  }
}
