#define Pot A1 // patte de lecture du curseur du potentiometre
#define Max 1023 // valeur maximale lue
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
void loop() {
  if (Val_Pot==0 || Val_Pot <= 0.25*Max) {Led1Off; Led2Off;}
  if (Val_Pot > 0.25*Max && Val_Pot <= 0.50*Max) {Led1On; Led2Off;}
  if (Val_Pot > 0.50*Max && Val_Pot <= 0.75*Max) {Led1Off; Led2On;}
  if (Val_Pot > 0.75*Max && Val_Pot <= Max) {Led1On; Led2On;}
  Serial.println (Val_Pot);
  delay(500);
  }
