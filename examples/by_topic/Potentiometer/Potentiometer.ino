/*
 Read the value of a Potentiometer connected to A0,
 then uses the results to write the brightness on
 an LED connected on D10. Also prints the values
 on the serial monitor.

 created in Aug 2018 by D. Cuartielles
 based on work by T. Igoe (2008, 2010), D. Gomba (2010), F. Vanzati (2011) and M. Loglio (2013)

 This example code is in the public domain.
 */

#include <EduIntro.h>

Potentiometer pot(A0);  // creating the object 'pot' on pin A0

Led led(D10);		// creating the object 'led' on pin D10

int brightnessVal = 0;  // value read from the pot

void setup() {
  // initialize serial communications at 9600 bps
  Serial.begin(9600);
}

void loop() {
  // read the potentiometer's value:
  brightnessVal = pot.read();

  // set the led brightness
  led.brightness(brightnessVal);

  // print the results to the serial monitor:
  Serial.print("brightness = " );
  Serial.println(brightnessVal);


  // wait 10 milliseconds before the next loop
  delay(10);
}
