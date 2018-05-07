/**
 * e-p-433-v2
 * 1 - Introduction
 *Dans le cadre du concept culinaire Quiet cook http://quiet-cook.com/ 
 *et de son SCAO http://fablabo.net/wiki/SCAO. 
 *Le prototypage (prototype N°3) de la e-poignée (433MHZ en version 2)
 *est réalisé par Régis LERUSTE http://fablabo.net/wiki/Utilisateur:LERUSTE_REGIS
 *et Olivier MARAIS http://fablabo.net/wiki/Cahier_de_recettes#Les_recettes_d.27Olivier
 *Dans l'environnement de développement Arduino IDE, 
 *le programe e-p-433-v2 constitue le code source qui permet l'édition, 
 *la compilation et le transfert du firmware à destination du micro-contrôleur.
 *L'objet de ce programme est double :
 *- la capture des températures délivrées par 2 thermomètres digitaux.
 *- la transmission périodique de ces valeurs au e-rupteur (e-r-433).
 *Ce programme est dévelloppé sous licence creative commons CC-BY-SA.
 *Il utile les librairies et codes sources dévelloppés par :
 *- Paul Stoffregem, accesibles par les liens :
 *- https://www.pjrc.com/teensy/td_libs_OneWire.html
 *- https://github.com/PaulStoffregen/OneWire
 *- Mike McCauley, accesibles par les liens :
 *- https://www.pjrc.com/teensy/td_libs_VirtualWire.html
 *- http://www.airspayce.com/mikem/arduino/VirtualWire.pdf
 */
/**
 * 2 - Initialisation des paramètres
 * 2a - Acquisition des températures
 * Exemple de code pour lire un unique capteur DS18B20 sur un bus 1-Wire.
 */
 
/* Dépendance pour le bus 1-Wire */
#include <OneWire.h>
#include "TimeLib.h"
 
/* Broche du bus 1-Wire */
const byte BROCHE_ONEWIRE = 17;

/* Code de retour de la fonction getTemperature() */
enum DS18B20_RCODES {
  READ_OK,  // Lecture ok
  NO_SENSOR_FOUND,  // Pas de capteur
  INVALID_ADDRESS,  // Adresse reçue invalide
  INVALID_SENSOR  // Capteur invalide (pas un DS18B20)
};


/* Création de l'objet OneWire pour manipuler le bus 1-Wire */
OneWire ds(BROCHE_ONEWIRE);
/**
 * 2b - Mesures des tensions
 */
const int Vbat_demie = A7; //Mesure de la moitié de la tension Vbat
float Vbat;
const float Vbat_limite = 4210;
const float Vbat_nominal = 3700;
const float Vbat_min = 3600;
const float Vbat_cut_off = 2800;
const int Vusb_demie = A8; //Mesure de la moitié de la tension Vusb
float Vusb;
const int V33_demie = A9; //Mesure de la moitié de la tension 3.3V
float V33;
const int MaxConv = 8192;
const int MaxVolt = 3272;
/**
 * 2c - BITE
 */
const int led_pin_v = 13;
const int led_pin_j = 14;
const int led_pin_r = 15;
/**
 * 2d - Transmission
 * Chargement de la librairie VirtualWire - Gestion de l'émetteur 433 MHZ
 */
#include <VirtualWire.h>
const int transmit_pin = 18;//Pin de sortie de l'émetteur
byte count = 1;//Initialisation du numéro du message 
/**
 * 3 - Fonctions spécifiques
 * 3a - Fonction d'acquisition de la température via un capteur DS18B20.
 */
byte getTemperature(float *temperature, byte reset_search) {
  byte data[9], addr[8];
  // data[] : Données lues depuis le scratchpad
  // addr[] : Adresse du module 1-Wire détecté
  
  /* Reset le bus 1-Wire si nécessaire (requis pour la lecture du premier capteur) */
  if (reset_search) {
    ds.reset_search();
  }
 
  /* Recherche le prochain capteur 1-Wire disponible */
  if (!ds.search(addr)) {
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
  ds.reset();
  ds.select(addr);
  
  /* Lance une prise de mesure de température et attend la fin de la mesure */
  ds.write(0x44, 1);
  delay(800);
  
  /* Reset le bus 1-Wire, sélectionne le capteur et envoie une demande de lecture du scratchpad */
  ds.reset();
  ds.select(addr);
  ds.write(0xBE);
 
 /* Lecture du scratchpad */
  for (byte i = 0; i < 9; i++) {
    data[i] = ds.read();
  }
   
  /* Calcul de la température en degré Celsius */
  *temperature = (int16_t) ((data[1] << 8) | data[0]) * 0.0625; 
  
  // Pas d'erreur
  return READ_OK;
}
/**
 * 3b - Fonction mesure des tensions et calibration
 */

/** 4 - Fonction setup() **/
void setup() {
  setTime(19, 06, 0, 01, 05, 2018); 
  /* Initialisation du port série */
  //Serial.begin(9600);
  delay(1000);
  Serial.println("Bonjour SCAO");
  pinMode(led_pin_v, OUTPUT);
  pinMode(led_pin_j, OUTPUT);
  pinMode(led_pin_r, OUTPUT);
  analogReadResolution(13);//Mesure de tension
    // Initialise the IO and ISR
  vw_set_tx_pin(transmit_pin);
  vw_setup(2000);   // Bits per sec
}
 
/** 5 - Fonction loop() **/
void loop() {
  Serial.begin(9600);
  float temperature[2];//Mesure de la température
   
  /* Lit la température ambiante à ~1Hz */
  if (getTemperature(&temperature[0], true) != READ_OK) {
    Serial.println(F("Erreur de lecture du capteur"));
    return;
  }
  if (getTemperature(&temperature[1], false) != READ_OK) {
    Serial.println(F("Erreur de lecture du capteur 2"));
    return;
  }
  Serial.print(count);
  Serial.print(" - ");
  /* Affiche la température */
  Serial.print(F("T1 : "));
  Serial.print(temperature[0], 1);
  Serial.print(F("   -  T2 : "));
  Serial.print(temperature[1], 1);
  Serial.print(" degrés ");
  Serial.write('C'); // Caractère degré
  int tmax=25;
  if (temperature[0] >= tmax){digitalWrite(led_pin_r, HIGH);} else {digitalWrite(led_pin_r, LOW);}
  /* Affiche les tensions */
  Vusb=map (2.0038*analogRead(Vusb_demie), 0, MaxConv, 0, MaxVolt);
  Serial.print(" - Vusb : ");
  Serial.print(Vusb);
  Serial.print(" mV ");
  Serial.print(" Vbat : ");
  Vbat=map (2.0038*analogRead(Vbat_demie), 0, MaxConv, 0, MaxVolt);
  if (Vbat <= Vbat_limite && Vbat > Vbat_min){digitalWrite(led_pin_v, HIGH);} else {digitalWrite(led_pin_v, LOW);}
  if (Vbat > Vbat_limite || Vbat <= Vbat_cut_off){digitalWrite(led_pin_r, HIGH);} else {digitalWrite(led_pin_r, LOW);}
  Serial.print(Vbat);
  Serial.print(" mV ");
  V33=map (2.0038*analogRead(V33_demie), 0, MaxConv, 0, MaxVolt);
  Serial.print(" V33 : ");
  Serial.print(V33);
  Serial.println(" mV ");
  /* Transmission des donnèes à l'e-r-433 */ 
  char msg[7] = {'h','e','l','l','o',' ','#'};
  
  msg[6] = count;
  digitalWrite(led_pin_j, HIGH); // Flash a light to show transmitting
  vw_send((uint8_t *)msg, 7);
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(led_pin_j, LOW);
  count = count + 1;
  //delay(1000);
}
