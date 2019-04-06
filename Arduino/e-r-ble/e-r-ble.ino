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
#include <CurieBLE.h>

#define STATE_OFF   (0x00)
#define STATE_ON    (0x01)
#define STATE_REGUL (0x02)

#define GABARIT_1   (0x01)
#define GABARIT_2   (0x02)
#define GABARIT_3   (0x03)
#define GABARIT_4   (0x04)
#define GABARIT_5   (0x05)
#define GABARIT_6   (0x06)
#define GABARIT_7   (0x07)
#define GABARIT_8   (0x08)
#define GABARIT_9   (0x09)



BLEPeripheral blePeripheral;  // BLE Peripheral Device (the board you're programming)
BLEService RupteurService("19B10000-E8F2-537E-4F6C-D104768A1214"); // BLE Rupteur Service
unsigned char u8_State    = STATE_OFF;
unsigned int  u16_DC      = 0;
unsigned char u8_Gabarit  = GABARIT_5;
unsigned int  u16_Tm      = 0;            //Température en centième de °C


// BLE Rupteur Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEUnsignedCharCharacteristic StateCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEUnsignedIntCharacteristic DCCharacteristic("19B10002-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEUnsignedCharCharacteristic GabaritCharacteristic("19B10003-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEUnsignedIntCharacteristic TmCharacteristic("19B10004-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

const int ledPin = 13; // pin to use for the LED

void setup() {
  Serial.begin(9600);

  // set LED pin to output mode
  pinMode(ledPin, OUTPUT);

  // set advertised local name and service UUID:
  blePeripheral.setLocalName("e-rupteur");
  blePeripheral.setAdvertisedServiceUuid(RupteurService.uuid());

  // add service and characteristic:
  blePeripheral.addAttribute(RupteurService);
  blePeripheral.addAttribute(StateCharacteristic);
  blePeripheral.addAttribute(DCCharacteristic);
  blePeripheral.addAttribute(GabaritCharacteristic);
  blePeripheral.addAttribute(TmCharacteristic);

  // set the initial value for the characeristic:
  StateCharacteristic.setValue(u8_State);
  DCCharacteristic.setValue(u16_DC);
  GabaritCharacteristic.setValue(u8_Gabarit);
  TmCharacteristic.setValue(u16_Tm);

  // begin advertising BLE service:
  blePeripheral.begin();

  Serial.println("BLE LED Peripheral");
}

void loop() {
  // listen for BLE peripherals to connect:
  BLECentral central = blePeripheral.central();

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
      if (StateCharacteristic.written()) 
      {
        u8_State = StateCharacteristic.value();
      }
      if (DCCharacteristic.written()) 
      {
        u16_DC = DCCharacteristic.value();
      }
      if (GabaritCharacteristic.written()) 
      {
        u8_Gabarit = GabaritCharacteristic.value();
      }
      if (TmCharacteristic.written()) 
      {
        u16_Tm = TmCharacteristic.value();
      }

      if(u8_State == STATE_ON)
      {
        digitalWrite(ledPin, HIGH);         // will turn the LED on
        Serial.println("LED on");
      } 
      else 
      {                              
          Serial.println(F("LED off"));
          digitalWrite(ledPin, LOW);          // will turn the LED off
      }
    }
  }

  // when the central disconnects, print it out:
  Serial.print(F("Disconnected from central: "));
  Serial.println(central.address());
}

