

/**
 * 1b - IHM clavier
 * Acquisition des paramètres de cuisson
 * L'objet est l'acquisition des paramètres de cuisson saisis par l'utilisateur (setup).
 * La commande start stop permet le passage du setup à la boucle loop
 * 2b - IHM clavier
 * Les paramètres de cuisson sont la Durée de Cuisson (DC) et le Gabarit de cuisson (Gabarit).
 * DC est exprimée en mn sur 3 chiffres
 * Le Gabarit est un nombre entier compris entre 1 et 9.
 * Chaque Gabarit est associé à 9 paramètres :
 * la période (p), 
 * le gain (G),
 * l'Intensité de chauffe(I),
 * la température d'utilisation (Tu),
 * le temps de montée Tm (mn)
 * la constante de temps Tau (mn)
 * la vitesse de consigne Vc (°C/mn)
 * l'accélération de consigne Ac (°C/mn2)
 * la durée d'anticipation ta (nombre d'itérations).
 * Ces paramètres sont décrits dans le document "brevet" (page 6 et 28) dont la version Word est accessible par le lien ci-dessous:
 * https://github.com/AIREL46/SCAO/blob/master/Brevet/SCAO/word/La%20description%20du%20SCAO%20-%20d.doc
 * La commande start stop (stsp) permet de quitter le setup pour entrer dans la boucle loop 
 * Elle est commandée par un switch ON/OFF SW2 et elle se concrétise par une variable booléenne.
 * En position OFF, la variable est false correspondant à l'état stop.
 * En position ON, la variable est true correspondant à l'état start.
 * A l'état stop l'exécution du programme est maintenu dans une boucle de saisie du setup().
 * A l'état start l'exécution du programme transite dans la boucle loop().
 */
const int inPin_stsp = 11;    // SW2 connected to digital pin 10
bool val_stsp = false;//Création de la variable booléenne start stop (stsp)
//Création des tableaux (array) des gabarits de cuisson
float Gabarit1[] = {30, 0.4, 0.275, 70, 25, 30, 2, 1, 4};
float Gabarit2[] = {30, 0.4, 0.275, 72.5, 22.5, 28, 2.5, 1.25, 4};
float Gabarit3[] = {30, 0.4, 0.275, 75, 20, 24, 3, 1.5, 4};
float Gabarit4[] = {30, 0.4, 0.275, 77.5, 17.5, 22, 3.5, 1.75, 4};
float Gabarit5[] = {30, 0.4, 0.275, 80, 15, 20, 4, 2, 4};
float Gabarit6[] = {30, 0.4, 0.342, 82.5, 12.5, 18, 4.5, 2.25, 4};
float Gabarit7[] = {30, 0.4, 0.409, 85, 10, 16, 5, 2.5, 4};
float Gabarit8[] = {30, 0.4, 0.685, 87.5, 7.5, 14, 5.5, 2.75, 4};
float Gabarit9[] = {30, 0.4, 0.685, 90, 5, 12, 6, 3, 4};
//Création des variables "paramètres de cuisson"
int p; float G; float I; float Tu; float Tm; int Tau; float Vc; float Ac; int ta;
//Affectation de la variable led à l'entrée 13
int led = 13;
//Création de la variable booléenne val_saisie
bool val_saisie = true;
//Création de la variable Durée de Cuisson (DC) et affectation d'une valeur par défaut
int DC = 100;
//Création de la variable Gabarit et affectation d'une valeur par défaut
int Gabarit = 5;
//Création de la variable flag dédiée à la saisie du N° de gabarit
int flag=1;
//Création du paramètre i correspondant au nombre de chiffres à saisir pour définir la durée de cuisson
int i=3;
int reponse;
//3b - IHM clavier
//4b - IHM clavier
void setup() {                
  Serial.begin (9600);
  pinMode(inPin_stsp, INPUT);//sets the digital pin 11 as input
  delay(6000);
  Serial.println ("Systeme de Cuisson Assistee par Ordinateur (SCAO) ");
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
 Serial.print ("Duree de cuisson "), Serial.print (DC); Serial.print (" mn - ");
  //Visualisation des parametres correspondants au N° du gabarit choisi
  delay (1000);
  switch (Gabarit) {
  case 1: p=Gabarit1[0]; G=Gabarit1[1]; I=Gabarit1[2]; Tu=Gabarit1[3]; Tm=Gabarit1[4]; Tau=Gabarit1[5]; Vc=Gabarit1[6]; Ac=Gabarit1[7]; ta=Gabarit1[8];  break;
  case 2: p=Gabarit2[0]; G=Gabarit2[1]; I=Gabarit2[2]; Tu=Gabarit2[3]; Tm=Gabarit2[4]; Tau=Gabarit2[5]; Vc=Gabarit2[6]; Ac=Gabarit2[7]; ta=Gabarit2[8];  break;
  case 3: p=Gabarit3[0]; G=Gabarit3[1]; I=Gabarit3[2]; Tu=Gabarit3[3]; Tm=Gabarit3[4]; Tau=Gabarit3[5]; Vc=Gabarit3[6]; Ac=Gabarit3[7]; ta=Gabarit3[8];  break;
  case 4: p=Gabarit4[0]; G=Gabarit4[1]; I=Gabarit4[2]; Tu=Gabarit4[3]; Tm=Gabarit4[4]; Tau=Gabarit4[5]; Vc=Gabarit4[6]; Ac=Gabarit4[7]; ta=Gabarit4[8];  break;
  case 5: p=Gabarit5[0]; G=Gabarit5[1]; I=Gabarit5[2]; Tu=Gabarit5[3]; Tm=Gabarit5[4]; Tau=Gabarit5[5]; Vc=Gabarit5[6]; Ac=Gabarit5[7]; ta=Gabarit5[8];  break;
  case 6: p=Gabarit6[0]; G=Gabarit6[1]; I=Gabarit6[2]; Tu=Gabarit6[3]; Tm=Gabarit6[4]; Tau=Gabarit6[5]; Vc=Gabarit6[6]; Ac=Gabarit6[7]; ta=Gabarit6[8];  break;
  case 7: p=Gabarit7[0]; G=Gabarit7[1]; I=Gabarit7[2]; Tu=Gabarit7[3]; Tm=Gabarit7[4]; Tau=Gabarit7[5]; Vc=Gabarit7[6]; Ac=Gabarit7[7]; ta=Gabarit7[8];  break;
  case 8: p=Gabarit8[0]; G=Gabarit8[1]; I=Gabarit8[2]; Tu=Gabarit8[3]; Tm=Gabarit8[4]; Tau=Gabarit8[5]; Vc=Gabarit8[6]; Ac=Gabarit8[7]; ta=Gabarit8[8];  break;
  case 9: p=Gabarit9[0]; G=Gabarit9[1]; I=Gabarit9[2]; Tu=Gabarit9[3]; Tm=Gabarit9[4]; Tau=Gabarit9[5]; Vc=Gabarit9[6]; Ac=Gabarit9[7]; ta=Gabarit9[8];  break;
  }//switch
  Serial.print ("N° de gabarit choisi : ");  Serial.print(Gabarit); Serial.println(" correspondant aux paramètres (p, G, I, Tu, Tm, Tau, Vc, Ac, ta) : ");
  Serial.print (p); Serial.print (" - "); Serial.print (G); Serial.print (" - "); Serial.print (I); Serial.print (" - "); Serial.print (Tu); Serial.print (" - "); Serial.print (Tm); Serial.print (" - "); Serial.print (Tau); Serial.print (" - "); Serial.print (Vc); Serial.print (" - "); Serial.print (Ac); Serial.print (" - "); Serial.println (ta);
  while (!val_stsp) {val_stsp = digitalRead(inPin_stsp); Serial.print(val_stsp); Serial.println (" - attente de la cde start"); delay(1000);}
  }//setup

//5b - IHM clavier
void loop() {
  val_stsp = digitalRead(inPin_stsp);//read the input pin
  Serial.print(val_stsp);
  Serial.println(" - Cuisson en cours");
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second
}
