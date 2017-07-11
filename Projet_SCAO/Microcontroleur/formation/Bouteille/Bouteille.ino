#define Led1 4 // actif a 1
#define Led1On digitalWrite(Led1, HIGH)
#define Led1Off digitalWrite(Led1, LOW)
#define P1 2
#define Pous1On (digitalRead (P1)==0)//actif a 0V
#define Pous1Off (digitalRead (P1)==1)//actif a 5V
#define P2 3
#define Pous2On (digitalRead (P2)==0)//actif a 0V
#define Pous2Off (digitalRead (P2)==1)//actif a 5V
void setup(){
  pinMode (Led1, OUTPUT);
  pinMode (P1, INPUT);
  pinMode (P2, INPUT);
  }
int av1=Pous1On;
int v1;
int av2=Pous2On;
int v2;
int nbi;
int nbim;
int db(100); //durée de la boucle en ms
int tr; //temps de remplissage
void loop() {
  // détection flanc montant de P1
  v1=Pous1On;
  v2=Pous2On;
  if (!av1 && v1) {av1=v1; Led1On; nbi=0;}
  if (av1 && !v1) {av1=v1; Led1Off; nbim=nbi;}
  ++nbi;
  if (!av2 && v2) {Led1On; delay (tr); Led1Off;}
  av2=v2; 
  delay (db);
  tr=db*nbim;
  }
