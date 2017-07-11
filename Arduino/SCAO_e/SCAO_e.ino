

/*
  
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
float Gabarit1[] = {30, 0.4, 0.275, 70, 25, 30, 2, 1, 4};
float Gabarit2[] = {30, 0.4, 0.275, 72.5, 22.5, 28, 2.5, 1.25, 4};
float Gabarit3[] = {30, 0.4, 0.275, 75, 20, 24, 3, 1.5, 4};
float Gabarit4[] = {30, 0.4, 0.275, 77.5, 17.5, 22, 3.5, 1.75, 4};
float Gabarit5[] = {30, 0.4, 0.275, 80, 15, 20, 4, 2, 4};
float Gabarit6[] = {30, 0.4, 0.342, 82.5, 12.5, 18, 4.5, 2.25, 4};
float Gabarit7[] = {30, 0.4, 0.409, 85, 10, 16, 5, 2.5, 4};
float Gabarit8[] = {30, 0.4, 0.685, 87.5, 7.5, 14, 5.5, 2.75, 4};
float Gabarit9[] = {30, 0.4, 0.685, 90, 5, 12, 6, 3, 4};
int p; float G; float I; float Tu; float Tm; int Tau; float Vc; float Ac; int ta;
int led = 13;
int DC = 100;
int Gabarit = 5;
int flag=1;
int i=3;
int reponse;
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  Serial.begin (9600);
  Serial.println ("Systeme de Cuisson Assistee par Ordinateur (SCAO) ");
   //Saisie de la duree de cuisson DC
  byte a; byte b ; byte c; byte x=(15); 
  Serial.println ("Entrer DC (mn) sur 3 chiffres");
  while (i > 0) {
    Serial.println (i);
    delay (10000);
    i=i-1;
    Serial.println (i);
    delay (10000);
    i=i-1;
    Serial.println (i);
    delay (10000);
    i=i-1;
    } //While DC

  }//setup

// the loop routine runs over and over again forever:
void loop() {
  Serial.println ("Systeme de Cuisson Assistee par Ordinateur (SCAO) ");

  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second
}
