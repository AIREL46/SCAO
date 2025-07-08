#define Pot A1 // patte de lecture du curseur du potentiometre
#define Max 1023 // valeur maximale lue
#define Middle 1023/2 // valeur Middle lue
#define Min 0 // valeur minimale lue
#define rcmax 90 // rapport cyclique maximal
#define rcmiddle 90 // rapport cyclique maximal
#define rcmin 10 // rapport cyclique maximal
#define Val_Pot analogRead(Pot)
#define Led1 4 // actif a 1
#define Led1On digitalWrite(Led1, HIGH)
#define Led1Off digitalWrite(Led1, LOW)
#define Led2 5 // actif a 1
#define Led2On digitalWrite(Led2, HIGH)
#define Led2Off digitalWrite(Led2, LOW)

void setup(){
  Serial.begin(9600);
  pinMode (Led1, OUTPUT);
  pinMode (Led2, OUTPUT);
  }
  float rc1;
  float rc2;
  int p(500); //periode
void loop() {
  if (Val_Pot > Middle) {Led1Off; Led2On; rc1=map(Val_Pot, Middle, Max, rcmin, rcmax); delay (p*rc1/100); Led2Off; delay (p-(p*rc1/100));}
  if (Val_Pot <= Middle) {Led1On; Led2Off; rc2=map(Val_Pot, Min, Middle, rcmin, 2*rcmin); delay (p*rc2/100); Led1Off; delay (p-(p*rc2/100));}
  Serial.println (rc2); 
  }
