/*
Write a signal to a MosFet transistor using a Potentiometer.

created in Aug 2018 by D. Cuartielles
based on work by M. Loglio (2013)

This example code is in the public domain.
*/

// include the EduIntro library
#include <EduIntro.h>

MosFet mos(D3);         //create the mos object on pin D3
Potentiometer pot(A0);  //create the pot object on pin A0

void setup() {
  //nothing here
}

void loop()
{
  int val = pot.read(); //assign to a "val" variable
                        //the potentiometer values

  mos.write(val);       //assign the values to the mosfet

  delay(10);            //rest for 10 milliseconds.
}
