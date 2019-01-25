/*
  ButtonStates for Cardboard Keyboard

  This example code is in the public domain.

  created in Jan 2019 by D. Cuartielles
  based on work by F. Vanzati (2011) and M. Loglio (2013)
*/

#include <EduIntro.h>
#include <Keyboard.h>

// reconfigure these pins to be the ones where you plug your wires
byte btnPins[] = {D9, D10, D11, D12};

// which are the keys you will be using ... ?
byte key[] = {'a', 'd', KEY_UP_ARROW, ' '};

// array to control the buttons
Button btn[] = {
  Button(btnPins[0]),
  Button(btnPins[1]),
  Button(btnPins[2]),
  Button(btnPins[3]),
  };

void setup()
{
  // we are going to use the serial communication as a
  // way to see on the PC what is happening on the Arduino
  Serial.begin(9600);

  // initialize the keyboard controller
  Keyboard.begin();
}

void loop()
{
  for (int i; i < 4; i ++) {
    if (btn[i].pressed()) {
      Serial.print("pressed pin: "); Serial.println(btnPins[i]);
      Keyboard.press(key[i]);
    }
    if (btn[i].held())
      Serial.print("held pin: "); Serial.println(btnPins[i]);
    if (btn[i].released()) {
      Serial.print("released pin: "); Serial.println(btnPins[i]);
      Serial.print("switch pin "); Serial.print(btnPins[i]); Serial.print(": ");
      Serial.println(btn[i].readSwitch());
      Keyboard.release(key[i]);
    }
  }
}
