#include "Motion.h"

//#if defined(ARDUINO_ARCH_MEGAAVR)
#if defined(AVR_UNO_WIFI_REV2)

Motion::Motion(){
}

int Motion::begin(){
    return IMU.begin();
}

int Motion::readAcceleration() {
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(Motion::acc_x,Motion::acc_y,Motion::acc_z);
    return 1;
  }
  return 0;
}

int Motion::readGyroscope() {
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(Motion::gyro_x,Motion::gyro_y,Motion::gyro_z);
    return 1;
  } 
  return 0;
}

int Motion::read() {
  if(Motion::readAcceleration() && Motion::readGyroscope())
    return 1;
  return 0;
}

#endif
