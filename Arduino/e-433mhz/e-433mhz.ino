//Programme d'émission
#include <VirtualWire.h>

const int led_pin = 13;
const int transmit_pin = 12;

void setup()
{
  // Initialise the IO and ISR
  pinMode(led_pin, OUTPUT); 
  vw_set_tx_pin(transmit_pin);
  vw_setup(2000);   // Bits per sec
}

byte count = 1;

void loop()
{
  char msg[7] = {'h','e','l','l','o',' ','#'};

  msg[6] = count;
  digitalWrite(led_pin, HIGH); // Flash a light to show transmitting
  vw_send((uint8_t *)msg, 7);
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(led_pin, LOW);
  delay(1000);
  count = count + 1;
}
