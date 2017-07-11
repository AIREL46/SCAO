#define Led1 5 // actif a 1
#define Led1On digitalWrite(Led1, HIGH)
#define Led1Off digitalWrite(Led1, LOW)
#define Led2 4 // actif a 1
#define Led2On digitalWrite(Led2, HIGH)
#define Led2Off digitalWrite(Led2, LOW)
#define P1 2
#define Pous1On (digitalRead (P1)==0)//actif a 0V
#define Pous1Off (digitalRead (P1)==1)//actif a 5V
void setup(){
  pinMode (Led1, OUTPUT);
  pinMode (Led2, OUTPUT);
  pinMode (P1, INPUT);
  //Serial.begin(9600);
 }
int v; // Initialisation v pour détection du flanc montant du bouton poussoir
int av=Pous1On;// Initialisation av (ancienne valeur) pour détection du flanc montant du bouton poussoir
double nbim;
double nbimm(1);
double nbid;
double nbidm(1);
double rc;
void loop() {
  // détection flanc montant de P1
  v=Pous1On;
  if(!av && v) {av=v; nbim=0; nbidm=nbid;}
  if(av && !v) {av=v; nbid=0; nbimm=nbim;}
  ++nbim;
  ++nbid;
  rc=nbimm/(nbimm+nbidm);
  if (rc <= 0.4) {Led2Off; Led1On;}
  if (rc >= 0.6) {Led1Off; Led2On;}
  if (rc > 0.4 && rc < 0.6) {Led1Off; Led2Off;}
  if (nbimm==nbidm) {Led1Off; Led2Off;}
  delay(1000);
}
