//Ecran_clavier.ino
void setup() {Serial.begin(9600); Serial.println();Serial.println("Debut : ");}
char car;
void loop() {
  if (Serial.available() >0){
  car=Serial.read();
  Serial.print ("J'ai tape : ");
  Serial.print (car);
  Serial.print (" = 0x");
  Serial.println (car,HEX);
  //}
  delay (500);
  }
}
