/**
 * e-p-wifi.ino
 * Ce programme e-p-wifi.ino résulte d'un portage informatique dû au remplacement du micrôcontrôleur Teensy 3.2 
 * par le micrôcontrôleur Arduino MKR wifi 1010 https://store.arduino.cc/mkr-wifi-1010. 
 * Ce portage permet d'atteindre les objectifs suivants :
 * - ce nouveau microcontrôleur introduit une nouvelle fonction "IHM wifi" 
 *   qui offre à l'utilisateur la possibilité de piloter l'application SCAO du prototype n°3 à partir d'un smartphone
 * Ce programme est structuré en paragraphes :
 * 1 - Introduction
 * 2 - Initialisation des paramètres
 * 3 - Fonctions spécifiques
 * 4 - Fonction setup
 * 5 - Fonction loop
 * Chaque paragraphe est constitué de sous paragraphes :
 * a) IHM wifi
 * b) IHM clavier
 * c) Acquisition des températures T1 et T2
 * d) Mesures des tensions et calcul de ibat
 * e) Built In Test Equipment (BITE)
 * f) Transmission
 * g) Horodatage et chronomètre
 * h) Bilan énergétique de la batterie
 * i) Calcul
 * j) Visualisation du contenu des échantillons
 * k) Mode sleep
 * 1 - Introduction
 *Dans le cadre du concept culinaire Quiet cook http://quiet-cook.com 
 *et de son Système de Cuisson Assistée par Ordinateur (SCAO) http://fablabo.net/wiki/SCAO. 
 *Le prototypage (prototype N°3) de la e-poignée (433MHZ en version 2)
 *est réalisé par Régis LERUSTE http://fablabo.net/wiki/Utilisateur:LERUSTE_REGIS
 *et Olivier MARAIS http://fablabo.net/wiki/Cahier_de_recettes#Les_recettes_d.27Olivier
*ce programe e-p-wifi.ino constitue le code source qui permet l'édition, 
la compilation et le téléversement du firmware à destination du micro-contrôleur.
*L'environnement de développement Arduino IDE est constitué du microcontrôleur MKR wifi 1010 relié à l'ordinateur 
*à l'aide d'un câble USB. Ce câble permet l'établissement d'une liaison série. 
*De l'ordinateur vers le microcontrôleur pour téléverser le firmware. 
*Du microcontrôleur vers l'ordinateur pour l'envoi de messages à l'aide du port /dev/ttyACM0, 
*soit pour les afficher sur la console, 
*soit pour les mettre à disposition du programme BASH capture.sh qui édite un fichier "journal".   
*Le présent code source est publié sur Github sous licence creative commons CC-BY https://github.com/AIREL46/SCAO/blob/master/Arduino/e-p-433-v2/e-p-433-v2.ino
*L'objet du firmware est l'administration du microcontrôleur et de ses composants périphériques câblés selon le schéma électrique https://raw.githubusercontent.com/AIREL46/SCAO/master/kicad/e-p-433-v2/e-p-433-v2-1.png
*Son exécution par le microcontôleur est systématique dès son téléversement et ensuite à chaque mise sous tension. Il est organisé selon 2 fonctions principales : 
*- la capture des températures délivrées par 2 thermomètres digitaux, le premier concerne la température sur le couvercle de la casserole, le second la température de la batterie, l'une des fonctions secondaires qui assure la sécurité de la e-poignée. .
*- la transmission périodique de ces valeurs au e-rupteur (e-r-433).
*Ses fonctions principales sont complétées de fonctions secondaires (voir ci-dessous).
*Il utile des ressources extérieures (librairies, codes sources et exemples) développées par des informaticiens. 
*Chacun, des sous paragraphes ci-dessous, dédié à une fonction, cite, le nom de l'informaticien, indique les liens permettant d'accéder à la librairie ainsi qu'aux codes sources ou aux exemples.
 *
 * 1a - IHM wifi
 * 
 * 1b - IHM clavier
 * Acquisition des paramètres de cuisson
 * L'objet est l'acquisition des paramètres de cuisson saisis par l'utilisateur (setup).
 * La commande start stop permet le passage du setup à la boucle loop
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
 * Un cristal a été ajouté au Teensy 3.2.
 * La librarie Time apporte les fonctions spécifiques qui permettent de gérer cette fonction d'horodatage.
 * Cette Librarie a été développée par Michael Margolis, accesibles par les liens :
 *- https://www.pjrc.com/teensy/td_libs_Time.html
 *- https://github.com/PaulStoffregen/Time
 *- https://github.com/PaulStoffregen/Time/blob/master/examples/TimeTeensy3/TimeTeensy3.ino (pour la fonction RTC),
 *  accessible également dans l'Arduino IDE (Fichier - Exemples - Time - TimeTeensy3)
 *  TimeRTC.pde
 *  example code illustrating Time library with Real Time Clock.
 *  
 *  Chronomètre
 *  L'objet du chronomètre est la mesure du temps de travail du microcontrôleur.
 *  La librarie Chrono apporte les fonctions spécifiques qui permettent de gérer cette fonction.
 *  Cette Librarie a été développée par Sofian Audry and Thomas Ouellet Fredericks, elle est accesible par les liens :
 * - http://github.com/SofaPirate/Chrono
 * 
 * 1h Bilan énergétique de la batterie
 * L'objet est l'établissement du bilan énergétique de la batterie
 * Cette fonction réalise les calculs de l'énegie électrique consommée et le ratio par rapport à la capacité nominale de 400 mAh
 * 1i Calcul
 * 1j - Visualisation du contenu des échantillons
 *  * L'objet est la visualisation du contenu des échantillons.
 * Cette fonction utilise la liaison série (câble USB) entre le microcontrôleur et l'ordinateur.
 * Elle se concrétise par une console sur l'écran de l'ordinateur.
 * 1k - Mode Sleep
 * L'objet du mode sleep est l'économie d'énergie de la batterie.
 * - Colin Duffy, pour le "mode sleep" (snooze) avec la gestion de la liaison série, accesible par le lien : 
 *- https://github.com/duff2013/Snooze/blob/master/examples/deepsleep/deepSleep_usb_serial/deepSleep_usb_serial.ino
 *- https://github.com/duff2013/Snooze
 * 
 * 
 */
/**
 * 2 - Initialisation des paramètres
 * Paramètres communs
 */
 unsigned long tt1=0;//temps de travail 1
 unsigned long tt2=0;//temps de travail 2
 unsigned long ti=30000000;//temps itératif
 unsigned long ts=0;//temps de sleep
/**  
 * 2a - IHM wifi
 * 
 * 2b - IHM clavier
 * Les paramètres de cuisson sont la Durée de Cuisson (DC) et le Gabarit de cuisson (Gabarit).
 * DC est exprimée en mn sur 3 chiffres
 * Le Gabarit est un nombre entier compris entre 1 et 9.
 * Chaque Gabarit est associé à 9 paramètres :
 * la période (p), 
 * le gain (G),
 * l'Intensité de chauffe(I),
 * la température d'utilisation (Tu),
 * le temps de montée Tm (mn)
 * la constante de temps Tau (mn)
 * la vitesse de consigne Vc (°C/mn)
 * l'accélération de consigne Ac (°C/mn2)
 * la durée d'anticipation ta (nombre d'itérations).
 * Ces paramètres sont décrits dans le document "brevet" (page 6 et 28) dont la version Word est accessible par le lien ci-dessous:
 * https://github.com/AIREL46/SCAO/blob/master/Brevet/SCAO/word/La%20description%20du%20SCAO%20-%20d.doc
 * La commande start stop (stsp) permet de quitter le setup pour entrer dans la boucle loop 
 * Elle est commandée par un switch ON/OFF SW2 et elle se concrétise par une variable booléenne.
 * En position OFF, la variable est false correspondant à l'état stop.
 * En position ON, la variable est true correspondant à l'état start.
 * A l'état stop l'exécution du programme est maintenu dans une boucle de saisie du setup().
 * A l'état start l'exécution du programme transite dans la boucle loop().
 */
const int inPin_stsp = 1;    // SW2 connected to digital pin 2
bool val_stsp = false;//Création de la variable booléenne start stop (stsp)
//Création des tableaux (array) des gabarits de cuisson
float Gabarit1[] = {30, 0.4, 0.275, 70, 25, 30, 2, 1.0, 4};
float Gabarit2[] = {30, 0.4, 0.275, 72.5, 22.5, 28, 2.5, 1.25, 4};
float Gabarit3[] = {30, 0.4, 0.275, 75, 20, 24, 3, 1.5, 4};
float Gabarit4[] = {30, 0.4, 0.275, 77.5, 17.5, 22, 3.5, 1.75, 4};
float Gabarit5[] = {30, 0.4, 0.275, 80, 15, 20, 4, 2.0, 4};
float Gabarit6[] = {30, 0.4, 0.342, 82.5, 12.5, 18, 4.5, 2.25, 4};
float Gabarit7[] = {30, 0.4, 0.409, 85, 10, 16, 5, 2.5, 4};
float Gabarit8[] = {30, 0.4, 0.685, 87.5, 7.5, 14, 5.5, 2.75, 4};
float Gabarit9[] = {30, 0.4, 0.685, 90, 5, 12, 6, 3.0, 4};
//Création des variables "paramètres de cuisson"
int p; // période 
float G;
float I;
float Tu;
float Tm;
int Tau;
float Vc;
float A_c;
int ta;
//Création de la variable Durée de Cuisson (DC) et affectation d'une valeur par défaut
int DC = 100;
//Création de la variable Gabarit et affectation d'une valeur par défaut
int Gabarit = 5;
//Création de la variable flag dédiée à la saisie du N° de gabarit
int flag=1;
//Création du paramètre i correspondant au nombre de chiffres à saisir pour définir la durée de cuisson
int i=3;
int reponse;
 /** 
 * 2c - Acquisition des températures
 * Code pour lire un thermomètre digital DS18B20 sur un bus 1-Wire.
 */
 float T1;
 float T2;
/* Dépendance pour le bus 1-Wire */
#include <OneWire.h> //Chargement de la librairie OneWire.h
/* Broches des 2 bus 1-Wire */
const byte BROCHE_ONEWIRE_1 = 0;
const byte BROCHE_ONEWIRE_2 = 3;

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
const int Vbat_demie_1 = A0; //Initialisation de la variable Vbat_demie_1 et affectation à l'entrée analogique A0 (demie valeur de la tension Vbat avant la résistance de 1 Ohm)
const int Vbat_demie_2 = A1; //Initialisation de la variable Vbat_demie_2 et affectation à l'entrée analogique A1 (demie valeur de la tension Vbat après la résistance de 1 Ohm)
float Vbat_1; //Initialisation de la variable Vbat_1 (valeur de la tension Vbat avant la résistance de 1 Ohm)
float Vbat_2; //Initialisation de la variable Vbat_2 (valeur de la tension Vbat après la résistance de 1 Ohm)
float ibat; //Initialisation de la variable ibat (valeur du courant qui traverse la résistance de 1 Ohm)
const float Vbat_limite = 4300; //Limite supérieure de Vbat
const float Vbat_nominal = 3700; //Valeur nominale de Vbat
const float Vbat_min = 3600; //Valeur minimun de Vbat
const float Vbat_cut_off = 2800; //Cut off de Vbat
const int Vusb_demie = A2; //Initialisation de la variable Vusb_demie
float Vusb; //Initialisation de la variable Vusb
const int V33_demie = A3; //Initialisation de la variable V33_demie
float V33; //Initialisation de la variable V33
//Initialisation des valeurs utilisées par la fonction de changement d'échelle (fonction mathématique map() de l'arduino)
const int MaxConv = 8192; //Valeur maximale lue
const int MaxVolt = 3272; //Valeur de la tension correspondante à la valeur maximale
bool state_Vusb = false;
/**
 * 2e - Built In Test Equipment (BITE)
 *Les résultats du BITE sont visalisés par 3 leds :
verte : l'allumage témoigne d'un bon fonctionnement
        l'extinction peut être envisagée en mode sleep
jaune : allumée quand l'émission commence
        éteinte quand l'émission s'arrète
rouge : l'allumage témoigne d'une ou plusieurs anomalies
**/
const int led_pin_r = 5;//Led rouge
const int led_pin_j = 6;//Led jaune
const int led_pin_v = 7;//Led verte
 /** 2f - Transmission
 * Chargement de la librairie VirtualWire - Gestion de l'émetteur 433 MHZ
 **/
 
//#include <VirtualWire.h>
const int transmit_pin = 4;//Pin de sortie de l'émetteur
byte count = 0;//Initialisation du numéro du message 


/**
 * 2g - Horodatage & Chronomètre
 * Horodatage 
 **/
//#include "TimeLib.h" //Include TimeLib.h library
/**
 * Chronomètre 
  */
//#include <Chrono.h> //Include Chrono.h Library
//Chrono Chrono(Chrono::MICROS);//Instanciate a Chrono object
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
 * 2k Le mode sleep est commandé par un switch ON/OFF SW3, concrétisé par une variable booléenne et visualisé par une led violette,
en position OFF, la variable est false et la led est éteinte.
En position ON, la variable est true et la led est alluméee.

*/
const int led_pin_b = 4;//blue led connected to digital pin 4
const int inPin_sleep = 2;//SW3 connected to digital pin 1
bool val_sleep = false;//variable to store the read value
/**
 * Chargement de la librairie
 */
#include <ArduinoLowPower.h>
//#include <TimeLib.h>

/*#include <Snooze.h>
// Load timer and USBSerial drivers
SnoozeTimer timer;
SnoozeUSBSerial usb;*/

/***********************************************************
 Install drivers to a SnoozeBlock, timer to wake and USB Serial Driver to
 fix printing to serial monitor after sleeping.
 ***********************************************************/
/*SnoozeBlock config_teensy32(usb, timer);*/

/**
 * 3 - Fonctions spécifiques
 * Fonctions spécifiques communes
 * Wait for serial monitor
 * Clignotement rapide dans l'attente de l'établissement de la liaison série
 * L'interprétation de la condition : 
 * La liaison est établie -> le code n'est pas exécuté
 * La liaison n'est pas établie -> le code est exécuté pour une durée inférieure à la valeur indiquée par la variable time
 */
#include <digitalWriteFast.h>
   
 void wait_s_m(){
    int time = 0;
    while (!Serial && time < 1000) {
        mesures();//Lance la fonction mesures() pour connaitre l'état de Vusb (state_Vusb)
        if (!state_Vusb) {digitalWriteFast(led_pin_r, HIGH);}
        if (state_Vusb) {digitalWriteFast(led_pin_v, HIGH);}
        delay(30);
        if (!state_Vusb) {digitalWriteFast(led_pin_r, LOW);}
        if (state_Vusb) {digitalWriteFast(led_pin_v, LOW);}
        delay(30);
    }
    // normal delay for Arduino Serial Monitor
    delay(1200);
  }
 /**
 * 3a - IHM wifi
 * 
 * 3b - IHM clavier
 */
 void saisie(){Serial.println ("Systeme de Cuisson Assistee par Ordinateur (SCAO) ");
  //Saisie des paramètres de cuisson
  //Saisie de la duree de cuisson DC
  byte a; byte b; byte c; byte x=(15); 
  Serial.println ("Entrer DC (mn) sur 3 chiffres");
  while (i > 0) {
  switch (i) {
  case 3:
  if (Serial.available () > 0)  {a=Serial.read(); a=a&x; i=i-1; break;}
  case 2:
  if (Serial.available () > 0)  {b=Serial.read(); b=b&x; i=i-1; break;}
  case 1:
  if (Serial.available () > 0)  {c=Serial.read(); c=c&x; DC=(100*a+10*b+c); Serial.print (DC); Serial.println (" mn "); i=i-1; break;}
  default: {delay(1000);} 
    }//Switch
  } //While DC

  //Saisie du gabarit
  Serial.println ("Par defaut le gabarit est 5, voulez-vous le changer o/n ?");
   flag=1;
   while (flag>0) {if (Serial.available () > 0) {
   reponse=Serial.read();
   if (reponse==111 | reponse==79) {
   Serial.println ("Choisir le gabarit 1 -> 9 ");
   while (flag>0) {if (Serial.available () > 0) {
   reponse=Serial.read(); 
   Gabarit=reponse&x; 
   if (Gabarit > 0 & Gabarit <=9){flag=flag-1;}
   delay (1000);
 }//if serial.available b
 }//while
 }//if
   if (reponse==110 | reponse==78) {flag=flag-1;}
   delay (1000);
 }//if Serial.available a
 }//while
 
 //Visualisation DC et N° de gabarit
 Serial.print ("Duree de cuisson "), Serial.print (DC); Serial.println (" mn - ");
  //Visualisation des parametres correspondants au N° du gabarit choisi
  delay (1000);
  switch (Gabarit) {
  case 1: p=Gabarit1[0]; G=Gabarit1[1]; I=Gabarit1[2]; Tu=Gabarit1[3]; Tm=Gabarit1[4]; Tau=Gabarit1[5]; Vc=Gabarit1[6]; A_c=Gabarit1[7]; ta=Gabarit1[8];  break;
  case 2: p=Gabarit2[0]; G=Gabarit2[1]; I=Gabarit2[2]; Tu=Gabarit2[3]; Tm=Gabarit2[4]; Tau=Gabarit2[5]; Vc=Gabarit2[6]; A_c=Gabarit2[7]; ta=Gabarit2[8];  break;
  case 3: p=Gabarit3[0]; G=Gabarit3[1]; I=Gabarit3[2]; Tu=Gabarit3[3]; Tm=Gabarit3[4]; Tau=Gabarit3[5]; Vc=Gabarit3[6]; A_c=Gabarit3[7]; ta=Gabarit3[8];  break;
  case 4: p=Gabarit4[0]; G=Gabarit4[1]; I=Gabarit4[2]; Tu=Gabarit4[3]; Tm=Gabarit4[4]; Tau=Gabarit4[5]; Vc=Gabarit4[6]; A_c=Gabarit4[7]; ta=Gabarit4[8];  break;
  case 5: p=Gabarit5[0]; G=Gabarit5[1]; I=Gabarit5[2]; Tu=Gabarit5[3]; Tm=Gabarit5[4]; Tau=Gabarit5[5]; Vc=Gabarit5[6]; A_c=Gabarit5[7]; ta=Gabarit5[8];  break;
  case 6: p=Gabarit6[0]; G=Gabarit6[1]; I=Gabarit6[2]; Tu=Gabarit6[3]; Tm=Gabarit6[4]; Tau=Gabarit6[5]; Vc=Gabarit6[6]; A_c=Gabarit6[7]; ta=Gabarit6[8];  break;
  case 7: p=Gabarit7[0]; G=Gabarit7[1]; I=Gabarit7[2]; Tu=Gabarit7[3]; Tm=Gabarit7[4]; Tau=Gabarit7[5]; Vc=Gabarit7[6]; A_c=Gabarit7[7]; ta=Gabarit7[8];  break;
  case 8: p=Gabarit8[0]; G=Gabarit8[1]; I=Gabarit8[2]; Tu=Gabarit8[3]; Tm=Gabarit8[4]; Tau=Gabarit8[5]; Vc=Gabarit8[6]; A_c=Gabarit8[7]; ta=Gabarit8[8];  break;
  case 9: p=Gabarit9[0]; G=Gabarit9[1]; I=Gabarit9[2]; Tu=Gabarit9[3]; Tm=Gabarit9[4]; Tau=Gabarit9[5]; Vc=Gabarit9[6]; A_c=Gabarit9[7]; ta=Gabarit9[8];  break;
  }//switch
  Serial.print ("N° de gabarit choisi : ");  Serial.println(Gabarit); Serial.print("Ce gabarit correspond aux paramètres (p, G, I, Tu, Tm, Tau, Vc, Ac, ta) : ");
  Serial.print ("{");Serial.print (p); Serial.print (", "); Serial.print (G); Serial.print (", "); Serial.print (I); Serial.print (", "); Serial.print (Tu); Serial.print (", "); Serial.print (Tm); Serial.print (", "); Serial.print (Tau); Serial.print (", "); Serial.print (Vc); Serial.print (", "); Serial.print (A_c); Serial.print (", "); Serial.print (ta);Serial.println ("}");
  Serial.println ("Voulez-vous continuer ? taper O");
  flag=1;
  while (flag>0) {if (Serial.available() > 0)
    {reponse=Serial.read(); if (reponse==111 | reponse==79){flag=flag-1;}//Si le caractère frappé est O ou o
    
    }
  }
  }
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
  analogReadResolution(13);
  Vusb=map (2.0038*analogRead(Vusb_demie), 0, MaxConv, 0, MaxVolt);
  Vbat_1=map (2.0038*analogRead(Vbat_demie_1), 0, MaxConv, 0, MaxVolt);
  Vbat_2=map (2.0038*analogRead(Vbat_demie_2), 0, MaxConv, 0, MaxVolt);
  ibat=Vbat_1 - Vbat_2;
  V33=map (2.0038*analogRead(V33_demie), 0, MaxConv, 0, MaxVolt);
  if (Vusb < 1000) {state_Vusb = false;}
  if (Vusb > 4000) {state_Vusb = true;}
  }
 /** 
 * 3e - BITE
  **/
  
 /** 3f - Tranmission
 * 3g - Horodatage & Chronomètre
 **//*
 void digitalClockDisplay() {
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(";");
  Serial.print(day());
  Serial.print(";");
  Serial.print(month());
  Serial.print(";");
  Serial.print(year()); 
  Serial.print(";"); 
}

time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}

/*  code to process time sync messages from the serial port   */
/*
#define TIME_HEADER  "T"   // Header tag for serial time sync message

unsigned long processSyncMessage() {
  unsigned long pctime = 0L;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013 

  if(Serial.find(TIME_HEADER)) {
     pctime = Serial.parseInt();
     return pctime;
     if( pctime < DEFAULT_TIME) { // check the value is a valid time (greater than Jan 1 2013)
       pctime = 0L; // return 0 to indicate that the time is not valid
     }
  }
  Serial.println(pctime);
  return pctime;
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
*/
 /**
 * 3h - Bilan énergétique de la batterie
 * 3i - Calcul
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
  Serial.print(ibat);//Courant mesuré ibat en mA
  Serial.print(";");//Séparation des champs par une virgule
  Serial.print(V33);//Tension mesurée V33 en mV
  Serial.print(";");//Séparation des champs par une virgule
  Serial.println(Ec);//Energie mesurée Ec en joules
  delay(2000);
  }
 /**
 * 3k - Mode sleep
 * 
 */

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
  
  //4a - IHM wifi
  //4b - IHM clavier
  pinMode(inPin_stsp, INPUT);//sets the digital pin 2 as input
  if (state_Vusb) {saisie();}
  //char recu;
  //while (Serial.available() > 0) {recu = Serial.read(); Serial.print (recu); break;}
  while (!val_stsp) {
    val_stsp = digitalRead(inPin_stsp);
    Serial.print(val_stsp);
    Serial.println (" - attente de la cde start");
    digitalWrite(led_pin_v, HIGH);
    digitalWrite(led_pin_j, HIGH);
    digitalWrite(led_pin_r, HIGH);
    digitalWrite(led_pin_b, HIGH);
    delay(1000);
    digitalWrite(led_pin_v, LOW);
    digitalWrite(led_pin_j, LOW);
    digitalWrite(led_pin_r, LOW);
    digitalWrite(led_pin_b, LOW);
    delay(1000);
    }

  //4c - Acquisition des températures T1 et T2
  //4d - Mesure des tensions et calcul du courant ibat
  analogReadResolution(13);
  
  //4e - BITE
   
  //4f - Transmission
    // Initialise the IO and ISR

    
  //vw_set_tx_pin(transmit_pin);
  //vw_setup(2000);   // Bits per sec


  /*
  //4g - Horodatage & Chronomètre
  //setTime(16, 8, 00, 23, 02, 2019);
  // set the Time library to use Teensy 3.0's RTC to keep time
  setSyncProvider(getTeensy3Time); //Configure Time to automatically called the getTimeFunction() regularly. This function should obtain the time from another service and return a time_t number, or zero if the time is not known. 
  wait_s_m();//Wait for serial monitor 
  //while (!Serial);  // Wait for Arduino Serial Monitor to open
  delay(100);
  if (timeStatus()!= timeSet) {
    Serial.println("Unable to sync with the RTC");
  } else {
    Serial.println("RTC has set the system time");
  }
  */
  //4h - Bilan énergétique de la batterie
  //4i - calcul
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
}
 /** 5 - Fonction loop() **/
void loop() {
  //Chrono.restart();  // restart the Chrono 
  //5a - IHM wifi
  
  //5b - IHM clavier
    
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
      
  //5e - BITE
  float tmax=25;
  if (T2 >= tmax){digitalWrite(led_pin_r, HIGH);} else {digitalWrite(led_pin_r, LOW);}
  if (Vbat_2 <= Vbat_limite && Vbat_2 > Vbat_min){digitalWrite(led_pin_v, HIGH);} else {digitalWrite(led_pin_v, LOW);}
  //if (Vbat_2 > Vbat_limite || Vbat_2 <= Vbat_cut_off){digitalWrite(led_pin_r, HIGH);} else {digitalWrite(led_pin_r, LOW);}

  //5f - Transmission
  /* Transmission des donnèes à l'e-r-433 */ 
  /*La fonction de transmission vw_send(message, length) : transmit a message, "message" is an array of the bytes to send,
  and "length" is the number of bytes stored in the array.*/
  
  //char msg[7] = {'h','e','l','l','o',' ','#'};
  //msg[6] = count;  
  //time_t heure[1] = {now()};
  //float mesure[5]= {T1, T2, Vusb, Vbat_1, ibat};
  //unsigned long Energie[1] = {Ec};
  //digitalWrite(led_pin_j, HIGH); // Flash a light to show transmitting
  //vw_send((uint8_t *)msg, 7); //Transmission hello et count
  //vw_wait_tx(); // Wait until the whole message is gone
  //vw_send((uint8_t *)heure, 1); //Transmission de l'heure
  //vw_wait_tx(); // Wait until the whole message is gone
  //vw_send((uint8_t *)mesure, 5); //Transmission T1, T2, Vusb, Vbat, ibat
  //vw_wait_tx(); // Wait until the whole message is gone
  //vw_send((uint8_t *)Energie, 1); //Transmission de l'énergie consommée
  //vw_wait_tx(); // Wait until the whole message is gone
  //digitalWrite(led_pin_j, LOW);
  count = count + 1;
  //delay(100);


/*
  //5g - Horodatage & Chronomètre
  //time_t t = now();
    if (Serial.available() > 0) {
    time_t t = processSyncMessage();
    if (t != 0) {
      Teensy3Clock.set(t); // set the RTC
      setTime(t);
    }
  }
  */
 //5h - Bilan énergétique de la batterie
 //tt2 = (Chrono.elapsed());
 Et = ((Vbat_1/1000) * ibat)*((tt1 + tt2)/1000000);
 if (val_sleep) {Es = ((Vbat_1/1000) * 1.5)*(ts/1000000);}
 if (!val_sleep  ) {Es = ((Vbat_1/1000) * ibat)*(ts/1000000);}
 Etot = Et + Es;
 Ec = Ec + Etot;  

  //5i - Calcul
  //5j - Visualisation du contenu des échantillons
 //Appel de la fonction visu() si le Teensy 3.2 est connecté à l'ordinateur (reçoit du 5V) à l'aide d'un câble USB
  if (state_Vusb){visu();}
 
  //5k - Mode sleep

  val_sleep = digitalRead(inPin_sleep);   // read the input pin
  digitalWrite(led_pin_b, val_sleep);  // sets the LED to the switch's value
      /********************************************************
     Set Low Power Timer wake up in milliseconds.
     ********************************************************/
  //tt1 = (Chrono.elapsed());
  ts = ti - (tt1 + tt2);
  //timer.setTimer(ts/1000);// milliseconds
  delay(200);
  //if (val_sleep) {LowPower.idle( ts );}// return module that woke processor
  if (!val_sleep) {delay(ts/1000);}
  //Chrono.restart();  // restart the Chrono
  wait_s_m();//Wait for serial monitor 
  digitalWrite(led_pin_b, LOW);  // sets the blue LED to LOW
}
  
