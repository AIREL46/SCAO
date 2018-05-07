/**
 * Exemple de code pour lire plusieurs capteurs DS18B20 sur un même bus 1-Wire.
 */
 
/* Dépendance pour le bus 1-Wire */
#include <OneWire.h>
 
 
/* Broche du bus 1-Wire */
const byte BROCHE_ONEWIRE = 17;

/* Code de retour de la fonction getTemperature() */
enum DS18B20_RCODES {
  READ_OK,
  NO_SENSOR_FOUND,
  INVALID_ADDRESS,
  INVALID_SENSOR
};


/* Création de l'objet OneWire pour manipuler le bus 1-Wire */
OneWire ds(BROCHE_ONEWIRE);
 
 
/**
 * Fonction de lecture de la température via un capteur DS18B20.
 */
byte getTemperature(float *temperature, byte reset_search) {
  byte data[9], addr[8];
  // data[] : Données lues depuis le scratchpad
  // addr[] : Adresse du module 1-Wire détecté
  
  /* Reset le bus 1-Wire ci nécessaire (requis pour la lecture du premier capteur) */
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
 
 
/** Fonction setup() **/
void setup() {

  /* Initialisation du port série */
  //Serial.begin(9600);
}
 
 
/** Fonction loop() **/
void loop() {
  Serial.begin(9600);
  float temperature[2];
   
  /* Lit les températures des trois capteurs */
  if (getTemperature(&temperature[0], true) != READ_OK) {
    Serial.println(F("Erreur de lecture du capteur 1"));
    return;
  }
  if (getTemperature(&temperature[1], false) != READ_OK) {
    Serial.println(F("Erreur de lecture du capteur 2"));
    return;
  }
     
  /* Affiche les températures */
  Serial.print(F("Temperatures : "));
  Serial.print(temperature[0], 2);
  Serial.write(176); // Caractère degré
  Serial.print(F("C, "));
  Serial.print(temperature[1], 2);
  Serial.write(176); // Caractère degré
  Serial.println(F("C, "));
  }
