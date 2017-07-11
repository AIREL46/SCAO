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
  Serial.begin(9600);
  }
  int x;
  int y;

void loop() {
  x=0;
  if (x==6) y=3;
  Serial.print (x);
  Serial.print (" - ");
  Serial.println (y);
  delay (1000);  
}
