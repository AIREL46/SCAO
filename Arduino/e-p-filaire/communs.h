/*
* Communs
* 1 - Introduction
*/
/*
* 2 - Initialisation des paramètres
*/
#ifndef COMMUNS_H
#define COMMUNS_H
#include <Arduino.h>
extern byte count;//Initialisation du numéro du message
extern float Tcons;//Température de consigne (trajectoire)
extern double t;//temps écoulé depuis le début de la cuisson
extern unsigned long tt1;//temps de travail 1
extern unsigned long tt2;//temps de travail 2
extern unsigned long ti;//temps itératif
extern unsigned long ts;//temps de sleep
/*
* 3 - Fonctions spécifiques
*/
/*
* 4 - Fonction setup
*/
//digitalWrite(led_pin_r, HIGH);
void setup_communs();
/*
* 5 - Fonction loop
*/
#endif
