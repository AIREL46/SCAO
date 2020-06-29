/*1c - Acquisition des températures T1 et T2
* L'acquisition de la température est réalisée à l'aide d'un DS18B20  digital  thermometer  provides  9-bit  to  12-bit  Celsius  temperature  measurements.
* The  DS18B20  communicates  over  a  1-Wire  bus.
* La librarie OneWire.h met à disposition un ensemble de fonction permettant de gérer l'échange de données entre le DS18B20 et le microcontrôleur.
* Le développement de cette librarie est assuré par Paul Stoffregem, accessibles par les liens :
*
*- https://www.pjrc.com/teensy/td_libs_OneWire.html
*- https://github.com/PaulStoffregen/OneWire
*Il utile le code source dévelloppé par :
*- Fabien Batteix (Skywood) qui est le rédacteur en chef et administrateur du site Carnet du Maker, ainsi que le gérant de l'entreprise TamiaLab qui édite le site.
*- selon l'article https://www.carnetdumaker.net/articles/mesurer-une-temperature-avec-un-capteur-1-wire-ds18b20-et-une-carte-arduino-genuino/
*- en tenant compte que pour des raisons de sécurité inhérant au projet SCAO qu'il est indispensable que la capture de données en provenance
* des 2 thermomètres digitaux DB18B20 se réalise toujours dans le même ordre, en particulier après un changement de l'un ou des deux thermomètres.
*
/*
* 2c - Acquisition des températures
* Code pour lire un thermomètre digital DS18B20 sur un bus 1-Wire.
*/
float T1;
float T2;
float Ti;
/* Dépendance pour le bus 1-Wire */
#include <OneWire.h> //Chargement de la librairie OneWire.h

/* Code de retour des 2 fonctions getT1() et getT2() */
enum DS18B20_RCODES {
 READ_OK,  // Lecture ok
 NO_SENSOR_FOUND,  // Pas de capteur
 INVALID_ADDRESS,  // Adresse reçue invalide
 INVALID_SENSOR  // Capteur invalide (pas un DS18B20)
};

/* Création des 2 objets OneWire pour manipuler les 2 bus 1-Wire */
OneWire ds1(BROCHE_ONEWIRE_1);
OneWire ds2(BROCHE_ONEWIRE_2);

/**
* 3c-1 - Fonction d'acquisition de la température via le 1er thermomètre digital DS18B20 (ds1).
* Fonction de lecture de la température via un thermomètre digital DS18B20 câblé sur le 1er bus ds1.
*/
byte getT1(float *T1, byte reset_search) {
byte data[9], addr[8];
// data[] : Données lues depuis le scratchpad
// addr[] : Adresse du module 1-Wire détecté

/* Reset le bus 1-Wire si nécessaire (requis pour la lecture du premier capteur) */
if (reset_search) {
 ds1.reset_search();
}

/* Recherche le prochain capteur 1-Wire disponible */
if (!ds1.search(addr)) {
 // Pas de capteur
 return NO_SENSOR_FOUND;
}

/* Vérifie que l'adresse a été correctement reçue */
if (OneWire::crc8(addr, 7) != addr[7]) {
 // Adresse invalide
 return INVALID_ADDRESS;
}

/* Vérifie qu'il s'agit bien d'un DS18B20 */
if (addr[0] != 0x28) {
 // Mauvais type de capteur
 return INVALID_SENSOR;
}

/* Reset le bus 1-Wire et sélectionne le capteur */
ds1.reset();
ds1.select(addr);

/* Lance une prise de mesure de température et attend la fin de la mesure */
ds1.write(0x44, 1);
delay(800);

/* Reset le bus 1-Wire, sélectionne le capteur et envoie une demande de lecture du scratchpad */
ds1.reset();
ds1.select(addr);
ds1.write(0xBE);

/* Lecture du scratchpad */
for (byte i = 0; i < 9; i++) {
 data[i] = ds1.read();
}

/* Calcul de la température en degré Celsius */
*T1 = (int16_t) ((data[1] << 8) | data[0]) * 0.0625;

// Pas d'erreur
return READ_OK;
}
/** 3c-2 - Fonction d'acquisition de la température via le 2ème thermomètre digital DS18B20 (ds2).
*/
byte getT2(float *T2, byte reset_search) {
byte data[9], addr[8];
// data[] : Données lues depuis le scratchpad
// addr[] : Adresse du module 1-Wire détecté

/* Reset le bus 1-Wire ci nécessaire (requis pour la lecture du premier capteur) */
if (reset_search) {
 ds2.reset_search();
}

/* Recherche le prochain capteur 1-Wire disponible */
if (!ds2.search(addr)) {
 // Pas de capteur
 return NO_SENSOR_FOUND;
}

/* Vérifie que l'adresse a été correctement reçue */
if (OneWire::crc8(addr, 7) != addr[7]) {
 // Adresse invalide
 return INVALID_ADDRESS;
}

/* Vérifie qu'il s'agit bien d'un DS18B20 */
if (addr[0] != 0x28) {
 // Mauvais type de capteur
 return INVALID_SENSOR;
}

/* Reset le bus 1-Wire et sélectionne le capteur */
ds2.reset();
ds2.select(addr);

/* Lance une prise de mesure de température et attend la fin de la mesure */
ds2.write(0x44, 1);
delay(800);

/* Reset le bus 1-Wire, sélectionne le capteur et envoie une demande de lecture du scratchpad */
ds2.reset();
ds2.select(addr);
ds2.write(0xBE);

/* Lecture du scratchpad */
for (byte i = 0; i < 9; i++) {
 data[i] = ds2.read();
}

/* Calcul de la température en degré Celsius */
*T2 = (int16_t) ((data[1] << 8) | data[0]) * 0.0625;

// Pas d'erreur
return READ_OK;
}

//4c - Acquisition des températures T1 et T2

//5c - Acquisition des températures T1 et T2
