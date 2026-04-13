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

