#define Led1 4 // actif a 1
#define Led1On digitalWrite(Led1, HIGH)
#define Led1Off digitalWrite(Led1, LOW)
#define Led2 5 // actif a 1
#define Led2On digitalWrite(Led2, HIGH)
#define Led2Off digitalWrite(Led2, LOW)
#define P1 2
#define Pous1On (digitalRead (P1)==0)//actif a 0V
#define Pous1Off (digitalRead (P1)==1)//actif a 5V
#define P2 3
#define Pous2On (digitalRead (P2)==0)//actif a 0V
#define Pous2Off (digitalRead (P2)==1)//actif a 5V
enum {re, mi, fa, sol, la, si};
void setup(){
  pinMode (Led1, OUTPUT);
  pinMode (Led2, OUTPUT);
  pinMode (P1, INPUT);
  pinMode (P2, INPUT);
  //Serial.begin(9600);
 }
int v1; // Initialisation v1 pour détection des flancs du bouton poussoir P1
int av1=Pous1On;// Initialisation av1 (ancienne valeur) pour détection des flancs du bouton poussoir P1
int v2; // Initialisation v2 pour détection des flancs du bouton poussoir P2
int av2=Pous2On;// Initialisation av2 (ancienne valeur) pour détection des flancs du bouton poussoir P2
void loop() {
  //v1=Pous1On;
  //if(!av1 && v1) {av1=v1; Led1On;} // détection flanc montant de P1
  //if(av1 && !v1) {av1=v1; Led1Off;} // détection flanc descendant de P1
  //v2=Pous2On;
  //if(!av2 && v2) {av2=v2; Led2On;} // détection flanc montant de P2
  //if(av2 && !v2) {av2=v2; Led2Off;} // détection flanc descendant de P2
  while (!(Pous1On && Pous2On)) {Led1On; delay (500); Led1Off; delay (500);}
  //delay(1000);
}
