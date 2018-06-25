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
 *- Michael Margolis, accesibles par les liens :
 *- https://www.pjrc.com/teensy/td_libs_Time.html
 *- https://github.com/PaulStoffregen/Time
 */
/**
 * 2 - Initialisation des paramètres
 * 2a - Acquisition des températures
 * Code pour lire plusieurs capteurs DS18B20 sur un bus 1-Wire.
 */
 
/* Dépendance pour le bus 1-Wire */
#include <OneWire.h> //Chargement de la librairie OneWire.h
/* Broche du bus 1-Wire */
const byte BROCHE_ONEWIRE = 17;
const byte nb_cap = 0x02;

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
 * 2c - Built In Test Equipment (BITE)
Les résultats du BITE sont visalisés par 3 leds :
verte : l'allumage témoigne d'un bon fonctionnement
        l'extinction peut être envisagée en mode sleep
jaune : allumée quand l'émission commence
        éteinte quand l'émission s'arrète
rouge : l'allumage témoigne d'une ou plusieurs anomalies
 */
const int led_pin_v = 13;//Led verte
const int led_pin_j = 14;//Led jaune
const int led_pin_r = 15;//Led rouge
/**
 * 2d - Transmission
 * Chargement de la librairie VirtualWire - Gestion de l'émetteur 433 MHZ
 */
#include <VirtualWire.h>
const int transmit_pin = 18;//Pin de sortie de l'émetteur
byte count = 1;//Initialisation du numéro du message 
/**
 * 2e - Horodatage
 * Chargement de la librairie TimeLib.h
 */
#include "TimeLib.h"
/**
 * 2f - Mode sleep
 * Chargement de la librairie
 */
#include <avr/sleep.h>
/**
 * 3 - Fonctions spécifiques
 * 3a - Fonction d'acquisition de la température via un capteur DS18B20.
 */
byte getTemperature(float *temperature, byte reset_search) {
  byte data[9], addr[8]; 
  // Si le booléen reset_search est vrai, on recommence la recherche de capteur de zéro.
  //Ce booléen doit être à true lors de la lecture du premier capteur.. 
  // data[] : Données lues depuis le scratchpad
  // addr[] : Adresse du module 1-Wire détecté
  byte reg2 = {nb_cap};//Données à écrire dans le byte 2
  byte reg3 = {0xFF};//Données à écrire dans le byte 3
  byte reg4 = {0x7F};//Données à écrire dans le byte 4
  /* Reset le bus 1-Wire si nécessaire (requis pour la lecture du premier capteur) */
  if (reset_search) {
    ds.reset_search();
  }
 
  /* Recherche le prochain capteur 1-Wire disponible */
  /*Quand la fonction ds.search(addr) est exécutée 
  l'adresse du capteur se trouve dans l'array de 8 bytes addr 
  Boolean operator ! (logical not)*/
  if (!ds.search(addr)) {
    // Pas de capteur
    return NO_SENSOR_FOUND;
  }
  
  /* Vérifie que l'adresse a été correctement reçue */
  /* Compute a CRC check on an array of data. */
  if (OneWire::crc8(addr, 7) != addr[7]) {
    // Adresse invalide
    return INVALID_ADDRESS;
  }
 
  /* Vérifie qu'il s'agit bien d'un DS18B20 */
  if (addr[0] != 0x28) {
    // Mauvais type de capteur
    return INVALID_SENSOR;
  }
   
   /* Write the bytes 2, 3 et 4 to scratchpad */
   ds.reset();
   ds.select(addr);
   ds.write(0x4E);//Write scratchpad
   ds.write(reg2);
   ds.write(reg3);
   ds.write(reg4);
   delay(200);
  //Copy scratchpad to EEPROM
   ds.reset();
   ds.select(addr);
   ds.write(0x48);//Copy scratchpad to EEPROM
   delay(200);
  /* Reset le bus 1-Wire et sélectionne le capteur */
  ds.reset(); //Reset the 1-wire bus. Usually this is needed before communicating with any device. 
  /* Select a device based on its address. */ 
  ds.select(addr);
   /* Lance une prise de mesure de température et attend la fin de la mesure */
  ds.write(0x44, 1); //Write a byte, and leave power applied to the 1 wire bus. 
  delay(800);
  
  /* Reset le bus 1-Wire, sélectionne le capteur et envoie une demande de lecture du scratchpad */
  ds.reset();
  ds.select(addr);
  ds.write(0xBE);//Read scratchpad
 
 /* Lecture du scratchpad */
  for (byte i = 0; i < 9; i++) {
    data[i] = ds.read();
  }
    
  /* Calcul de la température en degré Celsius */
  *temperature = (int16_t) ((data[1] << 8) | data[0]) * 0.0625; 
  //Affichage de l'adresse du capteur
  Serial.print(data[2]);
  Serial.print(" - ");
  Serial.print(" ad-cap : ");
  for(byte i = 0; i < 8; ++i) {
    if (addr[i] < 0x10) Serial.write('0');
    Serial.print(addr[i], HEX);
    Serial.write(' ');
  }
  // Pas d'erreur
  return READ_OK;
}
/**
 * 3b - Fonction mesure des tensions et calibration
 */

/** 4 - Fonction setup() **/
void setup() {
  /* Initialisation du port série */
  //Serial.begin(9600);
  delay(1000);
  Serial.println("Bonjour SCAO");
  //a) Acquisition des temtératures
  //b) Mesure des tensions
  analogReadResolution(13);
  //c) BITE
  pinMode(led_pin_v, OUTPUT);
  pinMode(led_pin_j, OUTPUT);
  pinMode(led_pin_r, OUTPUT);
  //d) Transmission
    // Initialise the IO and ISR
  vw_set_tx_pin(transmit_pin);
  vw_setup(2000);   // Bits per sec
  //e) Horodatage
  setTime(18, 02, 00, 23, 05, 2018);
  //f) Mode sleep
}
 
/** 5 - Fonction loop() **/
void loop() {
  Serial.begin(9600);
  //a) Acquisition des températures
  float temperature[2];//Initialise une array pour mémoriser T1 et T2
  /* Lit la température T1 */
  if (getTemperature(&temperature[0], true) != READ_OK) {
    Serial.println(F("Erreur de lecture du capteur"));
    return;
  }
  if (getTemperature(&temperature[1], false) != READ_OK) {
    Serial.println(F("Erreur de lecture du capteur 2"));
    return;
  }

  //b) Mesure des tensions

  //c) BITE
  int tmax=25;
  if (temperature[0] >= tmax){digitalWrite(led_pin_r, HIGH);} else {digitalWrite(led_pin_r, LOW);}
  if (Vbat <= Vbat_limite && Vbat > Vbat_min){digitalWrite(led_pin_v, HIGH);} else {digitalWrite(led_pin_v, LOW);}
  if (Vbat > Vbat_limite || Vbat <= Vbat_cut_off){digitalWrite(led_pin_r, HIGH);} else {digitalWrite(led_pin_r, LOW);}

  //d) Transmission
  /* Transmission des donnèes à l'e-r-433 */ 
  char msg[7] = {'h','e','l','l','o',' ','#'};
  
  msg[6] = count;
  digitalWrite(led_pin_j, HIGH); // Flash a light to show transmitting
  vw_send((uint8_t *)msg, 7);
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(led_pin_j, LOW);
  count = count + 1;
  //delay(1000);

  //e) Horodatage
  time_t t = now();

  //f) Mode sleep

  //g) Visualisation des résultats
  Serial.print(day (t));
  Serial.print("/");
  Serial.print(month (t));
  Serial.print("/");
  Serial.print(year (t));
  Serial.print(" - ");
  Serial.print(hour (t));
  Serial.print(":");
  Serial.print(minute (t));
  Serial.print(":");
  Serial.print(second (t));
  Serial.print(" - ");
  Serial.print(count);
  Serial.print(" - ");
  /* Affiche T1 et T2 */
  Serial.print(F("T1 : "));
  Serial.print(temperature[0], 1);
  Serial.print(F("   -  T2 : "));
  Serial.print(temperature[1], 1);
  Serial.print(" degrés ");
  Serial.write('C'); // Caractère degré
  /* Affiche les tensions */
  Vusb=map (2.0038*analogRead(Vusb_demie), 0, MaxConv, 0, MaxVolt);
  Serial.print(" - Vusb : ");
  Serial.print(Vusb);
  Serial.print(" mV ");
  Serial.print(" Vbat : ");
  Vbat=map (2.0038*analogRead(Vbat_demie), 0, MaxConv, 0, MaxVolt);
  Serial.print(Vbat);
  Serial.print(" mV ");
  V33=map (2.0038*analogRead(V33_demie), 0, MaxConv, 0, MaxVolt);
  Serial.print(" V33 : ");
  Serial.print(V33);
  Serial.println(" mV ");
}
