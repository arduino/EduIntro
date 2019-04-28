#include "DHT11.h"
#include "EduIntro.h"

DHT11::DHT11(uint8_t _pin) : DigitalInput(_pin, INPUT)
{
  pin = _pin;
}

DHT11::ReadStatus DHT11::update() {
    uint8_t    buffer[RESPONSE_SIZE] = { 0 };
    uint8_t    bitIndex              = BYTE_MS_BIT;
    ReadStatus status                = OK;

    // Request sample
    pinMode(this->pin, OUTPUT);
    digitalWrite(this->pin, LOW);
    delay(START_SIGNAL_WAIT);

    // Wait for response
    digitalWrite(this->pin, HIGH);
    pinMode(this->pin, INPUT);
    delayMicroseconds(RESPONSE_WAIT);

    // Acknowledge or timeout
    // Response signal should first be low for 80us...
    if ((status = this->waitForPinChange(LOW)) != OK) {
        goto done;
    }

    // ... then be high for 80us ...
    if ((status = this->waitForPinChange(HIGH)) != OK) {
        goto done;
    }

    /*
     * ... then provide 5 bytes of data that include the integral part of the
     * humidity, the fractional part of the humidity, the integral part of the
     * temperature, the fractional part of the temperature, and a checksum
     * that is the sum of the integral parts of humidity and temperature.
     */
    for (size_t i = 0; i < BITS_IN(buffer); i++) {
        if ((status = this->waitForPinChange(LOW)) != OK) {
            goto done;
        }

        unsigned long highStart = micros();

        if ((status = this->waitForPinChange(HIGH)) != OK) {
            goto done;
        }

        // 26-28 us = 0, 50 us = 1.  40 us is a good threshold between 0 and 1
        if ((micros() - highStart) > ONE_THRESHOLD) {
            buffer[i / BITS_PER_BYTE] |= (1 << bitIndex);
        }

        // Decrement or reset bitIndex
        bitIndex = (bitIndex > 0) ? bitIndex - 1 : BYTE_MS_BIT;
    }

    // Check the checksum.  Only if it's good, record the new values.
     if (buffer[CHECKSUM_INDEX] == (  buffer[0] + buffer[1]
                                    + buffer[2] + buffer[3])) {
        this->humidity    = buffer[HUMIDITY_INDEX];
        this->temperatureC = buffer[TEMPERATURE_INDEX];
        this->temperatureF = (this->temperatureC * 9.0)/ 5.0 + 32.0; ;
    } else {
        status = ERROR_CHECKSUM;
    }

done:
    return status;
}
