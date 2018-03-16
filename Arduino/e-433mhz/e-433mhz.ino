//Programme d'émission
#include <VirtualWire.h>

const int led_pin_v = 13;
const int led_pin_j = 14;
const int led_pin_r = 15;
const int transmit_pin = 12;

void setup()
{
  // Initialise the IO and ISR
  pinMode(led_pin_v, OUTPUT); 
  pinMode(led_pin_j, OUTPUT); 
  pinMode(led_pin_r, OUTPUT); 
  vw_set_tx_pin(transmit_pin);
  vw_setup(2000);   // Bits per sec
}

byte count = 1;

void loop()
{
  char msg[7] = {'h','e','l','l','o',' ','#'};

  msg[6] = count;
  digitalWrite(led_pin_v, HIGH); // Flash a light to show transmitting
  digitalWrite(led_pin_j, HIGH); // Flash a light to show transmitting
  digitalWrite(led_pin_r, HIGH); // Flash a light to show transmitting
  vw_send((uint8_t *)msg, 7);
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(led_pin_v, LOW);
  digitalWrite(led_pin_j, LOW);
  digitalWrite(led_pin_r, LOW);
  delay(1000);
  count = count + 1;
}

