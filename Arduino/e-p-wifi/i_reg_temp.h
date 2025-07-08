/*
* 1i Régulation de la température
*/
/*
* 2i Régulation de la température
*/
# include <math.h>
int phase;//Initialisation de la variable phase
float Tinit;//Initialisation de la variable Température initiale
float T10pc;//Initialisation de la variable Température T10%
float T98pc;//Initialisation de la variable Température T98%
bool inter98pc;//Initialisation de la variable intersection T98%
float Dich;//Initialisation de la variable Durée itérative de chauffe
float ecart;//Initialisation de la variable écart
float Correction;//Initialisation de la variable Correction
double Dur;//Initialisation de la variable Durée de chauffe restante
double Dur_ph1;//Durée restante en phase 1
double Dur_ph2;//Durée restante en phase 2
double Dur_ph3;//Durée restante en phase 3
double Dur_ph4;//Durée restante en phase 4
double t_deb_cuisson;//Initialisation de la variable temps nécessaire pour atteindre la température de début de cuisson
bool Ach = false;//Initialisation de la variable Autorisation de chauffe

/*
* 3i Régulation de la température
*/
void reg_temp() {
  //Positionnement de l'Autorisation de chauffe
  if (Dur > 0 && !alarme_temperature_bat && !alarme_Vbat_2 && !alarme_Vusb && !alarme_V33 && !alarme_coupure_secteur) {Ach = true;}
  else {Ach = false;}
  //Calcul de la température de consigne (Tcons)
  if (Ach) {
    if (Dur_ph1 > 0) {
      Tcons = Tinit + ((T10pc - Tinit)/Tm)*t;
      Dur_ph1 = (double)Dur_ph1 - 0.5;//Décrémentation de durée  restante en phase 1
      phase = 1;
      if (Dur_ph1 == 0) {
        t = (double)0.0;
      }//la phase 1 est terminée, alors réinitialiser t à la valeur zéro
    }
    else {
      Tcons = Tinit + (T10pc - Tinit) + (Tu-T10pc)*(1-exp(-(double)t/Tau));//Calcul de la température de consigne (trajectoire de référence) à partir de la phase 2

    }
  }
  ecart = Tcons - T2;//Calcul de l'écart de température entre la trajectoire de référence et la trajectoire réelle
  Correction = ecart*G;//Calcul de la Correction
  digitalWrite(led_pin_v, LOW);
  if (Ach) {
  //Calcul de la Durée itérative de chauffe
  if (Correction <= 0) {Dich = 0;}
  if (Correction > 0 && Correction > 1) {Dich = p*I;}
  if (Correction > 0 && Correction < 1) {Dich = p*I*Correction;}
  //Réglage du flux thermique de la table de cuisson à l'aide de l'actionneur (relai)
    digitalWrite(led_pin_j, HIGH);
    digitalWrite(relay, HIGH);//Application de la tension 230VAC sur la table de cuisson
    delay((Dich*1000)/2);//Maintien sous tension 230VAC de la table de cuisson (première moitiè)
    courant = (analogRead(itc)*42.04*0.826)/5000;//Conversion analogique/digitale de la valeur délivrée par le module phidgets 1122
    Serial.print("courant : ");
    Serial.println(courant);
    delay((Dich*1000)/2);//Maintien sous tension 230VAC de la table de cuisson (seconde motiée)
    digitalWrite(relay, LOW);//Coupure de la tension 230VAC de la table de cuisson
    Dur = (double)Dur - 0.5;//Décrémentation de la Durée de chauffe restante
  }
  else {
    Dich = 0;
    courant = 0;
  }
  if (T10pc > T2 > T98pc){
    phase = 2;
  }
  if ((T2 > T98pc) && (!inter98pc)) {
    inter98pc = true;
    phase = 3;
  }
  if (Dur <= 0) {
    FC1 = true;//Fin de Chauffe
    phase = 4;
  }
}
/*
* 4i Régulation de la température
*/
void setup_i() {
  pinMode (relay, OUTPUT);
  inter98pc = false;//Initialisation de la variable inter98pc à false
  //Mesure et mémorisation de la température initiale sur le couvercle de la casserole
  if (getT2(&T2, true) != READ_OK) {
    Serial.println(F("Erreur de lecture du capteur T2"));
    return;
  }
  Tinit = T2;//Température initiale
  Tcons = Tinit;//Initialisation de la température de consigne
  if (Tinit < 55) {
    t_deb_cuisson = -(Tau*log(1-((55-Tinit)/(Tu-Tinit))));//Calcul théorique du temps nécessaire pour atteindre le début de cuisson
    Dur = DC1 + t_deb_cuisson + Tm;//Calcul de la durée de cuisson restante
  }
  else {
    Dur = DC1;//Calcul de la durée de cuisson restante
  }
  T10pc = Tinit + 0.1 * (Tu - Tinit);
  Dur_ph1 = Tm;//Intialisation de la durée testante en phase 1 à la valeur de Tm
  T98pc = Tinit + 0.98 * (Tu - Tinit);
}
/*
* 5i Régulation de la température
*/
