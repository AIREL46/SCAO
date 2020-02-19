/**
 * e-p-wifi.ino
 * Le présent code source est publié sur Github sous licence creative commons CC-BY 
 * Voir -> https://github.com/AIREL46/SCAO/blob/master/Arduino/e-p-wifi/e-p-wifi.ino
 * Ce programme e-p-wifi.ino est dédié au microcontrôleur Arduino MKR wifi 1010 qui équipe la e-poignée du prototype N°3 intégrée dans le SCI.
 * voir ->  https://store.arduino.cc/mkr-wifi-1010
 * Pour mémoire, ce SCI (Système de Cuisson Intelligent) est composé principalement de 2 objets connectés et d'un smartphone.
 * (voir le schéma https://github.com/AIREL46/SCAO/raw/master/wiki/sci.png).
 * Le premier objet connecté est cette e-poignée est le second le e-rupteur (prise meross).
 * Le microcontrôleur introduit la fonction de communication wifi qui offre à l'utilisateur la possibilité de piloter le SCI à partir du smartphone.
 * Ce programme est structuré en paragraphes :
 * 1 - Introduction
 * 2 - Initialisation des paramètres
 * 3 - Fonctions spécifiques
 * 4 - Fonction setup
 * 5 - Fonction loop
 * Chaque paragraphe est constitué de sous paragraphes :
 * a) Les IHM (wifi et calvier)
 * b) Libre
 * c) Acquisition des températures T1 et T2
 * d) Mesures des tensions et calcul de ibat
 * e) Built In Test Equipment (BITE)
 * f) Transmission
 * g) Horodatage et chronomètre
 * h) Bilan énergétique de la batterie
 * i) Régulation de la température
 * j) Visualisation du contenu des échantillons
 * k) Mode sleep
 * 1 - Introduction
 *Dans le cadre du concept culinaire Quiet cook http://quiet-cook.com 
 *et de ce SCI https://fablabo.net/wiki/SCC. 
 *Le prototypage (prototype N°3) de la e-poignée (en version wifi)
 *est réalisé par Régis LERUSTE http://fablabo.net/wiki/Utilisateur:LERUSTE_REGIS
 *Baptiste BOURIAU https://www.baptistebouriau.fr/
 *et Olivier MARAIS http://fablabo.net/wiki/Cahier_de_recettes#Les_recettes_d.27Olivier
*ce programe e-p-wifi.ino constitue le code source qui permet l'édition, 
la compilation et le téléversement du firmware à destination du micro-contrôleur.
*L'environnement de développement Arduino IDE est constitué du microcontrôleur MKR wifi 1010 relié à l'ordinateur 
*à l'aide d'un câble USB. Ce câble permet l'établissement d'une liaison série. 
*De l'ordinateur vers le microcontrôleur pour téléverser le firmware. 
*Du microcontrôleur vers l'ordinateur pour l'envoi de messages à l'aide du port /dev/ttyACM0, 
*soit pour les afficher sur le moniteur série, 
*soit pour les mettre à disposition du programme BASH capture.sh qui édite un fichier "journal".   
*L'objet du firmware est l'administration du microcontrôleur et de ses composants périphériques câblés sur un shield ou une breadboard selon les schéma électriques :
*Shield -> https://github.com/AIREL46/SCAO/blob/master/kicad/e-p-wifi-shield/e-p-wifi.png
*Breadboard -> https://github.com/AIREL46/SCAO/raw/master/wifi/kicad/schema_electrique_e-p-433-wifi.png
*Son exécution par le microcontôleur est systématique dès son téléversement et ensuite à chaque mise sous tension. 
*Il est organisé selon 2 fonctions principales : 
*- la capture des températures délivrées par 2 thermomètres digitaux, le premier concerne la température sur le couvercle de la casserole, le second la température de la batterie, l'une des fonctions secondaires qui assure la sécurité de la e-poignée. .
*- la commande ON/OFF du e-rupteur (meross).
*Ses fonctions principales sont complétées de fonctions secondaires (voir ci-dessous).
*Il utile des ressources extérieures (librairies, codes sources et exemples) développées par des dévoloppeurs (informaticiens). 
*En application des règles de licences Creative commons, chacun, des sous paragraphes ci-dessous, dédié à une fonction, cite, le nom du développeur, 
*indique les liens permettant d'accéder à la librairie ainsi qu'aux codes sources ou aux exemples.
*
*1a IHM -> a.h
 *   
 * 1b - Libre
 * 
 * 1c - Acquisition des températures T1 et T2
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
 * 1d - Mesure des tensions et calcul du courant ibat
 * La mesure des tensions est l'une des fonctions secondaires qui assure la sécurité de la e-poignée.
 * La mesure consiste en une conversion analogique digitale de la tension. Cette conversion est réalisée par le microcontrôleur. La tension à mesurer est appliquée sur l'une de ses entrées analogiques. Pour tenir compte de la tension d'alimentation de 3.3V du microcontrôleur, la tension à mesurer est au préalable divisée par 2 à l'aide d'un pont diviseur constitué de 2 résistances de valeurs égales.
 * La valeur mesurée est ensuite multipliée par 2, plus exactement par une valeur légérement supérieure à 2 pour compenser l'effet de l'impédance de l'entrée du microcontrôleur.
 * La figure accessible par le lien ci-après explicite le principe https://github.com/AIREL46/SCAO/raw/master/wiki/map.png
 * 
 * 1e - BITE
 * L'objet du Build In Test Equipment (BITE) est d'assurer la sécurité de la e-poignée.
 * Cette sécurité se concrétise par un réseau de surveillance qui détecte d'éventuelles anomalies.
 * L'utilisateur est informé de l'état du fonctionnement par 3 leds (verte, orange, rouge).
 * Le BITE surveille la température de la batterie, les tensions continues Vusb, Vbat et V33.
 * 
 * 1f - Transmission
 * L'objet est la transmission périodique (30s) au e-rupteur (e-r-433) des échantillons.
 * Les échantillons ont pour objet le regroupement des données.
 * Chaque échantillon contient : la date et l'heure, la température mesurée sur le couvercle de la casserole ainsi que les données culinaires et de sécurité.
 * Cette fonction utilise un shield AM Transmitter module QAM-TX1 en version 433 MHZ.
 * Ce module est connecté à une antenne 1/4 d'onde.
 * La librarie VirtualWire apporte les fonctions spécifiques qui permettent de gérer cette fonction transmission.
 * Cette Librarie a été développée par Mike McCauley, elle est accesible par les liens :
 *- https://www.pjrc.com/teensy/td_libs_VirtualWire.html
 *- http://www.airspayce.com/mikem/arduino/VirtualWire.pdf
 *- https://github.com/manashmndl/VirtualWire
 * 
 * 1g - Horodatage & Chronomètre
 * Horodatage
 * L'objet de l'horodatage est la datation des échantillons.
 *   
 *  Chronomètre
 *  L'objet du chronomètre est la mesure du temps de travail du microcontrôleur.
 *  La librarie Chrono apporte les fonctions spécifiques qui permettent de gérer cette fonction.
 *  Cette Librarie a été développée par Sofian Audry and Thomas Ouellet Fredericks, elle est accesible par les liens :
 * - http://github.com/SofaPirate/Chrono
 * 
 * 1h Bilan énergétique de la batterie
 * L'objet est l'établissement du bilan énergétique de la batterie
 * Cette fonction réalise les calculs de l'énegie électrique consommée et le ratio par rapport à la capacité nominale de 2000 mAh
 * 1i Calcul
 * 1j - Visualisation du contenu des échantillons
 * L'objet est la visualisation du contenu des échantillons.
 * Cette fonction utilise la liaison série (câble USB) entre le microcontrôleur et l'ordinateur.
 * Elle se concrétise par une console sur l'écran de l'ordinateur.
 * 1k - Mode Sleep
 * L'objet du mode sleep est l'économie d'énergie de la batterie.
 *  
 */
/*
 * 2 - Initialisation des paramètres
 */

 unsigned long tt1=0;//temps de travail 1
 unsigned long tt2=0;//temps de travail 2
 unsigned long ti=30000000;//temps itératif
 unsigned long ts=0;//temps de sleep
 #include "1.h"
/*
 * 2a Les IHM -> a.h
 */
 #include "a.h" 

 /** 
 * 2c - Acquisition des températures
 * Code pour lire un thermomètre digital DS18B20 sur un bus 1-Wire.
 */
 float T1;
 float T2;
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
 * 2d - Mesure des tensions et calcul du courant ibat
 */
 
float Vbat_1; //Initialisation de la variable Vbat_1 (valeur de la tension Vbat avant la résistance de 1 Ohm)
float Vbat_2; //Initialisation de la variable Vbat_2 (valeur de la tension Vbat après la résistance de 1 Ohm)
float ibat; //Initialisation de la variable ibat (valeur du courant qui traverse la résistance de 1 Ohm)
const float Vbat_limite = 4300; //Limite supérieure de Vbat
const float Vbat_nominal = 3700; //Valeur nominale de Vbat
const float Vbat_min = 3600; //Valeur minimun de Vbat
const float Vbat_cut_off = 2800; //Cut off de Vbat*/
float Vusb; //Initialisation de la variable Vusb
float V33; //Initialisation de la variable V33
//Initialisation des valeurs utilisées par la fonction de changement d'échelle (fonction mathématique map() de l'arduino)
const int MaxConv = 4095; //Valeur maximale lue
const int MaxVolt = 3300; //Valeur de la tension correspondante à la valeur maximale

bool state_Vusb = false;

/*
 * 2e - Built In Test Equipment (BITE)
 */



 /** 2f - Transmission
 * Chargement de la librairie VirtualWire - Gestion de l'émetteur 433 MHZ
 **/
/* 
#include <VirtualWire.h>
const int transmit_pin = 4;//Pin de sortie de l'émetteur*/
byte count = 0;//Initialisation du numéro du message 


/**
 * 2g - Horodatage & Chronomètre
 * Horodatage 
 */

 /*
#include "TimeLib.h" //Include TimeLib.h library
/**
 * Chronomètre 
  */
#include <Chrono.h> //Include Chrono.h Library
Chrono Chrono(Chrono::MICROS);//Instanciate a Chrono object

/**
 * 2h - Bilan énergétique de la batterie
 * Chargement de la librairie
 */
unsigned long Etot=0; //Energie électrique totale consommée en joule
unsigned long Et=0; //Energie électrique consommée pendant le travail
unsigned long Es=0; //Energie électrique consommée pendant le sommeil (sleep)
unsigned long Ec=0; //Energie électrique consommée cumulée

/**
 * 2i Calcul
 */

/**
 * 2j - Visualisation du contenu des échantillons
/**

/*
 * 2k mode sleep
 */
 
bool val_sleep = false;//variable to store the read value


 /*
  * 3 - Fonctions spécifiques
  */
/*
 //#include <digitalWriteFast.h> Non supporter par le MKR WiFi 1010
   */
 //Wait for serial monitor
 void wait_s_m(){
    int time = 0;
    while (!Serial && time < 1000) {
        mesures();//Lance la fonction mesures() pour connaitre l'état de Vusb (state_Vusb)
        if (!state_Vusb) {digitalWrite(led_pin_r, HIGH);}
        if (state_Vusb) {digitalWrite(led_pin_v, HIGH);}
        delay(30);
        if (!state_Vusb) {digitalWrite(led_pin_r, LOW);}
        if (state_Vusb) {digitalWrite(led_pin_v, LOW);}
        delay(30);
    }
    // normal delay for Arduino Serial Monitor
    delay(1200);
  }

 /*
  * 3a Les IHM -> a.h
  */

  /*
   * 3b - Libre
   */
   
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


  /**
 * 3d - Mesure des tensions et calcul du courant ibat
 */
  //fonction de changement d'échelle (fonction mathématique map() de l'arduino)
  //La multiplication par 2.0038 compense la division par 2 (pont diviseur) et l'impédance de l'entrée du microcontrôleur pour les chiffres après la virgule.
  void mesures(){
  Vusb = map (2.0038*analogRead(Vusb_demie), 0, MaxConv, 0, MaxVolt);
  delay(120);//Pour compenser la durée necessaire à la conversion analogique digital
  Vbat_1 = map (2.0038*analogRead(Vbat_demie_1), 0, MaxConv, 0, MaxVolt);
  delay(120);//Pour compenser la durée necessaire à la conversion analogique digital
  Vbat_2 = map (2.0038*analogRead(Vbat_demie_2), 0, MaxConv, 0, MaxVolt);
  delay(120);//Pour compenser la durée necessaire à la conversion analogique digital
  ibat = Vbat_1 - Vbat_2;
  V33 = map (2.0038*analogRead(V33_demie), 0, MaxConv, 0, MaxVolt);
  delay(120);//Pour compenser la durée necessaire à la conversion analogique digital
  if (Vusb < 1000) {state_Vusb = false;}
  if (Vusb > 4000) {state_Vusb = true;}
  }
// 3e - Built In Test Equipment (BITE)
//3f Transmission
//3g Horodatage et chronomètre
/** 3h - Bilan énergétique de la batterie
 */
//3h Bilan énergétique de la batterie
//3i Calcul
  /**
 * 3j - Visualisation du contenu des échantillons
 */
  void visu(){
  Serial.print(count);//N° de l'échantillon
  Serial.print(";");//Séparation des champs par une virgule
//  digitalClockDisplay();//Heure et date
  delay(100);
  Serial.print(T1, 2);//Température mesurée T1 en °C sur le couvercle de la casserole
  Serial.write(";"); //Séparation des champs par une virgule
  Serial.print(T2, 2);//Température mesurée T2 en °C sur la batterie
  Serial.write(";"); //Séparation des champs par une virgule
  Serial.print(Vusb);//Tension mesurée Vusb en mV
  Serial.print(";");//Séparation des champs par une virgule
  Serial.print(Vbat_1);//Tension mesurée Vbat1 en mV
  Serial.print(";");//Séparation des champs par une virgule
  Serial.print(Vbat_2);//Tension mesurée Vbat1 en mV
  Serial.print(";");//Séparation des champs par une virgule
  Serial.print(ibat);//Courant mesuré ibat en mA
  Serial.print(";");//Séparation des champs par une virgule
  Serial.print(V33);//Tension mesurée V33 en mV
  Serial.print(";");//Séparation des champs par une virgule
  Serial.println(Ec);//Energie mesurée Ec en joules
  delay(2000);
  }
//3k Mode sleep
/** 4 - Fonction setup() **/

void setup() {
  /* Initialisation du port série */
  Serial.begin(9600);
  delay(2000);
  mesures();
  pinMode(led_pin_v, OUTPUT);
  pinMode(led_pin_j, OUTPUT);
  pinMode(led_pin_r, OUTPUT);
  pinMode(led_pin_b, OUTPUT);  // sets the digital pin 19 as output
  //Test des leds (mise sous tension)
  digitalWrite(led_pin_v, HIGH);
  digitalWrite(led_pin_j, HIGH);
  digitalWrite(led_pin_r, HIGH);
  digitalWrite(led_pin_b, HIGH);
 /*
  * 4a Les IHM - Commun -> a.h
  */
  setup_a ();
 
 
//4b - Libre
//4c - Acquisition des températures T1 et T2

/*
 * 4d - Mesure des tensions et calcul du courant ibat*/
  analogReadResolution(12);
  // 4e - Built In Test Equipment (BITE)

 //4j - Visualisation du contenu des échantillons
  Serial.println ("Cuisson en cours - chaque échantillon contient les champs suivants :");
  Serial.println("N°;heure;date;T1 (degrés C);T2 (degrés C);Vusb (mV);Vbat (mV);ibat (mA);V33 (mV);Ec (joules)");  
 //4k - Mode sleep
  pinMode(inPin_sleep, INPUT);    // sets the digital pin 10 as input
  digitalWrite(led_pin_r, HIGH);//USB serial connection is not establihed - Clic on serial monitor icon (right top icon)
  wait_s_m();//Wait for serial monitor 
  //while (!Serial);
    delay(100);
    digitalWrite(led_pin_r, LOW);
    //Serial.println("Starting...");
    delay(100);

//4f Transmission
//4g Horodatage et chronomètre
//4h - Bilan énergétique de la batterie
//4i Calcul

}

void loop() {
//5a Les IHM
//5a-1 IHM wifi
//5a-2 IHM clavier
//5b - Libre
//5c - Acquisition des températures T1 et T2
  //float T1;
  /* Lit la température T1 */
  if (getT1(&T1, true) != READ_OK) {
    Serial.println(F("Erreur de lecture du capteur"));
    return;
  }
  //float T2;
  /* Lit la température ambiante à ~1Hz */
  if (getT2(&T2, true) != READ_OK) {
    Serial.println(F("Erreur de lecture du capteur"));
    return;
  }
  
  //5d - Mesure des tensions et calcul du courant ibat
 mesures();

// 5e - Built In Test Equipment (BITE)
 //5f - Transmission
  /* Transmission des donnèes à l'e-r-433 */ 
  /*La fonction de transmission vw_send(message, length) : transmit a message, "message" is an array of the bytes to send,
  and "length" is the number of bytes stored in the array.*/

  count = count +1;

//5g Horodatage et chronomètre
//5h - Bilan énergétique de la batterie
 tt2 = (Chrono.elapsed());
 Et = ((Vbat_1/1000) * ibat)*((tt1 + tt2)/1000000);
 if (val_sleep) {Es = ((Vbat_1/1000) * 1.5)*(ts/1000000);}
// if (!  ) {Es = ((Vbat_1/1000) * ibat)*(ts/1000000);}
 Etot = Et + Es;
 Ec = Ec + Etot;  
//5i Calcul
//5j - Visualisation du contenu des échantillons
//Appel de la fonction visu() si le Teensy 3.2 est connecté à l'ordinateur (reçoit du 5V) à l'aide d'un câble USB
  if (state_Vusb){visu();}
}
//5k - Mode sleep
