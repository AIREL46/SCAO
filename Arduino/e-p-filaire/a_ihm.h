/*
*****************
* L'IHM clavier *
*****************
 *
 *Définition de l'IHM clavier et de ses fonctions associées
 *En référence à Wikipédia, les IHM (Interactions Homme-machines) définissent les moyens mis en œuvre
 *afin qu'un humain puisse contrôler et communiquer avec une machine.
 *Dans le cadre de ce projet, les moyens mis en œuvre sont soit ceux de l'ordinateur (clavier, souri, écran) ;
 *qui sont complétés par ceux propres du microcontrôleur, un jeu de leds montés sur le shield.
 *L'IHM permet de dialoguer avec le microcontrôleur, d'y introduire des données et de visualiser des résultats.
 *L'IHM et ses fonctions associées sont :
 * 1) le moniteur série qui permet la visualisation du contenu des échantillons ainsi que les durées de cuisson (DC1 et DC2).
 * 2) le jeu de leds permet la visualisation des états de fonctionnement (BITE)
 * 3) le code source des IHM en mode "clavier" utilise principalement des fonctions de la librarie Arduino
 * qui permettent d'accéder au buffer de la liaison série :
 * - Serial.available() permet de connaître le nombre de caractères disponibles dans le buffer de la liaison série
 * - Serial.read() permet de lire le caractère disponible (utilisée pour lire le gabarit)
 * - Serial.parseInt() permet de lire plusieurs nombres entiers saisis l'un à la suite de l'autre
 *   (utilisée pour lire la Durée de Chauffe (DC1)).
 */
#ifndef A_IHM_H
#define A_IHM_H
#include <Arduino.h>
// extern variables Gabarit
extern float Gabarit1[];
extern float Gabarit2[];
extern float Gabarit3[];
extern float Gabarit4[];
extern float Gabarit5[];
extern float Gabarit6[];
extern float Gabarit7[];
extern float Gabarit8[];
extern float Gabarit9[];
// extern variables "paramètres de cuisson"
extern int p;//période
extern float G;//Gain
extern float I;//Intensité
extern float Tu;//Température d'utilisation
extern double Tm;//Temps de montée
extern int Tau;//Tau
extern float Vc;//Vitesse de consigne
extern float A_c;//Accélération de consigne
extern int ta;//temps d'anticipation
extern long DC1;//Création de la variable Durée de Chauffe (DC1)
extern long DC2;//Création de la variable Durée de Cuisson (DC2)
extern bool FC1;//Création de la variable Fin de Chauffe (FC1)
extern bool FC2;//variable Fin de Cuisson (FC2)
extern int Gabarit;//variable Gabarit
// 3a L'IHM - Fonctions spécifiques
//F1 - Visualisation DC1 et N° de gabarit
  void visu_DC_G();
    //F2 - Clignotements des 4 leds
  void cli_4leds();
  /*
 * 3a-2 IHM clavier
 */

 //F1 - Fonction spécifique de saisie en mode "clavier"
 void saisie();
    /*
   * 4a Les IHM - Commun
   */
 void setup_a ();
   /*
   * 4a-1 IHM wifi : Vide
   */

  /*
   * 4a-2 IHM clavier : vide
   */
#endif
