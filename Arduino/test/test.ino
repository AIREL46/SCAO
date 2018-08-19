const int led_pin_v = 13;//Led verte
// INCLUDE CHRONO LIBRARY
#include <Chrono.h> 
unsigned long tt=0;//temps de travail
// Instanciate a Chrono object.
Chrono Chrono(Chrono::MICROS);

void setup() {
Serial.begin(9600);
pinMode(led_pin_v, OUTPUT);
}

void loop() {
   digitalWrite(led_pin_v, HIGH);
   delay(1000);
   digitalWrite(led_pin_v, LOW);
   delay(1000);
   tt = (Chrono.elapsed());
   Serial.print ("temps de travail : ");
   Serial.print (tt);
   Serial.println (" mico secondes");
   Chrono.restart();  // restart the Chrono 
 }
