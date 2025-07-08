//Parking.ino
#define L1 4
#define Led1On digitalWrite (L1,1);//Allume
#define Led1Off digitalWrite (L1,0);//Eteint
#define L2 5
#define Led2On digitalWrite (L2,1);//Allume
#define Led2Off digitalWrite (L2,0);//Eteint
#define P1 2
#define Pous1On (digitalRead (P1)==0)//actif a 0V
#define Pous1Off (digitalRead (P1)==1)//actif a 5V
#define P2 3
#define Pous2On (digitalRead (P2)==0)//actif a 0V
#define Pous2Off (digitalRead (P2)==1)//actif a 5V

void setup(){
  pinMode (L1,OUTPUT);
  pinMode (L2,OUTPUT);
  pinMode (P1,INPUT);
  pinMode (P2,INPUT);
}
int Nbp1(0);
int Nbp2(0);
void loop () {
  if (Pous1On) {delay(200); ++Nbp1; delay(500);}
  if (Pous2On) {delay(200); ++Nbp2; delay(500);}
  if (Nbp1>Nbp2) {Led1On; Led2Off;}else {Led1Off; Led2Off;}
  if (Nbp2>Nbp1){Led2On; Led1Off;}else {Led1Off; Led2Off;}
}

