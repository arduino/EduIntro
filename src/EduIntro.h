/*
 *      EduIntro Library v0.1
 *
 *
 *
 *      created on Aug 2018
 *      by D. Cuartielles
 *      based on work from Dec 2011 by F. Vanzati
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

#include "Arduino.h"

#ifndef EduIntro_h
#define EduIntro_h

/*
-----------------------------------------------------------------------------
                                Generic Classes
-----------------------------------------------------------------------------
*/

#include "Generic/DigitalInput.h"
#include "Generic/AnalogInput.h"
#include "Generic/AnalogInput2.h"

/*
 -----------------------------------------------------------------------------
                                Digital Inputs
 -----------------------------------------------------------------------------
*/

/*      Button      */

#include "Button/Button.h"

/*      PIR      */

#include "PIR/PIR.h"

/*      DHT11      */

#include "DHT11/DHT11.h"

/*
 -----------------------------------------------------------------------------
                                Analog Inputs
 -----------------------------------------------------------------------------
 */

/*      Potentiometer        */

#include "Potentiometer/Potentiometer.h"

/*      Light Sensor        */

#include "LightSensor/LightSensor.h"

/*      Temperature Sensor        */

#include "Thermistor/Thermistor.h"
#include "LM35/LM35.h"

/*
 -----------------------------------------------------------------------------
                                    Outputs
 -----------------------------------------------------------------------------
 */

/*      LED     */

#include "LED/LED.h"

/*      Piezo     */

#include "Piezo/Piezo.h"

/*      MosFet      */

#include "MosFet/MosFet.h"

/*      Relay       */

#include "Relay/Relay.h"

/*      Servo       */

#include "ServoMotor/ServoMotor.h"

/*      Arduino uno wifi Rev2 accelerometer       */

#include "IMU/Motion.h"

/*      Arduino uno wifi Rev2 WIFININA       */

#include "WiFiComm/WiFiComm.h"

/*
 -----------------------------------------------------------------------------
                                    Constants
 -----------------------------------------------------------------------------
 */

/*        Minimum Analog In/Out that each platform have     */

#define D13 13
#define D12 12
#define D11 11
#define D10 10
#define D9 9
#define D8 8
#define D7 7
#define D6 6
#define D5 5
#define D4 4
#define D3 3
#define D2 2
#define D1 1
#define D0 0

#define ANALOG_MAX 1023

#endif
