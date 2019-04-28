#include <Arduino.h>
#include "../Generic/DigitalInput.h"

#ifndef DHT11_h
#define DHT11_h

/* for DHT11 serialized input */

#define BITS_IN(object) (8 * sizeof((object)))

enum {
    /*
     * Time required to signal the DHT11 to switch from low power mode to
     * running mode.  18 ms is the minimal, add a few extra ms to be safe.
     */
    START_SIGNAL_WAIT = 20,

    /*
     * Once the start signal has been sent, we wait for a response.  The doc
     * says this should take 20-40 us, we wait 5 ms to be safe.
     */
    RESPONSE_WAIT =  30,

    /*
     * The time threshold between a 0 bit and a 1 bit in the response.  Times
     * greater than this (in ms) will be considered a 1; otherwise they'll be
     * considered a 0.
     */
    ONE_THRESHOLD = 40,

    /*
     * The number of bytes we expect from the sensor.  This consists of one
     * byte for the integral part of the humidity, one byte for the fractional
     * part of the humidity, one byte for the integral part of the temperature,
     * one byte for the fractional part of the temperature, and one byte for
     * a checksum.  The DHT11 doesn't capture the fractional parts of the
     * temperature and humidity, but it doesn't transmit data during those
     * times.
     */
    RESPONSE_SIZE =  5,

    /*
     * The number of bits in a bytes.
     */
    BITS_PER_BYTE =  8,

    /*
     * The 0-base most significant bit in a byte.
     */
    BYTE_MS_BIT =  7,

    /*
     * The index in the response where the humidity reading is stored.
     */
    HUMIDITY_INDEX =  0,

    /*
     * The index in the response where the temperature is stored.
     */
    TEMPERATURE_INDEX =  2,

    /*
     * The index in the response where the checksum is stored.
     */
    CHECKSUM_INDEX =  4,
};

class DHT11 : public DigitalInput
{
public:
    //DHT11(uint8_t _pin): humidity(-1), temperatureC(-1), pin(_pin);
    DHT11(uint8_t _pin);
    // An enumeration modeling the read status of the sensor.
    enum ReadStatus {
        OK,
        ERROR_CHECKSUM,
        ERROR_TIMEOUT,
      };
    ReadStatus update();  // read the data and return status
    inline int readCelsius() const {
        return this->temperatureC;
      }
    inline float readFahrenheit() const {
        return this->temperatureF;
      }
    inline int readHumidity() const {
        return this->humidity;
      }

private:
    int pin;
    int humidity;
    int temperatureC;
    float temperatureF;
    enum {
      MAX_PIN_CHANGE_ITERATIONS = 10000, // timeout variable
    };
    inline ReadStatus waitForPinChange(const int oldValue,
                                       unsigned  maxIterations =
                                              MAX_PIN_CHANGE_ITERATIONS) const {
        while ((--maxIterations > 0) && (digitalRead(this->pin) == oldValue)) {
            // Just keep looping...
        }

        return (maxIterations > 0) ? OK : ERROR_TIMEOUT;
      }
};

#endif
