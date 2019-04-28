#include "AnalogInput2.h"
#include "EduIntro.h"

#if USB_VID == 0x2341 && USB_PID == 0x803C
#include <Esplora.h>
#endif

AnalogInput2::AnalogInput2(uint8_t _pinX, uint8_t _pinY)
{
    pinX = _pinX;
    pinY = _pinY;
}

AnalogInput2::AnalogInput2(uint8_t _pinX, uint8_t _pinY, uint8_t _pinZ)
{
    pinX = _pinX;
    pinY = _pinY;
    pinZ = _pinZ;
}

int AnalogInput2::readX() {

    int val;

    #if USB_VID == 0x2341 && USB_PID == 0x803C
        val = Esplora.readTK(pinX);
    #else
        val = analogRead(pinX);
    #endif

    return val;
}

int AnalogInput2::readY() {

    int val;

    #if USB_VID == 0x2341 && USB_PID == 0x803C
        val = Esplora.readTK(pinY);
    #else
        val = analogRead(pinY);
    #endif

    return val;
}

int AnalogInput2::readZ() {

    int val;

    #if USB_VID == 0x2341 && USB_PID == 0x803C
        val = Esplora.readTK(pinZ);
    #else
        val = analogRead(pinZ);
    #endif

    return val;
}
