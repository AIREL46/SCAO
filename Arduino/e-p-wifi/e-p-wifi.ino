/**
 * e-p-wifi.ino
 * Ce programme e-p-wifi.ino résulte d'un portage informatique dû au remplacement du micrôcontrôleur Teensy 3.2 
 * par le micrôcontrôleur Arduino MKR wifi 1010 https://store.arduino.cc/mkr-wifi-1010. 
 * Ce nouveau microcontrôleur introduit la nouvelle fonction "IHM wifi" 
 * qui offre à l'utilisateur la possibilité de piloter l'application SCAO du prototype n°3 à partir d'un smartphone
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
 *et de son Système de Cuisson Assistée par Ordinateur (SCAO) http://fablabo.net/wiki/SCAO. 
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
*Le présent code source est publié sur Github sous licence creative commons CC-BY 
*https://github.com/AIREL46/SCAO/blob/master/Arduino/e-p-wifi/e-p-wifi.ino
*L'objet du firmware est l'administration du microcontrôleur et de ses composants périphériques câblés selon le schéma électrique :
*https://github.com/AIREL46/SCAO/raw/master/wifi/kicad/schema_electrique_e-p-433-wifi.png
*Son exécution par le microcontôleur est systématique dès son téléversement et ensuite à chaque mise sous tension. 
*Il est organisé selon 2 fonctions principales : 
*- la capture des températures délivrées par 2 thermomètres digitaux, le premier concerne la température sur le couvercle de la casserole, le second la température de la batterie, l'une des fonctions secondaires qui assure la sécurité de la e-poignée. .
*- la transmission périodique de ces valeurs au e-rupteur (e-r-433).
*Ses fonctions principales sont complétées de fonctions secondaires (voir ci-dessous).
*Il utile des ressources extérieures (librairies, codes sources et exemples) développées par des dévoloppeurs (informaticiens). 
*Chacun, des sous paragraphes ci-dessous, dédié à une fonction, cite, le nom du développeur, 
*indique les liens permettant d'accéder à la librairie ainsi qu'aux codes sources ou aux exemples.
*
***********
* Les IHM *
***********
 *
 *Définition des IHM et de leur fonction associée
 *En référence à Wikipédia, les IHM (Interactions Homme-machines) définissent les moyens mis en œuvre 
 *afin qu'un humain puisse contrôler et communiquer avec une machine.
 *Dans le cadre de ce projet, les moyens mis en œuvre sont soit ceux de l'ordinateur (clavier, souri, écran) ;
 *soit ceux du smartphone ; dans les deux cas, ils sont complétés par ceux propres du microcontrôleur, 
 *c'est à dire : 3 inverseurs ("ON/OFF" "sleep" et "start stop") et un jeu de leds.
 *Les IHM permettent de dialoguer avec le microcontrôleur, d'y introduire des données et de visualiser des résultats.
 *Ces IHM et leur fonction associée sont :
 * 1) le smartphone qui communique avec le microcontrôleur à l'aide de leur interface wifi respective, 
 *    ou l'ordinateur via son clavier qui communique avec le microcontrôleur à l'aide du moniteur série
 *    l'un ou l'autre permet la saisie des paramètres de cuisson par l'utilisateur et leur acquisition par le microcontrôleur.
 * 2) le moniteur série permet la visualisation du contenu des échantillons ainsi que les durées de cuisson (DC1 et DC2).
 * 3) le jeu de leds permet la visualisation des états de fonctionnement (BITE) 
 * 4) l'inverseur ON/OFF permet d'alimenter le microcontrôleur à partir de la batterie
 * 5) l'inverseur "sleep" à deux positions qui fournit deux états logiques (0 et 1) permet au microcontreur de fonctionner 
 *    selon l'un des deux modes : normal ou sleep
 * 6) l'inverseur "start stop" à deux positions fournit deux états logiques (0 et 1) interprétés lors du déroullement du firmware 
 *    de deux manières différentes liées à la fonction en cours d'exécution :
 *     - dans le cas de la fonction setup() la transition de 0 -> 1 lui permet de quitter cette même fonction pour transiter vers la fonction loop()
 *     - dans le cas de la fonction loop() la transition de 1 -> 0 lui permet d'inhiber l'autorisation de chauffe Ach.
 *Le code source des fonctions associées aux IHM se différencie en fonction du moyen de communication mis en œuvre, 
 *smartphone ou ordinateur, dans la suite du programme, l'un et l'autre se distinguent par l'appellation "wifi" ou "clavier".
 * 
 * 1a Les IHM
 * 1a-1 Le code source des IHM en mode "wifi"
 * Le code source des IHM en mode "wifi" s'inspire de l'exemple Arduino "simple web server" SimpleWebServerWiFi.ino 
 * associé au fichier arduino_secrets.h qui permet de gérer le nom du réseau wifi ainsi que le mot de passe pour y accéder
 * Le programme SimpleWebServerWiFi.ino a été conçu pour allumer ou èteindre une led?
 * Un serveur Web permet de communiquer les paramètres de cuisson via le Web. 
 * Le principe est basé sur la connection au serveur wifi "freebox_a3c" de la Freebox puis à la création d'une page web
 * dont l'adresse IP est imprimé sur le moniteur série. 
 * A partir du navigateur Web, d’un ordinateur ou d’un smartphone,  
 * ouvrir cette adresse IP : http: // « adresse IP » / cde 
 * Où « cde » est la commande à transmettre variable en fonction du contexte.
 * Les libraries utilisées sont :
 * - SPI allows to communicate with SPI (Serial Peripheral Interface) devices, with the Arduino as the master device.
 * - WiFiNINA allows to use the Arduino MKR 1010 capabilities.
 * - RTCZero allows to use the RTC functionalities for MKR1000
 * La fonction client.print() permet d'envoyer au smarphone via le serveur Web du code HTML, par exemple :
 * client.print("<!DOCTYPE html>");
 * 
 * 1a-2 - Le code source des IHM en mode "clavier"
 * Le code source des IHM en mode "clavier" utilise principalement des fonctions de la librarie Arduino 
 * qui permettent d'accéder au buffer de la liaison série :
 * - Serial.available() permet de connaître le nombre de caractères disponibles dans le buffer de la liaison série
 * - Serial.read() permet de lire le caractère disponible (utilisée pour lire le gabarit)
 * - Serial.parseInt() permet de lire plusieurs nombres entiers saisis l'un à la suite de l'autre 
 *   (utilisée pour lire la Durée de Cuisson (DC)).
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
/*
 * 2a Les IHM
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
 * l'accélération de consigne A_c (°C/mn2)
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
 //Initialisation des paramètres communs
const int inPin_stsp = 1;    // SW2 connected to digital pin 1
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
int p;//période 
float G;//Gain
float I;//Intensité
float Tu;//Température d'utilisation
float Tm;//Temps de montée
int Tau;//Tau
float Vc;//Vitesse de consigne
float A_c;//Accélération de consigne
int ta;//temps d'anticipation
//Création de la variable Durée de Cuisson (DC)
int DC;
//Création de la variable Gabarit
int Gabarit;

/*
 * 2a-1 IHM WiFi
 */

#include <SPI.h> //allows to communicate with SPI (Serial Peripheral Interface) devices, with the Arduino as the master device.
#include <WiFiNINA.h> //allows to use the Arduino MKR 1010 capabilities.
#include "arduino_secrets.h"
#include <RTCZero.h> //allows to use the RTC functionalities for MKR1000

RTCZero rtc; //Create an rtc object

String gabarit_url = "GET /?g=";
String time_url = "&t=";
String check_gabarit;
String get_gabarit;
String get_time;

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                // your network key Index number (needed only for WEP)

int led =  LED_BUILTIN;
int status = WL_IDLE_STATUS;
WiFiServer server(80);

 /*
  * 2a-2 IHM clavier
  */
//Initialisation des paramètres "clavier"
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
 
const int Vbat_demie_1 = A3; //Initialisation de la variable Vbat_demie_1 et affectation à l'entrée analogique A0 (demie valeur de la tension Vbat avant la résistance de 1 Ohm)
const int Vbat_demie_2 = A2; //Initialisation de la variable Vbat_demie_2 et affectation à l'entrée analogique A1 (demie valeur de la tension Vbat après la résistance de 1 Ohm)
float Vbat_1; //Initialisation de la variable Vbat_1 (valeur de la tension Vbat avant la résistance de 1 Ohm)
float Vbat_2; //Initialisation de la variable Vbat_2 (valeur de la tension Vbat après la résistance de 1 Ohm)
float ibat; //Initialisation de la variable ibat (valeur du courant qui traverse la résistance de 1 Ohm)
const float Vbat_limite = 4300; //Limite supérieure de Vbat
const float Vbat_nominal = 3700; //Valeur nominale de Vbat
const float Vbat_min = 3600; //Valeur minimun de Vbat
const float Vbat_cut_off = 2800; //Cut off de Vbat*/
const int Vusb_demie = A1; //Initialisation de la variable Vusb_demie
float Vusb; //Initialisation de la variable Vusb
const int V33_demie = A0; //Initialisation de la variable V33_demie
float V33; //Initialisation de la variable V33
//Initialisation des valeurs utilisées par la fonction de changement d'échelle (fonction mathématique map() de l'arduino)
const int MaxConv = 4095; //Valeur maximale lue
const int MaxVolt = 3300; //Valeur de la tension correspondante à la valeur maximale

bool state_Vusb = false;

/*
 * 2e - Built In Test Equipment (BITE)
 */

 const int led_pin_r = 7;//Led rouge
 const int led_pin_j = 6;//Led jaune
 const int led_pin_v = 5;//Led verte

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
 
 const int led_pin_b = 19;//blue led connected to digital pin 19
 const int inPin_sleep = 2;//SW3 connected to digital pin 2
bool val_sleep = false;//variable to store the read value


 /*
  * 3 - Fonctions spécifiques
  */
/*
 //#include <digitalWriteFast.h> Non supporter par le MKR WiFi 1010
   */
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
   * 3a Les IHM - Fonctions spécifiques communes
   */
   //F1 - Visualisation DC et N° de gabarit
  void visu_DC_G() {
  Serial.print ("Duree de cuisson "), Serial.print (DC); Serial.println (" mn - ");
  //Visualisation des parametres correspondants au N° du gabarit choisi
  delay (1000);
  //Affectation des paramètres de cuisson en fonction du gabarit choisi
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
  }
 /*
   * 3a-1 IHM WiFi - Fonstions spécifiques wifi
   * Les fonctions sont les suivantes :
   * F1-printWiFiStatus()
   * F2-setup_wifi()
   * F3-saisie_wifi()
   * 
   */
//F1-printWiFiStatus()
void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  
  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}

//F2-setup_wifi()
  void setup_wifi() {
 rtc.begin();//Initializes the internal RTC.
 
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < "1.0.0") {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.print(ssid);                   // print the network name (SSID);
    Serial.println (" (10 secondes d'attente)");
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }
  server.begin();                           // start the web server on port 80
  printWiFiStatus();                        // you're connected now, so print out the status
  }
  
//F3-saisie_wifi() - Saisie des paramètres de cuisson en wifi
 // compare the previous status to the current status
  void saisie_wifi() {
  IPAddress ip = WiFi.localIP();
  Serial.print("Choisir gabarit et DC en ouvrant à l'aide du navigateur une fenêtre à l'adresse http://");
  Serial.print (ip);
  Serial.println (" puis valider stsp.");
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Quiet cook");
            client.print("<br>");
            //client.print("<center><img srcset=images/quietcook-01.jpg></center>");
            client.print("<form method='get'>");//Tells the browser how to send form data to a web server.
            client.print("<select name=g required>");//The HTML <select> name Attribute is used to specify a name for the drop-down list.
            client.print("<option value='0'>Select a Gabarit</option>");//Defines the data sent to the server when a form option item is selected.
            client.print("<option value='1'>Gabarit 1</option>");
            client.print("<option value='2'>Gabarit 2</option>");
            client.print("<option value='3'>Gabarit 3</option>");
            client.print("<option value='4'>Gabarit 4</option>");
            client.print("<option value='5'>Gabarit 5</option>");
            client.print("<option value='6'>Gabarit 6</option>");
            client.print("<option value='7'>Gabarit 7</option>");
            client.print("<option value='8'>Gabarit 8</option>");
            client.print("<option value='9'>Gabarit 9</option></select><br>");
            client.print("<br>");
            client.print("<br>");
            client.print("<br>");
            client.print("<input type='number' name='t'>DC(mn)<br>");//Defines the input type.
            client.print("<input type='submit' value='Submit'></form>");
            client.print(Gabarit);
            client.print("<br>");
            client.print(DC);
            client.print("<br>");
            client.print(get_gabarit);
            client.print("<br>");
            client.print(get_time);
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
        // Check to see the client request
       
         int x=0;

         while(x!=10){
            check_gabarit = gabarit_url + x;
            //Tests whether or not a String ends with the characters of another String.
            if(currentLine.endsWith(check_gabarit)){
                Gabarit = x;
                get_gabarit = gabarit_url + Gabarit;//Par exemple si le gabarit est 5 : GET/?=5
                
              }
              x++;
          }
        
        int i=0;
            
        while(i!=1000){
          get_time = (get_gabarit + time_url) + i;//Par exemple si le gabarit est 5 et la durée 60 mn : GET/?=5&t=60
          if(currentLine.endsWith(get_time)){
            DC = i;
            break;
          }
          i++;
        }
      }//if (client.available())
    }//while (client.connected())
    // close the connection:
    //printWiFiStatus();
    client.stop();
    visu_DC_G();
    Serial.println("client disonnected");
  }//if (client)
}//saisie_wifi()

/*
 * 3a-2 IHM clavier
 */
 
 //F1 - Fonction spécifique de saisie en mode "clavier"
 void saisie(){
  //Saisie des paramètres de cuisson
  //Saisie de la duree de cuisson DC
  byte x=(15); 
  Serial.println ("Entrer DC (mn) sur 3 chiffres");
  bool bidon = true;
  while (bidon) {while (Serial.available () > 0) DC = Serial.parseInt(); if (DC>0) bidon=false;}
  Serial.print (DC);
  Serial.println (" mn ");
  delay(1000);
  //Saisie du gabarit
  Gabarit=5;
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
 
  Serial.println ("Voulez-vous continuer ? taper O");
  flag=1;
  while (flag>0) {if (Serial.available() > 0)
    {reponse=Serial.read(); if (reponse==111 | reponse==79){flag=flag-1;}//Si le caractère frappé est O ou o
    
    }
  }
  }
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
   * 4a Les IHM - Commun
   */
   //sets the digital pin 1 as input (SW2)
  pinMode(inPin_stsp, INPUT);
  
  //Choix de la fonction de saisie (wifi ou clavier)
  Serial.println ("Systeme de Cuisson Assistee par Ordinateur (SCAO) ");
  Serial.println("Saisie wifi (O) ou clavier (N)");
  bool wifi_clavier;
  flag=1;
  while (flag>0) {if (Serial.available() > 0)
    {reponse=Serial.read(); if (reponse==111 | reponse==79){flag=flag-1; wifi_clavier = true;}//Si le caractère frappé est O ou o
    else {flag=flag-1; wifi_clavier = false;}
    }
  }
  delay(2000);
  
  //Appel de la fonction "saisie clavier"
  if (state_Vusb && !wifi_clavier) {saisie();}
  
  //Appel du setup et de la fonction de saisie wifi
  if (wifi_clavier) {setup_wifi();}
  while (!val_stsp && wifi_clavier) {saisie_wifi(); val_stsp = digitalRead(inPin_stsp); delay(1000);}

  //Appel de la fonction visu_DC_G()
  visu_DC_G();
  
  /*   
   * 4a-1 IHM wifi : Vide
   */

  /*
   * 4a-2 IHM clavier
   */
    
  //Boucle d'attente de la commande stsp
  //Les 4 leds clignotent
  //Dès que le switch (SW2) stsp est en position active val_stsp est "true"
  //le progamme quitte la fonction setup pour entrer dans la fonction loop
  while (!val_stsp) {
    val_stsp = digitalRead(inPin_stsp);
    Serial.print(val_stsp);
    Serial.println (" - attente de la cmd start");
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
