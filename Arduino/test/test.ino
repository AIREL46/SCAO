//test de la batterie Lipo
#define mesure_1 A7 //Mesure de la tension Vbat
#define mesure_2 A8 //Mesure de la tension Vusb
#define mesure_3 A9 //Mesure de la tension 3.3V
#define MaxConv 8192
#define MaxVolt 3272
//Fontion mesure de tension
long int mesure(int i){
long int m;
m=map (2.0038*analogRead(mesure_1), 0, MaxConv, 0, MaxVolt);
long int rm[4];
rm[1]=m;
m=map (2.0038*analogRead(mesure_2), 0, MaxConv, 0, MaxVolt);
rm[2]=m;
m=map (2.0038*analogRead(mesure_3), 0, MaxConv, 0, MaxVolt);
rm[3]=m;
return rm[i];
}
const int led_pin = 13;
void setup() {
  pinMode(led_pin, OUTPUT);
  analogReadResolution(13);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(led_pin, HIGH);
  delay(1000);
  Serial.print(" Vusb : ");
  Serial.print(mesure(2));
  Serial.print(" mV ");
  Serial.print(" Vbat : ");
  Serial.print(mesure(1));
  Serial.print(" mV ");
  Serial.print(" V3.3 : ");
  Serial.print(mesure(3));
  Serial.println(" mV ");
  digitalWrite(led_pin, LOW);
  delay(1000);
}
