//2 L'IHM
// Les paramètres de cuisson sont la Durée de Chauffe (DC1) et le Gabarit de cuisson (Gabarit).
// DC1 est exprimée en mn sur 3 chiffres
// Le Gabarit est un nombre entier compris entre 1 et 9.
// Chaque Gabarit est associé à 9 paramètres :
// la période (p),
// le gain (G),
// l'Intensité de chauffe(I),
// la température d'utilisation (Tu),
// le temps de montée Tm (mn)
// la constante de temps Tau (mn)
// la vitesse de consigne Vc (°C/mn)
// l'accélération de consigne A_c (°C/mn2)
// la durée d'anticipation ta (nombre d'itérations).
// Ces paramètres sont décrits dans le document "brevet" (page 6 et 28) dont la version Word est accessible par le lien ci-dessous:
// https://github.com/AIREL46/SCAO/blob/master/Brevet/SCAO/word/La%20description%20du%20SCAO%20-%20d.doc
//Initialisation des paramètres communs
#ifndef CONFIG_H
#define CONFIG_H
#include <Arduino.h>
//Communs 1 - Introduction
// 2 - Initialisation des paramètres
extern byte count;//Initialisation du numéro du message
extern float Tcons;//Température de consigne (trajectoire)
extern double t;//temps écoulé depuis le début de la cuisson
extern unsigned long tt1;//temps de travail 1
extern unsigned long tt2;//temps de travail 2
extern unsigned long ti;//temps itératif
extern unsigned long ts;//temps de sleep
//Création des tableaux (array) des gabarits de cuisson
extern float Gabarit1[];
extern float Gabarit2[];
extern float Gabarit3[];
extern float Gabarit4[];
extern float Gabarit5[];
extern float Gabarit6[];
extern float Gabarit7[];
extern float Gabarit8[];
extern float Gabarit9[];
//Création des variables "paramètres de cuisson"
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
extern bool FC2;//Création de la variable Fin de Cuisson (FC2)
extern int Gabarit;//Création de la variable Gabarit
//2 IHM clavier
//Initialisation des paramètres "clavier"
//Création de la variable flag dédiée à la saisie du N° de gabarit
//extern int flag;
//Création du paramètre i correspondant au nombre de chiffres à saisir pour définir la Durée de Chauffe
//extern int i;
//extern int reponse;
/*
* 3 - Communs - Fonctions spécifiques
*/
/*
* 4 - Communs - Fonction setup
*/
//digitalWrite(led_pin_r, HIGH);
void setup_communs();
/*
* 5 - Communs - Fonction loop
*/
#endif
