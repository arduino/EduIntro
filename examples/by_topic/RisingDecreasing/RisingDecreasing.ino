/*
Increasing & Decreasing

 this sketch shows how to use increasing() and
 decreasing() on analog inputs.

 increasing() returns HIGH when values are rising,
 decreasing() is HIGH when values are decreasing

 created in Aug 2018 by D. Cuartielles
 based on work by M. Loglio (2013)

 This example code is in the public domain.
 */

// include the EduIntro library
#include <EduIntro.h>

Thermistor therm(A0); // creating the object 'therm' on pin A0

void setup()
{
  // initialize serial communications at 9600 bps
  Serial.begin(9600);
}

void loop()
{
  if (therm.increasing()) Serial.println("increasing");
  if (therm.decreasing()) Serial.println("decreasing");
  delay(50);
}
