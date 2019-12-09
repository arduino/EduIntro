#include <Arduino.h>

//#if defined(ARDUINO_ARCH_MEGAAVR)
#if defined(AVR_UNO_WIFI_REV2)

#include <Arduino_LSM6DS3.h>

#ifndef Motion_h
#define Motion_h

class Motion
{
  public:
      Motion();
      int begin();
      int read();
      int readAcceleration();
      int readGyroscope();
      float acc_x;
      float acc_y;
      float acc_z;
      float gyro_x;
      float gyro_y;
      float gyro_z;
};
#endif

#endif
