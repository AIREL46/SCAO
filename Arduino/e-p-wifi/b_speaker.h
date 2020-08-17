/*
1b - Speaker
 -
 Piezo

 This example shows how to run a Piezo Buzzer on pin 9
 using the analogWrite() function.

 It beeps 3 times fast at startup, waits a second then beeps continuously
 at a slower pace
2b - Speaker

 */
//3b - Speaker
void beep(unsigned char delayms){
  analogWrite(speaker, 200);      // Almost any value can be used except 0 and 255
                           // experiment to get the best tone
  delay(delayms);          // wait for a delayms ms
  analogWrite(speaker, 0);       // 0 turns it off
  delay(delayms);          // wait for a delayms ms
}
//4b - Speaker
void setup_b()  {
  beep(50);
  beep(50);
  beep(50);
  delay(1000);
}
//5b - Speaker
//void loop()  {
  //beep(200);
  //delay(1000);
//}
