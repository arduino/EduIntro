#include "AnalogInput.h"
#include "EduIntro.h"

AnalogInput::AnalogInput(uint8_t _pin)
{
    pin = _pin;
}

int AnalogInput::read() {

    int val;

    #if USB_VID == 0x2341 && USB_PID == 0x803C
        val = Esplora.readTK(pin);
    #else
        val = analogRead(pin);
    #endif

    if (val > _oldVal)
    {
      _increasing = true;
      _decreasing = false;
    }

    if (val < _oldVal)
    {
      _increasing = false;
      _decreasing = true;
    }

    _oldVal = val;

    return val;
}

boolean AnalogInput::increasing() {
    AnalogInput::read();
    return _increasing;
}

boolean AnalogInput::decreasing() {
    AnalogInput::read();
    return _decreasing;
}
