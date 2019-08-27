/*
  Melody

  Plays a song stored in an array, repeatedly. You should connect
  a speaker to pin D10

  created in Aug 2018 by D. Cuartielles

  This example code is in the public domain.
 */

// include the EduIntro library
#include <EduIntro.h>

// define the song as (note, duration) pairs
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int melody[] = { NOTE_C4, 4,
                 NOTE_G3, 8,
                 NOTE_G3, 8,
                 NOTE_A3, 4,
                 NOTE_G3, 4,
                 SILENCE, 4,
                 NOTE_B3, 4,
                 NOTE_C4, 4 };

Piezo piezo(D10);	// creating the object 'piezo' on pin D10

void setup() {
//nothing here
}

void loop()
{
  piezo.play(melody); // play the song
  delay(1000);        // wait for a second
}
