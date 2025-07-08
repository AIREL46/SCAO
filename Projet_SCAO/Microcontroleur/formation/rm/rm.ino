#define avd 4 // actif a 1 - Avance droite - Led1
#define avdOn digitalWrite(avd, HIGH)
#define avdOff digitalWrite(avd, LOW)
#define recd 5 // actif a 1 - Recule droite - Led2
#define recdOn digitalWrite(recd, HIGH)
#define recdOff digitalWrite(recd, LOW)
#define avg 6 // actif a 1 - Avance gauche - Led3
#define avgOn digitalWrite(avg, HIGH)
#define avgOff digitalWrite(avg, LOW)
#define recg 7 // actif a 1 - Recule gauche - Led4
#define recgOn digitalWrite(recg, HIGH)
#define recgOff digitalWrite(recg, LOW)
#define md 2
#define mdOn (digitalRead (md)==0)//actif a 0V - Moustache droite
#define mdOff (digitalRead (md)==1)//actif a 5V
#define mg 3
#define mgOn (digitalRead (mg)==0)//actif a 0V - Moustache gauche
#define mgOff (digitalRead (mg)==1)//actif a 5V
void setup(){
  pinMode (avd, OUTPUT);
  pinMode (recd, OUTPUT);
  pinMode (avg, OUTPUT);
  pinMode (recg, OUTPUT);
  pinMode (md, INPUT);
  pinMode (mg, INPUT);
  }
int avmdr=mdOn;
int mdr;
int avmga=mgOn;
int mga;

void loop() {
  mdr=mdOn;
  mga=mgOn;
  // détection des flancs montants de md et mg
  if (!avmdr && mdr) {avmdr=mdr; avdOff; avgOff; recdOn; recgOn; delay (1000); recdOff; recgOff; avdOn; recgOn; delay (500); recgOff;} //Obstacle a droite
  if (!avmga && mga) {avmga=mga; avdOff; avgOff; recdOn; recgOn; delay (1000); recdOff; recgOff; avgOn; recdOn; delay (500); recdOff;} //Obstacle a gauche
  // détection des flancs descendants de md et mg
  if (avmdr && !mdr) {avmdr=mdr;} //Plus obstacle a droite
  if (avmga && !mga) {avmga=mga;} //Plus obstacle a gauche
  avdOn;
  avgOn;
  
}
