/**
 * e-p-wifi.ino
 * Le présent code source est publié sur Github sous licence creative commons CC-BY
 * Voir -> https://github.com/AIREL46/SCAO/blob/master/Arduino/e-p-wifi/e-p-wifi.ino
 * Ce programme e-p-wifi.ino est dédié au microcontrôleur Arduino MKR wifi 1010 qui équipe la e-poignée du prototype N°3 intégrée dans le SCI.
 * voir ->  https://store.arduino.cc/mkr-wifi-1010
 * Pour mémoire, ce SCI (Système de Cuisson Intelligent) est composé principalement de 2 objets connectés et d'un smartphone.
 * (voir le schéma https://github.com/AIREL46/SCAO/raw/master/wiki/sci.png).
 * Le premier objet connecté est cette e-poignée et le second le e-rupteur (prise meross).
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
 #include "1_def_mat.h"
/*
 * 2a Les IHM -> a.h
 */
 #include "a_ihm.h"


// 2c - Acquisition des températures
 #include "c_acq_temp.h"

 /* 2d - Mesure des tensions et calcul du courant ibat
 */
 #include "d_mes_tensions.h"

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
*/
 #include "j_visu_ech.h"
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
 * 3c - Fonction d'acquisition de la température via 2 thermomètres digitaux DS18B20.
 */


  /**
 * 3d - Mesure des tensions et calcul du courant ibat
 */
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
  setup_d();
  // 4e - Built In Test Equipment (BITE)

 //4j - Visualisation du contenu des échantillons
 setup_j();
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
//Appel de la fonction visu() si le MKR wifi 1010 est connecté à l'ordinateur (reçoit du 5V) à l'aide d'un câble USB
  if (state_Vusb){visu();}
}
//5k - Mode sleep
