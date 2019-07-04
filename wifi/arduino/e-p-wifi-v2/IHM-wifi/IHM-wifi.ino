/*
 * 2 - Initialisation des paramètres
 */

 unsigned long tt1=0;//temps de travail 1
 unsigned long tt2=0;//temps de travail 2
 unsigned long ti=30000000;//temps itératif
 unsigned long ts=0;//temps de sleep

 /*
  * 2b - IHM clavier
  */

const int inPin_stsp = 1;    // SW2 connected to digital pin 1
bool val_stsp = false;//Création de la variable booléenne start stop (stsp)
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
int p; // période 
float G;
float I;
float Tu;
float Tm;
int Tau;
float Vc;
float A_c;
int ta;
//Création de la variable Durée de Cuisson (DC) et affectation d'une valeur par défaut
int DC = 100;
//Création de la variable Gabarit et affectation d'une valeur par défaut
int Gabarit = 5;
//Création de la variable flag dédiée à la saisie du N° de gabarit
int flag=1;
//Création du paramètre i correspondant au nombre de chiffres à saisir pour définir la durée de cuisson
int i=3;
int reponse;

 /** 
 * 2c - Acquisition des températures
 * Code pour lire un thermomètre digital DS18B20 sur un bus 1-Wire.
 */
 float T1;
 float T2;
/* Dépendance pour le bus 1-Wire */
#include <OneWire.h> //Chargement de la librairie OneWire.h
/* Broches des 2 bus 1-Wire */
const byte BROCHE_ONEWIRE_1 = 0;
const byte BROCHE_ONEWIRE_2 = 3;

/* Code de retour des 2 fonctions getT1() et getT2() */
enum DS18B20_RCODES {
  READ_OK,  // Lecture ok
  NO_SENSOR_FOUND,  // Pas de capteur
  INVALID_ADDRESS,  // Adresse reçue invalide
  INVALID_SENSOR  // Capteur invalide (pas un DS18B20)
};


/* Création des 2 objets OneWire pour manipuler les 2 bus 1-Wire */
OneWire ds1(BROCHE_ONEWIRE_1);
OneWire ds2(BROCHE_ONEWIRE_2);

/**
 * 2d - Mesure des tensions et calcul du courant ibat
 */
 
const int Vbat_demie_1 = A3; //Initialisation de la variable Vbat_demie_1 et affectation à l'entrée analogique A0 (demie valeur de la tension Vbat avant la résistance de 1 Ohm)
const int Vbat_demie_2 = A2; //Initialisation de la variable Vbat_demie_2 et affectation à l'entrée analogique A1 (demie valeur de la tension Vbat après la résistance de 1 Ohm)
float Vbat_1; //Initialisation de la variable Vbat_1 (valeur de la tension Vbat avant la résistance de 1 Ohm)
float Vbat_2; //Initialisation de la variable Vbat_2 (valeur de la tension Vbat après la résistance de 1 Ohm)
float ibat; //Initialisation de la variable ibat (valeur du courant qui traverse la résistance de 1 Ohm)
const float Vbat_limite = 4300; //Limite supérieure de Vbat
const float Vbat_nominal = 3700; //Valeur nominale de Vbat
const float Vbat_min = 3600; //Valeur minimun de Vbat
const float Vbat_cut_off = 2800; //Cut off de Vbat*/
const int Vusb_demie = A1; //Initialisation de la variable Vusb_demie
float Vusb; //Initialisation de la variable Vusb
const int V33_demie = A0; //Initialisation de la variable V33_demie
float V33; //Initialisation de la variable V33
//Initialisation des valeurs utilisées par la fonction de changement d'échelle (fonction mathématique map() de l'arduino)
const int MaxConv = 8192; //Valeur maximale lue
const int MaxVolt = 3272; //Valeur de la tension correspondante à la valeur maximale

bool state_Vusb = false;

/*
 * 2e - Built In Test Equipment (BITE)
 */

 const int led_pin_r = 7;//Led rouge
 const int led_pin_j = 6;//Led jaune
 const int led_pin_v = 5;//Led verte

 /** 2f - Transmission
 * Chargement de la librairie VirtualWire - Gestion de l'émetteur 433 MHZ
 **/
/* 
#include <VirtualWire.h>
const int transmit_pin = 4;//Pin de sortie de l'émetteur*/
byte count = 0;//Initialisation du numéro du message 


/**
 * 2g - Horodatage & Chronomètre
 * Horodatage 
 */

 /*
#include "TimeLib.h" //Include TimeLib.h library
/**
 * Chronomètre 
  */
#include <Chrono.h> //Include Chrono.h Library
Chrono Chrono(Chrono::MICROS);//Instanciate a Chrono object

/**
 * 2h - Bilan énergétique de la batterie
 * Chargement de la librairie
 */
unsigned long Etot=0; //Energie électrique totale consommée en joule
unsigned long Et=0; //Energie électrique consommée pendant le travail
unsigned long Es=0; //Energie électrique consommée pendant le sommeil (sleep)
unsigned long Ec=0; //Energie électrique consommée cumulée

/**
 * 2i Calcul
 */

/**
 * 2j - Visualisation du contenu des échantillons
/**

/*
 * 2k mode sleep
 */
 
 const int led_pin_b = 19;//blue led connected to digital pin 19
 const int inPin_sleep = 2;//SW3 connected to digital pin 2
bool val_sleep = false;//variable to store the read value


 /*
  * 3 - Fonctions spécifiques
  */
/*
 //#include <digitalWriteFast.h> Non supporter par le MKR WiFi 1010
   */
 void wait_s_m(){
    int time = 0;
    while (!Serial && time < 1000) {
        mesures();//Lance la fonction mesures() pour connaitre l'état de Vusb (state_Vusb)
        if (!state_Vusb) {digitalWrite(led_pin_r, HIGH);}
        if (state_Vusb) {digitalWrite(led_pin_v, HIGH);}
        delay(30);
        if (!state_Vusb) {digitalWrite(led_pin_r, LOW);}
        if (state_Vusb) {digitalWrite(led_pin_v, LOW);}
        delay(30);
    }
    // normal delay for Arduino Serial Monitor
    delay(1200);
  }

   /**
 * 3c-1 - Fonction d'acquisition de la température via le 1er thermomètre digital DS18B20 (ds1).
 * Fonction de lecture de la température via un thermomètre digital DS18B20 câblé sur le 1er bus ds1.
 */
byte getT1(float *T1, byte reset_search) {
  byte data[9], addr[8];
  // data[] : Données lues depuis le scratchpad
  // addr[] : Adresse du module 1-Wire détecté
  
  /* Reset le bus 1-Wire si nécessaire (requis pour la lecture du premier capteur) */
  if (reset_search) {
    ds1.reset_search();
  }
 
  /* Recherche le prochain capteur 1-Wire disponible */
  if (!ds1.search(addr)) {
    // Pas de capteur
    return NO_SENSOR_FOUND;
  }
  
  /* Vérifie que l'adresse a été correctement reçue */
  if (OneWire::crc8(addr, 7) != addr[7]) {
    // Adresse invalide
    return INVALID_ADDRESS;
  }
 
  /* Vérifie qu'il s'agit bien d'un DS18B20 */
  if (addr[0] != 0x28) {
    // Mauvais type de capteur
    return INVALID_SENSOR;
  }
 
  /* Reset le bus 1-Wire et sélectionne le capteur */
  ds1.reset();
  ds1.select(addr);
  
  /* Lance une prise de mesure de température et attend la fin de la mesure */
  ds1.write(0x44, 1);
  delay(800);
  
  /* Reset le bus 1-Wire, sélectionne le capteur et envoie une demande de lecture du scratchpad */
  ds1.reset();
  ds1.select(addr);
  ds1.write(0xBE);
 
 /* Lecture du scratchpad */
  for (byte i = 0; i < 9; i++) {
    data[i] = ds1.read();
  }
   
  /* Calcul de la température en degré Celsius */
  *T1 = (int16_t) ((data[1] << 8) | data[0]) * 0.0625; 
  
  // Pas d'erreur
  return READ_OK;
}
 /** 3c-2 - Fonction d'acquisition de la température via le 2ème thermomètre digital DS18B20 (ds2).
 */
byte getT2(float *T2, byte reset_search) {
  byte data[9], addr[8];
  // data[] : Données lues depuis le scratchpad
  // addr[] : Adresse du module 1-Wire détecté
  
  /* Reset le bus 1-Wire ci nécessaire (requis pour la lecture du premier capteur) */
  if (reset_search) {
    ds2.reset_search();
  }
 
  /* Recherche le prochain capteur 1-Wire disponible */
  if (!ds2.search(addr)) {
    // Pas de capteur
    return NO_SENSOR_FOUND;
  }
  
  /* Vérifie que l'adresse a été correctement reçue */
  if (OneWire::crc8(addr, 7) != addr[7]) {
    // Adresse invalide
    return INVALID_ADDRESS;
  }
 
  /* Vérifie qu'il s'agit bien d'un DS18B20 */
  if (addr[0] != 0x28) {
    // Mauvais type de capteur
    return INVALID_SENSOR;
  }
 
  /* Reset le bus 1-Wire et sélectionne le capteur */
  ds2.reset();
  ds2.select(addr);
  
  /* Lance une prise de mesure de température et attend la fin de la mesure */
  ds2.write(0x44, 1);
  delay(800);
  
  /* Reset le bus 1-Wire, sélectionne le capteur et envoie une demande de lecture du scratchpad */
  ds2.reset();
  ds2.select(addr);
  ds2.write(0xBE);
 
 /* Lecture du scratchpad */
  for (byte i = 0; i < 9; i++) {
    data[i] = ds2.read();
  }
   
  /* Calcul de la température en degré Celsius */
  *T2 = (int16_t) ((data[1] << 8) | data[0]) * 0.0625; 
  
  // Pas d'erreur
  return READ_OK;
}

/*
 * 3b - IHM clavier
 */
 
 void saisie(){Serial.println ("Systeme de Cuisson Assistee par Ordinateur (SCAO) ");
  //Saisie des paramètres de cuisson
  //Saisie de la duree de cuisson DC
  byte a; byte b; byte c; byte x=(15); 
  Serial.println ("Entrer DC (mn) sur 3 chiffres");
  while (i > 0) {
  switch (i) {
  case 3:
  if (Serial.available () > 0)  {a=Serial.read(); a=a&x; i=i-1; break;}
  case 2:
  if (Serial.available () > 0)  {b=Serial.read(); b=b&x; i=i-1; break;}
  case 1:
  if (Serial.available () > 0)  {c=Serial.read(); c=c&x; DC=(100*a+10*b+c); Serial.print (DC); Serial.println (" mn "); i=i-1; break;}
  default: {delay(1000);} 
    }//Switch
  } //While DC

  //Saisie du gabarit
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
 
 //Visualisation DC et N° de gabarit
 Serial.print ("Duree de cuisson "), Serial.print (DC); Serial.println (" mn - ");
  //Visualisation des parametres correspondants au N° du gabarit choisi
  delay (1000);
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
  Serial.print ("N° de gabarit choisi : ");  Serial.println(Gabarit); Serial.print("Ce gabarit correspond aux paramètres (p, G, I, Tu, Tm, Tau, Vc, Ac, ta) : ");
  Serial.print ("{");Serial.print (p); Serial.print (", "); Serial.print (G); Serial.print (", "); Serial.print (I); Serial.print (", "); Serial.print (Tu); Serial.print (", "); Serial.print (Tm); Serial.print (", "); Serial.print (Tau); Serial.print (", "); Serial.print (Vc); Serial.print (", "); Serial.print (A_c); Serial.print (", "); Serial.print (ta);Serial.println ("}");
  Serial.println ("Voulez-vous continuer ? taper O");
  flag=1;
  while (flag>0) {if (Serial.available() > 0)
    {reponse=Serial.read(); if (reponse==111 | reponse==79){flag=flag-1;}//Si le caractère frappé est O ou o
    
    }
  }
  }

  /**
 * 3d - Mesure des tensions et calcul du courant ibat
 */
  //fonction de changement d'échelle (fonction mathématique map() de l'arduino)
  //La multiplication par 2.0038 compense la division par 2 (pont diviseur) et l'impédance de l'entrée du microcontrôleur pour les chiffres après la virgule.
  void mesures(){
  analogReadResolution(13);
  Vusb = map (2.0038*analogRead(Vusb_demie), 0, MaxConv, 0, MaxVolt);
  Vbat_1 = map (2.0038*analogRead(Vbat_demie_1), 0, MaxConv, 0, MaxVolt);
  Vbat_2 = map (2.0038*analogRead(Vbat_demie_2), 0, MaxConv, 0, MaxVolt);
  ibat = Vbat_1 - Vbat_2;
  V33 = map (2.0038*analogRead(V33_demie), 0, MaxConv, 0, MaxVolt);
  if (Vusb < 1000) {state_Vusb = false;}
  if (Vusb > 4000) {state_Vusb = true;}
  }

/*
 * * 3h - Bilan énergétique de la batterie
 */

  /*
 * 3j - Visualisation du contenu des échantillons
 */
  void visu(){
  Serial.print(count);//N° de l'échantillon
  Serial.print(";");//Séparation des champs par une virgule
//  digitalClockDisplay();//Heure et date
  delay(100);
  Serial.print(T1, 2);//Température mesurée T1 en °C sur le couvercle de la casserole
  Serial.write(";"); //Séparation des champs par une virgule
  Serial.print(T2, 2);//Température mesurée T2 en °C sur la batterie
  Serial.write(";"); //Séparation des champs par une virgule
  Serial.print(Vusb);//Tension mesurée Vusb en mV
  Serial.print(";");//Séparation des champs par une virgule
  Serial.print(Vbat_1);//Tension mesurée Vbat1 en mV
  Serial.print(";");//Séparation des champs par une virgule
  Serial.print(ibat);//Courant mesuré ibat en mA
  Serial.print(";");//Séparation des champs par une virgule
  Serial.print(V33);//Tension mesurée V33 en mV
  Serial.print(";");//Séparation des champs par une virgule
  Serial.println(Ec);//Energie mesurée Ec en joules
  delay(2000);
  }

/** 4 - Fonction setup() **/

void setup() {
  /* Initialisation du port série */
  Serial.begin(9600);
  delay(2000);
  mesures();
   pinMode(led_pin_v, OUTPUT);
  pinMode(led_pin_j, OUTPUT);
  pinMode(led_pin_r, OUTPUT);
  pinMode(led_pin_b, OUTPUT);  // sets the digital pin 19 as output
  //Test des leds (mise sous tension)
  digitalWrite(led_pin_v, HIGH);
  digitalWrite(led_pin_j, HIGH);
  digitalWrite(led_pin_r, HIGH);
  digitalWrite(led_pin_b, HIGH);

  /*
   * 4b - IHM clavier
   */
  
  pinMode(inPin_stsp, INPUT);//sets the digital pin 1 as input
  if (state_Vusb) {saisie();}
  //char recu;
  //while (Serial.available() > 0) {recu = Serial.read(); Serial.print (recu); break;}
  while (!val_stsp) {
    val_stsp = digitalRead(inPin_stsp);
    Serial.print(val_stsp);
    Serial.println (" - attente de la cmd start");
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

//4c - Acquisition des températures T1 et T2

/*
 * 4d - Mesure des tensions et calcul du courant ibat*/
  analogReadResolution(13);

 //4j - Visualisation du contenu des échantillons
  Serial.println ("Cuisson en cours - chaque échantillon contient les champs suivants :");
  Serial.println("N°;heure;date;T1 (degrés C);T2 (degrés C);Vusb (mV);Vbat (mV);ibat (mA);V33 (mV);Ec (joules)");  
 //4k - Mode sleep
  pinMode(inPin_sleep, INPUT);    // sets the digital pin 10 as input
  digitalWrite(led_pin_r, HIGH);//USB serial connection is not establihed - Clic on serial monitor icon (right top icon)
  wait_s_m();//Wait for serial monitor 
  //while (!Serial);
    delay(100);
    digitalWrite(led_pin_r, LOW);
    //Serial.println("Starting...");
    delay(100);


  //4h - Bilan énergétique de la batterie

}

void loop() {
  // put your main code here, to run repeatedly:

//5c - Acquisition des températures T1 et T2
  //float T1;
  /* Lit la température T1 */
  if (getT1(&T1, true) != READ_OK) {
    Serial.println(F("Erreur de lecture du capteur"));
    return;
  }
  //float T2;
  /* Lit la température ambiante à ~1Hz */
  if (getT2(&T2, true) != READ_OK) {
    Serial.println(F("Erreur de lecture du capteur"));
    return;
  }
  
  //5d - Mesure des tensions et calcul du courant ibat
 mesures();

 //5f - Transmission
  /* Transmission des donnèes à l'e-r-433 */ 
  /*La fonction de transmission vw_send(message, length) : transmit a message, "message" is an array of the bytes to send,
  and "length" is the number of bytes stored in the array.*/

  count = count +1;

 //5h - Bilan énergétique de la batterie
 tt2 = (Chrono.elapsed());
 Et = ((Vbat_1/1000) * ibat)*((tt1 + tt2)/1000000);
 if (val_sleep) {Es = ((Vbat_1/1000) * 1.5)*(ts/1000000);}
// if (!  ) {Es = ((Vbat_1/1000) * ibat)*(ts/1000000);}
 Etot = Et + Es;
 Ec = Ec + Etot;  

 //5j - Visualisation du contenu des échantillons
 //Appel de la fonction visu() si le Teensy 3.2 est connecté à l'ordinateur (reçoit du 5V) à l'aide d'un câble USB
  if (state_Vusb){visu();}
}
