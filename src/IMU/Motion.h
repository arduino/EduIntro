#include <Arduino.h>
#include <Arduino_LSM6DS3.h>

#ifndef Motion_h
#define Motion_h

class Motion
{
  public:
      Motion();
      void begin();
      void read();
      float acc_x;
      float acc_y;
      float acc_z;
      float gyro_x;
      float gyro_y;
      float gyro_z;
};
#endif
