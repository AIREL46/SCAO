int led1 = 12;//This is the PIN the LED is controlled from
int led2 = 13;
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
  char car;
  if (Serial.available() > 0) {car = Serial.read(); Serial.print (car);}
  int mesure;
  double valeurUtile;
  mesure=analogRead (15);
  //valeurUtile=(4.93/1023)*mesure;
  valeurUtile=map (mesure, 0, 1023, 0, 4.93);
  Serial.print(mesure);
  Serial.print(" - ");
  Serial.println(valeurUtile);
  delay (500);
  if (valeurUtile < 4.93*0.25 || valeurUtile==0) {digitalWrite(led1, LOW); digitalWrite(led2, LOW);}
  if (valeurUtile > 4.93*0.25 && valeurUtile < 4.93*0.50) {digitalWrite(led1, HIGH); digitalWrite(led2, LOW);}
  if (valeurUtile > 4.93*0.50 && valeurUtile < 4.93*0.75) {digitalWrite(led1, LOW); digitalWrite(led2, HIGH);}
  if (valeurUtile > 4.93*0.75 || valeurUtile == 4.93) {digitalWrite(led1, HIGH); digitalWrite(led2, HIGH);}
}
