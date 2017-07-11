#define Pot A1 // patte de lecture du curseur du potentiometre
#define Max 1023 // valeur maximale lue
#define Min 0 // valeur minimale lue
#define Fmax 100 // valeur maximale de la fréquence
#define Fmin 1 // valeur minimale de la fréquence
#define Val_Pot analogRead(Pot)
#define Led1 4 // actif a 1
#define Led1On digitalWrite(Led1, HIGH)
#define Led1Off digitalWrite(Led1, LOW)
#define Led2 5 // actif a 1
#define Led2On digitalWrite(Led2, HIGH)
#define Led2Off digitalWrite(Led2, LOW)
#define P1 2
#define Pous1On (digitalRead (P1)==0)//actif a 0V
#define Pous1Off (digitalRead (P1)==1)//actif a 5V
void setup(){
  pinMode (Led1, OUTPUT);
  pinMode (Led2, OUTPUT);
  pinMode (P1, INPUT);
  Serial.begin(9600);
 }
double SRC(5); // Sélection du rapport cyclique
double RC; // Rapport cyclique
byte RF(1); // Réglage de la fréquence
double T; // Période
double t1; // 
double t2;
int v; // Initialisation v pour détection du flanc montant du bouton poussoir
int av=Pous1On;// Initialisation av (ancienne valeur) pour détection du flanc montant du bouton poussoir
void loop() {
  Serial.print (Val_Pot);
  Serial.print (" - ");
  Serial.print (RF);
  Serial.print (" - ");
  Serial.print (RC);
  Serial.print (" !av = ");
  Serial.print (!av);
  Serial.print (" v =  ");
  Serial.print (v);
  Serial.print (" !av && v =  ");
  Serial.print (!av && v);
  Serial.print (" T =  ");
  Serial.print (T);
  Serial.print (" t1 =  ");
  Serial.print (t1);
  Serial.print (" t2 =  ");
  Serial.println (t2);
  RF=map(Val_Pot, Min, Max, Fmin, Fmax);
  T=1000/RF;
  t1=T*RC;
  t2=T-t1;
  // détection flanc montant de P1
  v=Pous1On;
  if(av && !v) {SRC++; delay(500);}
  av=v;
  if(SRC==10) {SRC=0;}
  RC=SRC/10;
  if (RC==0) {RC=0.1;}
  Led1On;
  delay (t1);
  Led1Off;
  delay(t2);
}
