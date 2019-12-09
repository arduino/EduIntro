#include <Arduino.h>
#include "../Generic/Output.h"
#include "pitches.h"

#ifndef Piezo_h
#define Piezo_h

class Piezo : public Output
{
	public:
        Piezo(uint8_t _pin);
	void noBeep();
        void beep(int _tone);
        void beep(int _tone, int _duration);
        void play(int melody[]);
        void play(int n, int melody[]);
  protected:
        int getMelodySize(int melody[]);
};

#endif
