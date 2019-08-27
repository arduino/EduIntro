#include "Motion.h"

Motion::Motion(){
}
void Motion::begin(){
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
}

void Motion::read(){
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(Motion::acc_x,Motion::acc_y,Motion::acc_z);
  }
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(Motion::gyro_x,Motion::gyro_y,Motion::gyro_z);
  }
}
