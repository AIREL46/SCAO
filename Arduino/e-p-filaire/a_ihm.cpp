#include <Arduino.h>
#include "a_ihm.h"
#include "def_mat.h"
// 3a L'IHM - Fonctions spécifiques
//F1 - Visualisation DC1 et N° de gabarit
// =======================
// Switch case
// =======================
float* getGabarit(int g) {
  switch (g) {
    case 1: return Gabarit1;
    case 2: return Gabarit2;
    case 3: return Gabarit3;
    case 4: return Gabarit4;
    case 5: return Gabarit5;
    case 6: return Gabarit6;
    case 7: return Gabarit7;
    case 8: return Gabarit8;
    case 9: return Gabarit9;
    default: return Gabarit5;
  }
}
// =======================
// Visualisation de DC1 et du numéro de gabarit
// =======================
void visu_DC_G() {
  Serial.print("Duree de cuisson : ");
  Serial.print(DC1);
  Serial.println(" mn");
  float* g = getGabarit(Gabarit);
  p   = g[0];
  G   = g[1];
  I   = g[2];
  Tu  = g[3];
  Tm  = g[4];
  Tau = g[5];
  Vc  = g[6];
  A_c = g[7];
  ta  = g[8];
  Serial.print("Gabarit choisi : ");
  Serial.println(Gabarit);
}

  //F2 - Clignotements des 4 leds
  void cli_4leds() {
    digitalWrite(led_pin_v, HIGH);
    digitalWrite(led_pin_j, HIGH);
    digitalWrite(led_pin_r, HIGH);
    digitalWrite(led_pin_b, HIGH);
    delay(500);
    digitalWrite(led_pin_v, LOW);
    digitalWrite(led_pin_j, LOW);
    digitalWrite(led_pin_r, LOW);
    digitalWrite(led_pin_b, LOW);
    delay(500);
    }
 
/*
 * 3a-2 IHM clavier
 */

 //F1 - Fonction spécifique de saisie en mode "clavier"
  //Saisie des paramètres de cuisson
  //Saisie de la duree de cuisson DC1
// =======================
// Saisie clavier
// =======================
long lireEntier(long minVal, long maxVal) {
  long val = 0;
  while (true) {
    if (Serial.available()) {
      val = Serial.parseInt();
      if (val >= minVal && val <= maxVal) {
        return val;
      }
      Serial.println("Valeur invalide");
    }
  }
}
void saisie() {
  Serial.println("Entrer la duree de cuisson (de 1 à 999 mn)");
  DC1 = lireEntier(1, 999);
  Serial.println("Choisir le gabarit (1-9)");
  Gabarit = lireEntier(1, 9);
}
   /*
   * 4a Les IHM - Commun
   */
// =======================
// Setup IHM
// =======================
void setup_a() {
  Serial.println("Systeme de Cuisson Intelligente");
  if (Serial) {
    saisie();
  }
  visu_DC_G();
}
  /*
   * 4a-1 IHM wifi : Vide
   */

  /*
   * 4a-2 IHM clavier : vide
   */
