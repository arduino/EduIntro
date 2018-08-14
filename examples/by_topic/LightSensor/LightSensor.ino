/*
 Read values from an LDR Analog Sensor connected to A0,
 then uses the result to set the brightness on an LED
 connected on D9. Also prints the values on the
 serial monitor.

 created in Aug 2018 by D. Cuartielles
 based on work by T. Igoe (2010), D. Gomba (2010), F. Vanzati (2011) and M. Loglio (2013)

 This example code is in the public domain.
 */

#include <EduIntro.h>

LightSensor ldr(A0);	//create the "ldr" object on pin A0

Led led(D10);		//create the "led" object on pin D10

void setup() {
  // initialize serial communications at 9600 bps
  Serial.begin(9600);
}

void loop() {
  // store the ldr values into a variable called brightnessVal
  int brightnessVal = ldr.read();

  // set the led brightness
  led.brightness(brightnessVal);

  //to have it at full brightness
  //when it's dark, uncomment this line:
  //led.brightness(1023 - brightnessVal);

  // print the results to the serial monitor:
  Serial.print("brightness = " );
  Serial.println(brightnessVal);


  // wait 10 milliseconds before the next loop
  delay(10);
}
