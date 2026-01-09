/* Ce programe permet le test du speaker installé sur D4
 *  
 */
const int speaker=4;//Speaker installé sur D4
#include <Arduino.h>
 void beep(unsigned char delayms){
  analogWrite(speaker,200); //Almost any value can be uded except 0 and 255
  delay(delayms);
  analogWrite(speaker, 0);
  delay(delayms); 
  
 }
void setup() {
  // put your setup code here, to run once:
beep(50);
  delay(1000);
 }
void loop() {
  delay(1000);
  beep(500);
  delay(1000);
  beep(50);
  delay(1000);
  beep(50);
  delay(1000);
  beep(50);
  delay(3000);
  }
