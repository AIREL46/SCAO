//Moteur pap.ino
#define L1 4
#define Led1On digitalWrite (L1,1);//Allume
#define Led1Off digitalWrite (L1,0);//Eteint
#define L2 5
#define Led2On digitalWrite (L2,1);//Allume
#define Led2Off digitalWrite (L2,0);//Eteint
#define L3 6
#define Led3On digitalWrite (L3,1);//Allume
#define Led3Off digitalWrite (L3,0);//Eteint
#define L4 7
#define Led4On digitalWrite (L4,1);//Allume
#define Led4Off digitalWrite (L4,0);//Eteint
#define P1 2
#define Pous1On (digitalRead (P1)==0)//actif a 0V
#define Pous1Off (digitalRead (P1)==1)//actif a 5V
#define P2 3
#define Pous2On (digitalRead (P2)==0)//actif a 0V
#define Pous2Off (digitalRead (P2)==1)//actif a 5V

void setup(){
  pinMode (L1,OUTPUT);
  pinMode (L2,OUTPUT);
  pinMode (L3,OUTPUT);
  pinMode (L4,OUTPUT);
  pinMode (P1,INPUT);
  pinMode (P2,INPUT);
}

int Nbv(0);
int anciennevaleur1=Pous1On;
int valeur1;
int anciennevaleur2=Pous2On;
int valeur2;
void loop () {
  valeur1 = Pous1On;
  if (!anciennevaleur1 && valeur1){Led1Off; Led2On; Led3Off; Led4On; delay(500); Led1On; Led2Off; Led3Off; Led4On; delay(500); Led1On; Led2Off; Led3On; Led4Off; delay(500); Led1Off; Led2On; Led3Off; Led4On; delay(500);}
  anciennevaleur1=valeur1;
  valeur2 = Pous2On;
  if (!anciennevaleur2 && valeur2){Led1Off; Led2On; Led3On; Led4Off; delay(500); Led1On; Led2Off; Led3On; Led4Off; delay(500); Led1On; Led2Off; Led3Off; Led4On; delay(500); Led1Off; Led2On; Led3Off; Led4On; delay(500);}
  anciennevaleur2=valeur2;
}

