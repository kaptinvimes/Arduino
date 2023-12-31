/*
 *  Explanation: This sketch shows how to use the most important
 *  features of the 4-20mA current loop board in Arduino. This
 *  standard is used to transmit information of sensor over long
 *  distances. Arduino uses analog inputs for reading the sensor
 *  values.
 *
 *  Copyright (C) 2014 Libelium Comunicaciones Distribuidas S.L.
 *  http://www.libelium.com
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Version:          0.1
 *  Design:           David Gascon
 *  Implementation:   Ahmad Saad
 */

// Include this library for using current loop functions.
#include <currentLoop.h>

#define CHANNEL CHANNEL1

void setup()
{
  
  // Switch ON the 24V DC-DC converter
  sensorBoard.OFF();

  // Inits the Serial for viewing data in the serial monitor
  Serial.begin(9600);
  delay(100);
//  Serial.println("Arduino 4-20mA board switched ON...");
}


void loop()
{
  // Get the sensor value in int format (0-1023)
//  int value = sensorBoard.readChannel(CHANNEL);
//  Serial.print("Int value read from channel 1 : ");
//  Serial.println(value);

  // Get the sensor value as a voltage in Volts
//  float voltage = sensorBoard.readVoltage(CHANNEL,float -0.062);
//  Serial.print("Voltage value rad from channel 1 : ");
//  Serial.print(voltage);
//  Serial.println("V");

  // Get the sensor value as a current in mA
  float current = sensorBoard.readCurrent(CHANNEL,float(0.062));

//  Serial.print("Current value read from channel 1 : ");
  Serial.print(current);
 // Serial.println("mA");


//  Serial.println("***************************************");
Serial.print("\r\n");

  delay(5000);
}




