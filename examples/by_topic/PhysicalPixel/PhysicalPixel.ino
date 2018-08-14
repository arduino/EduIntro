/*
Physical Pixel

An example of using the Arduino board to receive data from the computer. In
this case, the Arduino boards turns on an LED when it receives the character
'H', and turns off the LED when it receives the character 'L'.

The data can be sent from the Arduino Serial Monitor, or another program like
Processing (see code below), Flash (via a serial-net proxy), PD, or Max/MSP.

The circuit:
- LED connected from digital pin 13 to ground

 created in Aug 2018 by D. Cuartielles
 based on work by D. Mellis (2006), T. Igoe and S. Fitzgerald (2011)

 This example code is in the public domain.
 */

#include <EduIntro.h>

Led led(D13);

int incomingByte;    // a variable to read incoming serial data

void setup()
{
  Serial.begin(9600);
}


void loop() {
  // see if there's incoming serial data:
  if (Serial.available() > 0) {

    // read the oldest byte in the serial buffer:
    incomingByte = Serial.read();

    // if it's a capital H (ASCII 72), turn on the LED:
    if (incomingByte == 'H') {
      led.on();
    }
    // if it's an L (ASCII 76) turn off the LED:
    if (incomingByte == 'L') {
      led.off();
    }

    if (incomingByte == 'S') {
      Serial.println(led.state(), DEC);
    }
  }
}
