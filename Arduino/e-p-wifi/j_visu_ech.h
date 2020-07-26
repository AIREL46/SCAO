/* 1j - Visualisation du contenu des échantillons
* L'objet est la visualisation du contenu des échantillons.
* Cette fonction utilise la liaison série (câble USB) entre le microcontrôleur et l'ordinateur.
* Elle se concrétise par une console sur l'écran de l'ordinateur.
*/
/**
 * 2j - Visualisation du contenu des échantillons
/**
* 3j - Visualisation du contenu des échantillons
*/
 void visu(){
 Serial.print("palier                     : ");
 Serial.println(palier, 0);//N° du palier
 //Serial.print(";");//Séparation des champs par une virgule
//  digitalClockDisplay();//Heure et date
 //printDate();
 //Serial.print(";");//Séparation des champs par une virgule
 //printTime();
 //Serial.print(";");//Séparation des champs par une virgule
 delay(100);
 Serial.print("temperature mesuree        : ");
 Serial.print(T2, 2);//Température mesurée T1 en °C sur la batterie
 Serial.println(" degres Celsius");
 //Serial.write(";"); //Séparation des champs par une virgule
 //Serial.print(T2, 2);//Température mesurée T2 en °C sur le couvercle de la casserole
 //Serial.write(";"); //Séparation des champs par une virgule
 Serial.print("temperature de consigne    : ");
 Serial.print(Tcons, 2);//Température mesurée Tcons en °C de consigne (trajectoire)
 Serial.println(" degres Celsius");
 Serial.print("duree iterative de chauffe : ");
 Serial.print(Dich, 2);//Température mesurée Tcons en °C de consigne (trajectoire)
 Serial.println(" secondes");
 Serial.print("autorisation de chauffe    : ");
 Serial.println(Ach);//Température mesurée Tcons en °C de consigne (trajectoire)
 Serial.print("duree restante             : ");
 Serial.print(Dur, 2);//Température mesurée Tcons en °C de consigne (trajectoire)
 Serial.println(" minutes");
 Serial.println();
 //Serial.write(";"); //Séparation des champs par une virgule
 //Serial.print(Vusb);//Tension mesurée Vusb en mV
 //Serial.print(";");//Séparation des champs par une virgule
 //Serial.print(Vbat_1);//Tension mesurée Vbat1 en mV
 //Serial.print(";");//Séparation des champs par une virgule
 //Serial.print(Vbat_2);//Tension mesurée Vbat1 en mV
 //Serial.print(";");//Séparation des champs par une virgule
 //Serial.print(ibat);//Courant mesuré ibat en mA
 //Serial.print(";");//Séparation des champs par une virgule
 //Serial.print(V33);//Tension mesurée V33 en mV
 //Serial.println(";");//Séparation des champs par une virgule
 //Serial.println(Ec);//Energie mesurée Ec en joules
 delay(2000);
 }
 //4j - Visualisation du contenu des échantillons
  void setup_j() {
  Serial.println ("Cuisson en cours");
  //Serial.println("t;T1 (degres C);T2 (degres C);Tcons (degres C); Vusb (mV);Vbat (mV))");
  }
  //5j - Visualisation du contenu des échantillons
