/*
  Makes a Continuous Servo change speed when turning a potentiometer.
  Prints the different motor states to the serial port.

  This example code is in the public domain.

  created in Feb 2019 by D. Cuartielles

  based on  https://www.arduino.cc/en/tutorial/knob
 */

// include the EduIntro library
#include <EduIntro.h>

Potentiometer pot(A0);  // creating the object 'pot' on pin A0

ServoMotor servo(D10);		// creating the object 'servo' on pin D10

int potVal = 0;   // value read from the pot
int angleVal = 0; // value of the angle to set the servo

void setup() {
  // initialize serial communications at 9600 bps
  Serial.begin(9600);
}

void loop()
{
  // read the potentiometer's value:
  potVal = pot.read();

  // map the data from the sensor (0..1023) to
  // one the servo can take (0..180)
  angleVal = map(potVal, 0, 1023, 0, 180);

  // set the led brightness
  servo.write(angleVal);

  // Signify it different events for the motor
  if (angleVal == 90)
    Serial.println("Motor Stop");
  if (angleVal <= 1)
    Serial.println("Motor Max clockwise");
  if (angleVal >= 179)
    Serial.println("Motor Max counter clockwise");

  // print the results to the serial monitor:
  Serial.print("angle = " );
  Serial.println(angleVal);


  // wait 100 milliseconds before the next loop
  delay(100);
}
