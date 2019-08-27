/*
Thermistor hooked up on pin A0.

Three values are displayed on the Serial Monitor every second:
- the value between 0 and 1023 that represent the Analog Input reading
- the temperature expressed in Celsius degrees
- the temperature expressed in Fahrenheit dedegrees

created in Aug 2018 by D. Cuartielles
based on work by F. Vanzati (2011) and M. Loglio (2013)

This example code is in the public domain.
*/

// include the EduIntro library
#include <EduIntro.h>

Thermistor therm(A0);  // creating the object 'therm' on pin A0

float C, F;  // temperature readings are returned in float format

void setup()
{
  // initialize serial communications at 9600 bps
  Serial.begin(9600);
}

void loop()
{
  C = therm.readCelsius();     	// Reading the temperature in Celsius degrees and store in the C variable
  F = therm.readFahrenheit();  	// Reading the temperature in Fahrenheit degrees and store in the F variable

  // Print the collected data in a row on the Serial Monitor
  Serial.print("Analog reading: ");	// Reading the analog value from the thermistor
  Serial.print(therm.read());
  Serial.print("\tC: ");
  Serial.print(C);
  Serial.print("\tF: ");
  Serial.println(F);

  delay(1000);                // Wait one second before get another temperature reading
}
