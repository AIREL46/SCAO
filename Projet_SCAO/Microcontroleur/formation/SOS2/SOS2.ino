#define Led1 4 // actif a 1
#define Led1On digitalWrite(Led1, HIGH)
#define Led1Off digitalWrite(Led1, LOW)
void setup(){
  pinMode (Led1, OUTPUT);
 }
char S = 'S';
char O = 'O';
void loop() {
  //Envoi lettre S
  Led1Off;//Start bit
  delay (3.33);
  for (int i=0; i<=7; i++) {if (S & (1<<i)) {Led1Off; delay (3.33);}else {Led1On; delay (3.33);}}
  Led1On;
  delay (6.66);// 2 stop bit
  //Envoi lettre O
  Led1Off;//Start bit
  delay (3.33);
  for (int i=0; i<=7; i++) {if (O & (1<<i)) {Led1Off; delay (3.33);}else {Led1On; delay (3.33);}}
  Led1On;
  delay (6.66);// 2 stop bit
  //Envoi lettre S
  Led1Off;//Start bit
  delay (3.33);
  for (int i=0; i<=7; i++) {if (S & (1<<i)) {Led1Off; delay (3.33);}else {Led1On; delay (3.33);}}
  Led1On;
  delay (6.66);// 2 stop bit
  delay (1000);
}
