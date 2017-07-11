//Petite_sequence_L1_L2.ino
#define L1 4
#define Led1On digitalWrite (L1,1);//Allume
#define Led1Off digitalWrite (L1,0);//Eteint
#define L2 5
#define Led2On digitalWrite (L2,1);//Allume
#define Led2Off digitalWrite (L2,0);//Eteint
#define P1 2
#define Pous1On (digitalRead (P1)==0)//actif a 0V
#define Pous1Off (digitalRead (P1)==1)//actif a 5V
void setup(){
  pinMode (L1,OUTPUT);
  pinMode (L2,OUTPUT);
  pinMode (P1,INPUT);

}
void loop () {
  if (Pous1On){
  Led1On; delay(1000);  Led1Off;
  Led1On;  Led2On; delay(1000);  Led1Off;  Led2Off;
  Led2On;  delay(1000);  Led2Off;
  }
}

