
/**
 * e-p-wifi.ino
 * Le présent code source est publié sur Github sous licence creative commons CC-BY
 * Voir -> https://github.com/AIREL46/SCAO/blob/master/Arduino/e-p-wifi/e-p-wifi.ino
 * Ce programme e-p-wifi.ino est dédié au microcontrôleur Arduino MKR wifi 1010 qui équipe la e-poignée du prototype N°3 intégrée dans le SCI.
 * voir ->  https://store.arduino.cc/mkr-wifi-1010
 * Pour mémoire, ce SCI (Système de Cuisson Intelligente) est composé principalement de 2 objets connectés et d'un smartphone.
 * (voir le schéma https://github.com/AIREL46/SCAO/raw/master/wiki/sci.png).
 * Le premier objet connecté est cette e-poignée et le second le e-rupteur.
 * Le microcontrôleur introduit la fonction de communication wifi qui offre à l'utilisateur la possibilité de piloter le SCI à partir du smartphone.
 * Ce programme est structuré en paragraphes :
 * 1 - Introduction
 * 2 - Initialisation des paramètres
 * 3 - Fonctions spécifiques
 * 4 - Fonction setup
 * 5 - Fonction loop
 * Chaque paragraphe est constitué de sous paragraphes correspondants à des modules logiciels distincts :
 * a) Les IHM (wifi et clavier)
 * b) Speaker
 * c) Acquisition des températures T1 et T2
 * d) Mesures des tensions
 * e) Built In Test Equipment (BITE)
 * f) Communication e-r-wifi
 * g) Horodatage et chronomètre
 * h) Bilan énergétique de la batterie
 * i) Régulation de la température
 * j) Visualisation du contenu des échantillons
 * k) Mode sleep
 * 1 - Introduction
 *Dans le cadre du concept culinaire Quiet cook
 *et de ce SCI https://fablabo.net/wiki/SCC.
 *Le prototypage (prototype N°3) de la e-poignée (en version wifi)
 *est réalisé par Régis LERUSTE http://fablabo.net/wiki/Utilisateur:LERUSTE_REGIS
 *et Olivier MARAIS http://fablabo.net/wiki/Cahier_de_recettes#Les_recettes_d.27Olivier
*ce programe e-p-wifi.ino constitue le code source qui permet l'édition,
la compilation et le téléversement du firmware à destination du micro-contrôleur.
*L'environnement de développement Arduino CLI est constitué du microcontrôleur MKR wifi 1010 relié à l'ordinateur
*à l'aide d'un câble USB. Ce câble permet l'établissement d'une liaison série.
*De l'ordinateur vers le microcontrôleur pour téléverser le firmware.
*Du microcontrôleur vers l'ordinateur pour l'envoi de messages à l'aide du port /dev/ttyACM0,
*soit pour les afficher sur le moniteur série,
*soit pour les mettre à disposition du programme Minicom qui réalise l'IHM entre le microcontrôleur et l'ordinateur et en option édite un fichier "journal".
*L'objet du firmware est l'administration du microcontrôleur et de ses composants périphériques câblés sur un shield selon les schéma électriques :
*Shield -> https://github.com/AIREL46/SCAO/blob/master/kicad/e-p-wifi-shield/e-p-wifi.png
*Son exécution par le microcontôleur est systématique dès son téléversement et ensuite à chaque mise sous tension.
*Il est organisé selon 2 fonctions principales :
*- la capture des températures délivrées par 2 thermomètres digitaux, le premier concerne la température sur le couvercle de la casserole, le second la température de la batterie, l'une des fonctions secondaires qui assure la sécurité de la e-poignée.
*- la commande ON/OFF du e-rupteur (relais Celduc).
*Ses fonctions principales sont complétées de fonctions secondaires (voir ci-dessous).
*Il utile des ressources extérieures (librairies, codes sources et exemples) développées par des dévoloppeurs (informaticiens).
*En application des règles de licences Creative commons, chacun, des sous paragraphes ci-dessous, dédié à une fonction, cite, le nom du développeur,
*indique les liens permettant d'accéder à la librairie ainsi qu'aux codes sources ou aux exemples.
*
* 1a IHM -> a_ihm.h
* 1b - Speaker -> b_speaker.h
* 1c - Acquisition des températures T1 et T2 -> c_acq_temp.h
* 1d - Mesure des tensions -> d_mes-tensions.h
* 1e - BITE -> e_bite.h
* 1f - Communication e-r-wifi -> f_communication.h
* 1g - Horodatage & Chronomètre -> g_horo_chrono.h
* 1h - Bilan énergétique -> h_bilan_eng.h
* 1i - Régulation de la température -> i_reg_temp.h
* 1j - Visualisation du contenu des échantillons -> j_visu_ech.h
* 1k - Mode Sleep -> k_sleep.h
*/
//2 - Initialisation des paramètres
 #include "1_communs.h"
 #include "1_def_mat.h"
//2a Les IHM -> a_ihm.h
 #include "a_ihm.h"
//2b Speaker -> b_speaker.h
 #include "b_speaker.h"
// 2c - Acquisition des températures
 #include "c_acq_temp.h"
//2d - Mesure des tensions et calcul du courant ibat
 #include "d_mes_tensions.h"
//2e - Built In Test Equipment (BITE)
 #include "e_bite.h"
 //2f - Communication e-r-wifi
 //2g - Horodatage & Chronomètre
 //Horodatage
 #include "g_wifi_rtc.h"
//#include "TimeLib.h" //Include TimeLib.h library
//Chronomètre
#include <Chrono.h> //Include Chrono.h Library
Chrono Chrono(Chrono::MICROS);//Instanciate a Chrono object
//2h - Bilan énergétique
#include "h_bilan_eng.h"
//2i Régulation de la température
#include "i_reg_temp.h"
//2j - Visualisation du contenu des échantillons
#include "j_visu_ech.h"
//2k mode sleep
bool val_sleep = false;//variable to store the read value
//3 Fonctions spécifiques
//Wait for serial monitor
  void wait_s_m(){
     int time = 0;
     while (!Serial && time < 1000) {
         mesures();//Lance la fonction mesures() pour connaitre l'état de Vusb (state_Vusb)
         if (!state_Vusb) {digitalWrite(led_pin_r, HIGH);}
         if (state_Vusb) {digitalWrite(led_pin_v, HIGH);}
         delay(300);
         if (!state_Vusb) {digitalWrite(led_pin_r, LOW);}
         if (state_Vusb) {digitalWrite(led_pin_v, LOW);}
         delay(300);
         time = time + 1;
     }
     // normal delay for Arduino Serial Monitor
     delay(1200);
   }

 //3a Les IHM -> a_ihm.h
 //3b Speaker -> b_speaker.h
 //3c - Fonction d'acquisition de la température via 2 thermomètres digitaux DS18B20.
 //3d - Mesure des tensions et calcul du courant ibat
 //3e - Built In Test Equipment (BITE)
 //3f Communication e-r-wifi
 //3g Horodatage et chronomètre
 //3h - Bilan énergétique
 //3h Bilan énergétique de la batterie
 //3i Régulation de la température -> i_reg_temp.h
 //3j - Visualisation du contenu des échantillons
 //3k Mode sleep
 //4 - Fonction setup()
void setup() {
  setup_communs();
  mesures();
  //Test des leds (mise sous tension)
  digitalWrite(led_pin_v, HIGH);
  digitalWrite(led_pin_j, HIGH);
  digitalWrite(led_pin_r, HIGH);
  digitalWrite(led_pin_b, HIGH);
  pinMode(led_pin_v, OUTPUT);
  pinMode(led_pin_j, OUTPUT);
  pinMode(led_pin_r, OUTPUT);
  pinMode(led_pin_b, OUTPUT);  // sets the digital pin 19 as output
  digitalWrite(led_pin_r, HIGH);//USB serial connection is not establihed - Clic on serial monitor icon (right top icon)
  wait_s_m();//Wait for serial monitor
  //while (!Serial);
    delay(100);
    digitalWrite(led_pin_r, HIGH);
    //Serial.println("Starting...");
    delay(100);
 // 4a Les IHM - Commun -> a_ihm.h
  setup_a ();
 //4b - Speaker -> b_speaker.h
  setup_b();
//4c - Acquisition des températures T1 et T2
//4d - Mesure des tensions
  setup_d();
//4e - Built In Test Equipment (BITE)
  setup_e();
  //4f Communication e-r-wifi
  //4g Horodatage et chronomètre
  //setup_g
  //setup_g();
  //4h - Bilan énergétique
  //4i Régulation de la température
  setup_i();
 //4j - Visualisation du contenu des échantillons
  setup_j();
 //4k - Mode sleep
  pinMode(inPin_sleep, INPUT);// sets the digital pin 10 as input
}
void loop() {
  Chrono.restart();
  digitalWrite(led_pin_v, HIGH);
  count = count +1;
//5a Les IHM
//5a-1 IHM wifi
//5a-2 IHM clavier
//5b - Speaker -> b_speaker.h
if (Dur > 0){
  beep(200);
  }
else {
  beep(5000);
  beep(5000);
  }
delay(1000);
//5c - Acquisition des températures T1 et T2
  // Lit la température T1
  if (getT1(&T1, true) != READ_OK) {
    Serial.println(F("Erreur de lecture du capteur"));
    return;
  }
  // Lit la température T2
  if (getT2(&T2, true) != READ_OK) {
    Serial.println(F("Erreur de lecture du capteur T2"));
    return;
  }

  //5d - Mesure des tensions et calcul du courant ibat
 mesures();

// 5e - Built In Test Equipment (BITE)
bite();
//5f - Communication e-r-wifi
//5g Horodatage et chronomètre
//5h - Bilan énergétique
//Table de Cuisson
if (Dur > 0){
som_dich = (double)som_dich + (double)Dich;
cout_total = (double)cout_total + ((double)cout_kwh * (((double)puissance) * ((double)Dich/3600)));
}
//5i Régulation de la température
reg_temp();
//5j - Visualisation du contenu des échantillons
//Appel de la fonction visu() si le MKR wifi 1010 est connecté à l'ordinateur (reçoit du 5V) à l'aide d'un câble USB
  //if (state_Vusb){visu_demo();}
  if (state_Vusb){visu_op();}
  if (!alarme_coupure_secteur) {
    t = (double)t + 0.5;//Incrémentation de la variable t
  }
//5k - Mode sleep
tt1 = Chrono.elapsed();
//Serial.print ("ti : ");
digitalWrite(led_pin_j, LOW);
digitalWrite(led_pin_b, HIGH);
//WiFi.lowPowerMode();
delay((ti - tt1)/1000);
//WiFi.noLowPowerMode();
digitalWrite(led_pin_b, LOW);
}
