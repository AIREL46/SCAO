/*
   Copyright (c) 2015 Intel Corporation.  All rights reserved.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include <CurieBLE.h> //Déclaration de la librairie CurieBle


BLEPeripheral blePeripheral;  // BLE Peripheral Device (the board you're programming)
BLEService epoigneeService("19B10010-E8F2-537E-4F6C-D104768A1214"); // BLE e-poignee Service
float  u16_Tm      = 20;            //Initialisation de la Température en centième de °C

// BLE Rupteur Switch Characteristic - custom 128-bit UUID, read and writable by central
// Initialisation des variables Ble
BLEUnsignedIntCharacteristic TmCharacteristic("19B10014-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
const int ledPin = 13; // pin to use for the LED
int t(0);
int Tu(80);
int Ti(20);
void setup() {
  Serial.begin(9600);
  
  // set LED pin to output mode
  pinMode(ledPin, OUTPUT);

  // set advertised local name and service UUID:
  blePeripheral.setLocalName("e-poignee");
  blePeripheral.setAdvertisedServiceUuid(epoigneeService.uuid());

  // add service and characteristic:
  blePeripheral.addAttribute(epoigneeService);
    blePeripheral.addAttribute(TmCharacteristic);

  // set the initial value for the characeristic:
  TmCharacteristic.setValue(u16_Tm);

  // begin advertising BLE service:
  blePeripheral.begin();

  Serial.println("BLE LED Peripheral");
  
}

void loop() {
  // listen for BLE peripherals to connect:
  BLECentral central = blePeripheral.central();
  delay (1000);
  t=t+1;
  //u16_Tm=u16_Tm+1;
  u16_Tm=(Ti+(Tu-Ti)*(1-exp(-t/20)));
  //TmCharacteristic.setValue(u16_Tm);
  Serial.print (t);
  Serial.print (" - ");
  Serial.println (u16_Tm);

  // if a central is connected to peripheral:
  if (central) 
  {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());

    // while the central is still connected to peripheral:
    while (central.connected()) 
    {
      // if the remote device wrote to the characteristic,
      // use the value to control the LED:
      
      if (TmCharacteristic.written()) 
      {
        u16_Tm = TmCharacteristic.value();
        digitalWrite(ledPin, HIGH);
      }
      else
      {digitalWrite(ledPin, LOW);
      }
      
    }
  }

  // when the central disconnects, print it out:
  Serial.print(F("Disconnected from central: "));
  Serial.println(central.address());
}

