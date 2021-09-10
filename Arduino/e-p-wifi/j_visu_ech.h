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
 void visu_demo(){
 Serial.print("t                          : ");
 Serial.println(t);
 Serial.print("temperature mesuree T1     : ");
 Serial.print(T1, 2);//Température mesurée T2 en °C sur la batterie
 Serial.println(" degres Celsius");
 Serial.print("temperature mesuree T2     : ");
 Serial.print(T2, 2);//Température mesurée T2 en °C sur le couvercle de la casserole
 Serial.println(" degres Celsius");
 Serial.print("temperature de consigne    : ");
 Serial.print(Tcons, 2);//Température de consigne en °C
 Serial.println(" degres Celsius");
 Serial.print("duree iterative de chauffe : ");
 Serial.print(Dich, 2);//Durée itérative de chauffe
 Serial.println(" secondes");
 Serial.print("duree restante             : ");
 Serial.print(Dur, 2);//Durée restante
 Serial.println(" minutes");
 Serial.print("cout                       : ");
 Serial.print(cout_total, 4);//Coût en €
 Serial.println(" euros");
 Serial.print("Somme des Dich             : ");
 Serial.print(som_dich, 2);//Somme des Dich
 Serial.println(" secondes");
 Serial.print("FC1                        : ");
 Serial.println(FC1);
 Serial.print("courant                    : ");
 Serial.println(courant);
 Serial.print("puissance                  : ");
 Serial.println(puissance);
 Serial.println();
 delay(2000);
 }
 void visu_op(){
 Serial.print (t);
 Serial.write(";"); //Séparation des champs par une virgule
 Serial.print(T1, 2);//Température mesurée T2 en °C sur le couvercle de la casserole
 Serial.write(";"); //Séparation des champs par une virgule
 Serial.print(T2, 2);//Température mesurée T2 en °C sur le couvercle de la casserole
 Serial.write(";"); //Séparation des champs par une virgule
 Serial.print(Tcons);//Température de consigne
 Serial.print(";");//Séparation des champs par une virgule
 Serial.print(Dich);//Durée itérative de chauffe
 Serial.print(";");//Séparation des champs par une virgule
 Serial.print(Ach);//Durée itérative de chauffe
 Serial.print(";");//Séparation des champs par une virgule
 Serial.print(Dur);//Durée itérative de chauffe
 Serial.println(";");//Séparation des champs par une virgule
 delay(2000);
 }
 //4j - Visualisation du contenu des échantillons
  void setup_j() {
  Serial.println ("Cuisson en cours");
  Serial.println("t;T1 (degres C);T2 (degres C);Tcons (degres C);Dich (s);Ach;Dur (mn))");
  }
  //5j - Visualisation du contenu des échantillons
