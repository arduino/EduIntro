/*
  Inertia Meassurement Unit (IMU) A.K.A. Motion

  IMPORTANT: This example is using the Arduino_LSM6DS3 library in the backed. You
             need to have it installed before testing this code. If you are on
             Arduino Create (the online IDE) the library will already be there.

  This example uses the embeded IMU unit in the Arduino UNO Wifi Rev2.

  The IMU captures values from the accelerometer and the gyroscope.
  These values can be accesable with:

  acc_x: Returns the X value of the accelerometer.
  acc_y: Returns the Y value of the accelerometer.
  acc_z: Returns the Z value of the accelerometer.
  gyro_x: Returns the X value of the gyroscope.
  gyro_y: Returns the Y value of the gyroscope.
  gyro_z: Returns the Z value of the gyroscope.

  This example code is in the public domain.

  created in Aug 2019 by C. Rodriguez
  based on work by D. Cuartielles (2019), F. Vanzati (2011) and M. Loglio (2013)
*/

// include the EduIntro library
#include <EduIntro.h>

Motion imu; //Create the object to access the IMU unit

void setup()
{
  // initialize serial communications at 9600 bps
  Serial.begin(9600);

  // initialize the IMU, if failed, stay here
  if (!imu.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
}

void loop()
{
  // read all data from the IMU and store it in local variables
  if (imu.read()) {

    // print the collected data in a row on the Serial Monitor
    // or use the Serial Plotter to better understand the values
    Serial.print(imu.acc_x);
    Serial.print('\t');
    Serial.print(imu.acc_y);
    Serial.print('\t');
    Serial.println(imu.acc_z);
  }
}
