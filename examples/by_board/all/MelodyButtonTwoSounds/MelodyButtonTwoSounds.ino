/*
  MelodyButtonTwoSounds

  Plays a song stored in an array, when pressing a button, a different one
  when releasing the button. You should connect a speaker to pin D10 and a
  button to pin D7. Melodies are stored in arrays ending with NULL

  created in Apr 2019 by D. Cuartielles

  This example code is in the public domain.
 */

// include the EduIntro library
#include <EduIntro.h>

// define the song as (note, duration) pairs
// note durations: 4 = quarter note, 8 = eighth note, etc.
// add the NULL to signify the end of the array
int melody1[] = { NOTE_C4, 4,
                 NOTE_G3, 8,
                 NOTE_G3, 8,
                 SILENCE, 4, NULL};

int melody2[] = { NOTE_D4, 4,
                 NOTE_C3, 8,
                 NOTE_F3, 8,
                 SILENCE, 4, NULL};

Button button(D7);// creating the object 'button' on pin D7

Piezo piezo(D10);// creating the object 'piezo' on pin D10

void setup() {
  //nothing here
}

void loop()
{
  // if the button was just pressed, play melody
  if (button.pressed()) {
    piezo.play (melody1);
  }
  if (button.released()) {
    piezo.play (melody2);
  }
}
