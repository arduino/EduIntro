#include "LED.h"
#include "EduIntro.h"

Led::Led(uint8_t _pin) : Output(_pin) {}
Led::Led(uint8_t _pin, uint8_t _logic) : Output(_pin, _logic) {}
