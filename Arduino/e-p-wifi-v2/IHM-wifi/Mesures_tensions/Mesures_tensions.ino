/**
 * 2d - Mesure des tensions et calcul du courant ibat
 */
 
const int Vbat_demie_1 = A3; //Initialisation de la variable Vbat_demie_1 et affectation à l'entrée analogique A0 (demie valeur de la tension Vbat avant la résistance de 1 Ohm)
const int Vbat_demie_2 = A2; //Initialisation de la variable Vbat_demie_2 et affectation à l'entrée analogique A1 (demie valeur de la tension Vbat après la résistance de 1 Ohm)
float Vbat_1; //Initialisation de la variable Vbat_1 (valeur de la tension Vbat avant la résistance de 1 Ohm)
float Vbat_2; //Initialisation de la variable Vbat_2 (valeur de la tension Vbat après la résistance de 1 Ohm)
float ibat; //Initialisation de la variable ibat (valeur du courant qui traverse la résistance de 1 Ohm)
const float Vbat_limite = 4300; //Limite supérieure de Vbat
const float Vbat_nominal = 3700; //Valeur nominale de Vbat
const float Vbat_min = 3600; //Valeur minimun de Vbat
const float Vbat_cut_off = 2800; //Cut off de Vbat*/
const int Vusb_demie = A1; //Initialisation de la variable Vusb_demie
float Vusb; //Initialisation de la variable Vusb
const int V33_demie = A0; //Initialisation de la variable V33_demie
float V33; //Initialisation de la variable V33
//Initialisation des valeurs utilisées par la fonction de changement d'échelle (fonction mathématique map() de l'arduino)
const int MaxConv = 8192; //Valeur maximale lue
const int MaxVolt = 3272; //Valeur de la tension correspondante à la valeur maximale
bool state_Vusb = false;

 /**
 * 3d - Mesure des tensions et calcul du courant ibat
 */
  //fonction de changement d'échelle (fonction mathématique map() de l'arduino)
  //La multiplication par 2.0038 compense la division par 2 (pont diviseur) et l'impédance de l'entrée du microcontrôleur pour les chiffres après la virgule.
  void mesures(){
  analogReadResolution(13);
  Vusb = map (2.0038*analogRead(Vusb_demie), 0, MaxConv, 0, MaxVolt);
  Vbat_1 = map (2.0038*analogRead(Vbat_demie_1), 0, MaxConv, 0, MaxVolt);
  Vbat_2 = map (2.0038*analogRead(Vbat_demie_2), 0, MaxConv, 0, MaxVolt);
  ibat = Vbat_1 - Vbat_2;
  V33 = map (2.0038*analogRead(V33_demie), 0, MaxConv, 0, MaxVolt);
  if (Vusb < 1000) {state_Vusb = false;}
  if (Vusb > 4000) {state_Vusb = true;}
  }
