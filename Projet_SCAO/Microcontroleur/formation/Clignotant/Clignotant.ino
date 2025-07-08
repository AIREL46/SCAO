int led1 = 12;//This is the PIN the LED is controlled from
int led2 = 13;
int onTime = 1000;
int offTime = 1000;
//the stup routine runs once when you press reset, or power up the Arduino
void setup()
{
  pinMode(led1, OUTPUT); //Initialize the digital pin as an output.
  pinMode(led2, OUTPUT);
  Serial.begin(9600); 
}
//this loop routine runs over and over again forever:
void loop()
{
  int mesure;
  double valeurUtile;
  mesure=analogRead (15);
  valeurUtile=(4.93/1023)*mesure;
  Serial.println(valeurUtile);
  digitalWrite(led1, HIGH); //turn the LED on (HIGH is the voltage level)
  digitalWrite(led2, HIGH);
  delay(onTime); //wait for a second
  digitalWrite(led1, LOW); //turn the LED off by making the voltage LOW
  digitalWrite(led2, LOW);
  delay(offTime); //wait for a second
}
