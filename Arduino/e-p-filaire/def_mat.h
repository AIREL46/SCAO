/*
 * Définitions matérielles du microcontrôleur MKR wifi 1010
 * Ci-dessous le lien pour visualiser le PinOut du MKR wifi 1010
 * https://www.henschke-geraetebau.de/dr/pic/MKR_WiFi_1010_Pinout.jpg
 * Ci-dessous le lien pour visualiser le schéma électrique du shield du MKR wifi 1010
 *https://github.com/AIREL46/SCAO/blob/master/kicad/e-p-filaire/e-p-filaire.png
  */
 //Les 28 pins correspondantes au PinOut du microcontrôleur MKR wifi 1010 sont représentées ci-dessous
 //En rapport au schéma électrique, une variable est initialisée si la pin est utilisée
#ifndef DEF_MAT_H
#define DEF_MAT_H
#include <Arduino.h>
 //AREF
 extern const int V33_demie; //Initialisation de la variable V33_demie sur l'entrée analogique A0
 extern const int Vusb_demie; //Initialisation de la variable Vusb_demie sur l'entrée analogique A1
 //A2 - NU
 extern const int relay; //Commande du relais connecté sur l'entrée digitale D18 (A3)
 extern const int led_pin_b;//blue led connected to digital pin D19 (A4)
 extern const int itc;//Initialisation de la valeur mesurée par le module phidgets 1122
 extern const int P230V;//Initialisation de la variable P230V et affectation de l'entrée analogique A6 (un chargeur 5V atteste de la présence 230V)
 //D0 - NU
 //D1 - NU
 //D2 - NU
 extern const byte BROCHE_ONEWIRE;//Initialisation de la variable BROCHE_ONEWIRE et affectation de l'entrée digitale D3 (connection du thermomètre digital DS18B20 pour la mesure T)
 extern const int speaker;//Speaker connecté sur l'entrée digitale D4
 extern const int led_pin_v;//Led verte connectée sur l'entrée digitale D5
 extern const int led_pin_j;//Led jaune connectée sur l'entrée digitale D6
 extern const int led_pin_r;//Led rouge connectée sur l'entrée digitale D7
 //MOSI - Interface SPI - (D8)
 //SCK  - Interface SPI - (D9)
 //MISO  - Interface SPI - (D10)
 //SDA - interface I2C - (D11)
 //SCL - interface I2C - (D12)
 //Rx - Interface UART (D13)
 //Tx - Interface UART (D14)
 //RESET
 //GND
 //+3V3
 //VIN
 //+5V
 #endif
