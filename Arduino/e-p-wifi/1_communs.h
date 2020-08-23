/*
* Communs
* 1 - Introduction
*/
/*
* 2 - Initialisation des paramètres
*/
byte count = 0;//Initialisation du numéro du message
float Tcons=0;//Trajectoire
double t=0.5;//temps écoulé depuis le début de la cuisson
unsigned long tt1=0;//temps de travail 1
unsigned long tt2=0;//temps de travail 2
unsigned long ti=30000000;//temps itératif
unsigned long ts=0;//temps de sleep
/*
* 3 - Fonctions spécifiques
*/

/*
* 4 - Fonction setup
*/
//digitalWrite(led_pin_r, HIGH);
void setup_communs() {
  Serial.println ("Bonjour");
  
}
/*
* 5 - Fonction loop
*/
