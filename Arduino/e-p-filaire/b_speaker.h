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
#ifndef B_SPEAKER_H
#define B_SPEAKER_H
#include <Arduino.h>
//3b - Speaker
void beep(unsigned char delayms);
//4b - Speaker
void setup_b();
//5b - Speaker
#endif
