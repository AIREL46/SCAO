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

#define STATE_OFF   (0x00) //Table de cuisson OFF
#define STATE_ON    (0x01) //Table de cuisson ON
#define STATE_REGUL (0x02) //Démarre le programme

#define GABARIT_1   (0x01) //Définition des 9 gabarits
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
unsigned char u8_State    = STATE_OFF; //Initialisation State OFF
unsigned int  u16_DC      = 0; //Initialisation DC=0
unsigned char u8_Gabarit  = GABARIT_5; //Initialisation du gabarit 5
float  u16_Tm      = 83;            //Initialisation de la Température en centième de °C

// BLE Rupteur Switch Characteristic - custom 128-bit UUID, read and writable by central
// Initialisation des variables Ble
BLEUnsignedCharCharacteristic StateCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEUnsignedIntCharacteristic DCCharacteristic("19B10002-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEUnsignedCharCharacteristic GabaritCharacteristic("19B10003-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEUnsignedIntCharacteristic TmCharacteristic("19B10004-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
const int ledPina = 13; // pin to use for the LED Arduino
const int ledPinv = 4; // pin to use for the LED verte
const int ledPinj = 7; // pin to use for the LED jaune
const int ledPinr = 8; // pin to use for the LED rouge
const int ledPinr0 = 2; // pin to use for the relay 0
const int ledPinr1 = 3; // pin to use for the relay 1
void setup() {
  Serial.begin(9600);
  
  // set LED pin to output mode
  pinMode(ledPina, OUTPUT);
  pinMode(ledPinv, OUTPUT);
  pinMode(ledPinj, OUTPUT);
  pinMode(ledPinr, OUTPUT);

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
  delay(2000);
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
        digitalWrite(ledPinr0, HIGH);         // will switch on the relay 0
        digitalWrite(ledPinr1, HIGH);         // will switch on the relay 1
        digitalWrite(ledPina, HIGH);         // will turn the LED Arduino on
        digitalWrite(ledPinv, HIGH);         // will turn the LED verte on
        digitalWrite(ledPinj, HIGH);         // will turn the LED jaune on
        digitalWrite(ledPinr, HIGH);         // will turn the LED rouge on
        Serial.println("LED on");
      } 
      else 
      {                              
          Serial.println(F("LED off"));
          digitalWrite(ledPinr0, LOW);         // will switch off the relay 0
          digitalWrite(ledPinr1, LOW);         // will switch off the relay 1
          digitalWrite(ledPina, LOW);          // will turn the LED Arduino off
          digitalWrite(ledPinv, LOW);          // will turn the LED verte off
          digitalWrite(ledPinj, LOW);          // will turn the LED jaune off
          digitalWrite(ledPinr, LOW);          // will turn the LED rouge off
      }
    }
  }

  // when the central disconnects, print it out:
  Serial.print(F("Disconnected from central: "));
  Serial.println(central.address());
}

