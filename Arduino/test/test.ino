//test de la batterie Lipo
#define mesure_1 A1 //Mesure de tension
#define MaxConv 8192
#define MaxVolt 3272
const int led_pin = 13;
const int digital_0 = 0;
void setup() {
  pinMode(led_pin, OUTPUT);
  pinMode(digital_0, OUTPUT);
  analogReadResolution(13);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(led_pin, HIGH);
  digitalWrite(digital_0, HIGH);
  delay(100);
  Serial.print(map (2.0038*analogRead(mesure_1), 0, MaxConv, 0, MaxVolt));
  Serial.println(" mV ");
  delay(1000);
  digitalWrite(led_pin, LOW);
  digitalWrite(digital_0, LOW);
  delay(100);
  Serial.print(map (2.0038*analogRead(mesure_1), 0, MaxConv, 0, MaxVolt));
  Serial.println(" mV ");
  delay(1000);
}
