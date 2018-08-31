#include <telemetry_version.h>
const int led_pin_v = 13;//Led verte
int it = 0;
char message[13] = "Hello Régis";

void setup() {
   /* Initialisation du port série */
  Serial.begin(9600);
  delay(1000);
  pinMode(led_pin_v, OUTPUT);
}

void loop() {
  //while (!Serial);
  delay(500);
  if (it==0) {Serial.print("N°;"); Serial.println("Evénement");}
  Serial.print(it);
  Serial.println(";Bonjour SCAO");
  digitalWrite(led_pin_v, HIGH);
  delay(1000);
  digitalWrite(led_pin_v, LOW);
  delay(500);
  it++;
}
