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

/*
 * 2 L'IHM
 * Les paramètres de cuisson sont la Durée de Chauffe (DC1) et le Gabarit de cuisson (Gabarit).
 * DC1 est exprimée en mn sur 3 chiffres
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
 //Initialisation des paramètres communs
#include <Arduino.h>
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
double Tm;//Temps de montée
int Tau;//Tau
float Vc;//Vitesse de consigne
float A_c;//Accélération de consigne
int ta;//temps d'anticipation
long DC1;//Création de la variable Durée de Chauffe (DC1)
long DC2;//Création de la variable Durée de Cuisson (DC2)
bool FC1 = false;//Création de la variable Fin de Chauffe (FC1)
bool FC2 = false;//Création de la variable Fin de Cuisson (FC2)
int Gabarit;//Création de la variable Gabarit
/* 2 IHM clavier
*/
//Initialisation des paramètres "clavier"
//Création de la variable flag dédiée à la saisie du N° de gabarit
int flag=1;
//Création du paramètre i correspondant au nombre de chiffres à saisir pour définir la Durée de Chauffe
int i=3;
int reponse;

  /*
   * 3a L'IHM - Fonctions spécifiques
   */
   //F1 - Visualisation DC1 et N° de gabarit
  void visu_DC_G() {
  Serial.print ("Duree de cuisson "), Serial.print (DC1); Serial.println (" mn - ");
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
  Serial.print ("Le gabarit choisi est : ");  Serial.println(Gabarit); //Serial.print("Ce gabarit correspond aux paramètres (p, G, I, Tu, Tm, Tau, Vc, Ac, ta) : ");
  //Serial.print ("{");Serial.print (p); Serial.print (", "); Serial.print (G); Serial.print (", "); Serial.print (I); Serial.print (", "); Serial.print (Tu); Serial.print (", "); Serial.print (Tm); Serial.print (", "); Serial.print (Tau); Serial.print (", "); Serial.print (Vc); Serial.print (", "); Serial.print (A_c); Serial.print (", "); Serial.print (ta);Serial.println ("}");
  }
  //F2 - Clignotements des 4 leds
  void cli_4leds() {
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
 
/*
 * 3a-2 IHM clavier
 */

 //F1 - Fonction spécifique de saisie en mode "clavier"
 void saisie(){
  //Saisie des paramètres de cuisson
  //Saisie de la duree de cuisson DC1
  byte x=(15);
  Serial.println ("Entrer la duree de cuisson (mn) > 0 (attention : apres la frappe du premier chiffre, vous avez 5 secondes pour saisir la valeur)");
  bool bidon = true;
  Serial.setTimeout(5000);//Laps de temps pour saisir la valeur
  while (bidon) {while (Serial.available () > 0) DC1 = Serial.parseInt(); if (DC1>0) bidon=false;}
  Serial.print (DC1);
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
   * 4a Les IHM - Commun
   */
 void setup_a () {
  //Message d'accueil
  Serial.println ("Systeme de Cuisson Intelligente (SCI) ");
  delay(2000);

  //Appel de la fonction "saisie clavier"
  //cette fonction est appellée si le moniteur série est connecté par l'intermédiaire du câble série entre l'ordinateur et la plateforme MKR wifi 1010
  //c'est la variable Serial qui atteste de cette connexion
  if (Serial) {saisie();}
  visu_DC_G();//Affiche la Durée de Chauffe et le contenu du gabarit sélectionnés par l'utilisateur
  }
  /*
   * 4a-1 IHM wifi : Vide
   */

  /*
   * 4a-2 IHM clavier : vide
   */
