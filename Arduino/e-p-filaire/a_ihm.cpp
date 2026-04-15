#include "a_ihm.h"
   * 3a L'IHM - Fonctions spécifiques
   */
   //F1 - Visualisation DC1 et N° de gabarit
  void visu_DC_G() {
  Serial.print("Duree de cuisson ");
  Serial.print(DC1);
  Serial.println(" mn - ");
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
