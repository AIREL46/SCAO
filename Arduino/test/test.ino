#include <Snooze.h>


const int led_pin_v = 13;//Led verte
// Load timer and USBSerial drivers
SnoozeTimer timer;
SnoozeUSBSerial usb;

/***********************************************************
 Install drivers to a SnoozeBlock, timer to wake and USB Serial Driver to
 fix printing to serial monitor after sleeping.
 ***********************************************************/
SnoozeBlock config_teensy32(usb, timer);
int idx;
void setup()
{
  
  Serial.begin(9600);
  pinMode(led_pin_v, OUTPUT);
  while (!Serial);
    delay(100);
    Serial.println("Starting...");
    delay(100);
     /********************************************************
     Set Low Power Timer wake up in milliseconds.
     ********************************************************/
    timer.setTimer(30000);// milliseconds
    // sleep index
  idx = 0;
    
}
 
void loop()
{
  int who = 0; // what woke us up
  delay(1000);
  digitalWrite(led_pin_v, LOW);
  Serial.println("Bonne nuit Quiet cook");
  delay(1000);
  who = Snooze.deepSleep( config_teensy32 );// return module that woke processor
  // wait for serial monitor
    elapsedMillis time = 0;
    while (!Serial && time < 1000) {
        Serial.write(0x00);// print out a bunch of NULLS to serial monitor
        digitalWriteFast(led_pin_v, HIGH);
        delay(30);
        digitalWriteFast(led_pin_v, LOW);
        delay(30);
    }
    // normal delay for Arduino Serial Monitor
    delay(200);
    // print who woke the teensy up, i.e. timer || digital
    Serial.printf("Timer Driver number indicator: %i | index: %i\n", who, idx);
    delay(1000);
idx++;
  Serial.println("Bonjour Quiet cook");
  digitalWrite(led_pin_v, HIGH);
}
