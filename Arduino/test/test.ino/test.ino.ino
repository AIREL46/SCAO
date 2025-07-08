#include <Telemetry.h>
int32_t i;
const int led_pin_v = 13;//Led verte

void setup() {
  Serial.begin(9600); // Do not forget to initialize serial
  i = 0;
  delay(1000);
  pinMode(led_pin_v, OUTPUT);
}

void loop() {
  // Send counter value under topic `foo`
  Telemetry.pub_i32("foo", i);
  digitalWrite(led_pin_v, HIGH);
  delay(1000);
  digitalWrite(led_pin_v, LOW);
  delay(1000);
  i++;
}
