//SOS.ino
#define L1 4
#define Led1On digitalWrite (L1,1);//Allume
#define Led1Off digitalWrite (L1,0);//Eteint

void setup(){
  pinMode (L1,OUTPUT);
}
void dot (){
  Led1On; delay(200); Led1Off;
  delay(200);
}
void dash (){
  Led1On; delay(600); Led1Off;
  delay(200);
}
void loop () {
  for (int i=0; i<3; i++){dash();}
  delay(600);
  for (int i=0; i<3; i++){dot();}
  delay(600);
  for (int i=0; i<3; i++){dash();}
  delay(600);
  delay(1400);
}

