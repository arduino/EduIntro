#include "Piezo.h"
#include "EduIntro.h"

Piezo::Piezo(uint8_t _pin) : Output(_pin) {}

void Piezo::noBeep()
{
  noTone(pin);
}

void Piezo::beep(int _tone)
{
  if (_tone > SILENCE)
    tone(pin, _tone);
  else
    noTone(pin);
}

void Piezo::beep(int _tone, int _duration)
{
  if (_tone > SILENCE)
    tone(pin, _tone, _duration);
  else
    noTone(pin);
}

void Piezo::play(int melody[])
{
  //size_t n = sizeof(melody)/sizeof(melody[0]);
  int n = getMelodySize(melody);
  for (int i = 0; i < n; i+=2) {
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / melody[i+1];
    beep(melody[i], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
  }
  noTone(pin);
}

void Piezo::play(int n, int melody[])
{
  for (int i = 0; i < n; i+=2) {
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / melody[i+1];
    beep(melody[i], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
  }
  noTone(pin);
}

int Piezo::getMelodySize(int melody[])
{
  int count = 0;
  while (melody[count] != NULL)
    count++;
  return count;
}
