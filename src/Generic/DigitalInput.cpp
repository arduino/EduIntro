#include "DigitalInput.h"
#include "EduIntro.h"

#if USB_VID == 0x2341 && USB_PID == 0x803C
#include <Esplora.h>
#endif

DigitalInput::DigitalInput(uint8_t _pin)
{
    pin = _pin;
    pinMode(pin, INPUT);
}

DigitalInput::DigitalInput(uint8_t _pin, uint8_t _mode)
{
    pin = _pin;
    pinMode(pin, _mode);
}

boolean DigitalInput::read() {

    boolean val;

    #if USB_VID == 0x2341 && USB_PID == 0x803C
        int value = Esplora.readTK(pin);
        if (value < 128)
            val = 0;
        else
            val = 1;
    #else
        val = digitalRead(pin);
    #endif

    return val;
}
