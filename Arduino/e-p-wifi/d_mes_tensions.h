/* 1d - Mesure des tensions et calcul du courant ibat
* La mesure des tensions est l'une des fonctions secondaires qui assure la sécurité de la e-poignée.
* La mesure consiste en une conversion analogique digitale de la tension. Cette conversion est réalisée par le microcontrôleur. La tension à mesurer est appliquée sur l'une de ses entrées analogiques. Pour tenir compte de la tension d'alimentation de 3.3V du microcontrôleur, la tension à mesurer est au préalable divisée par 2 à l'aide d'un pont diviseur constitué de 2 résistances de valeurs égales.
* La valeur mesurée est ensuite multipliée par 2, plus exactement par une valeur légérement supérieure à 2 pour compenser l'effet de l'impédance de l'entrée du microcontrôleur.
* La figure accessible par le lien ci-après explicite le principe https://github.com/AIREL46/SCAO/raw/master/wiki/map.png
*/
/* 2d - Mesure des tensions et calcul du courant ibat
*/
float Vbat_1; //Initialisation de la variable Vbat_1 (valeur de la tension Vbat avant la résistance de 1 Ohm)
float Vbat_2; //Initialisation de la variable Vbat_2 (valeur de la tension Vbat après la résistance de 1 Ohm)
float ibat; //Initialisation de la variable ibat (valeur du courant qui traverse la résistance de 1 Ohm)
float Vusb; //Initialisation de la variable Vusb
float V33; //Initialisation de la variable V33
//Initialisation des valeurs utilisées par la fonction de changement d'échelle (fonction mathématique map() de l'arduino)
const int MaxConv = 4095; //Valeur maximale lue
const int MaxVolt = 3300; //Valeur de la tension correspondante à la valeur maximale

bool state_Vusb = false;

/**
* 3d - Mesure des tensions et calcul du courant ibat
*/
//fonction de changement d'échelle (fonction mathématique map() de l'arduino)
//La multiplication par 2.0038 compense la division par 2 (pont diviseur) et l'impédance de l'entrée du microcontrôleur pour les chiffres après la virgule.
void mesures(){
Vusb = map (2.0038*analogRead(Vusb_demie), 0, MaxConv, 0, MaxVolt);
delay(120);//Pour compenser la durée necessaire à la conversion analogique digital
Vbat_1 = map (2.0038*analogRead(Vbat_demie_1), 0, MaxConv, 0, MaxVolt);
delay(120);//Pour compenser la durée necessaire à la conversion analogique digital
Vbat_2 = map (2.0038*analogRead(Vbat_demie_2), 0, MaxConv, 0, MaxVolt);
delay(120);//Pour compenser la durée necessaire à la conversion analogique digital
ibat = Vbat_1 - Vbat_2;
V33 = map (2.0038*analogRead(V33_demie), 0, MaxConv, 0, MaxVolt);
delay(120);//Pour compenser la durée necessaire à la conversion analogique digital
if (Vusb < 1000) {state_Vusb = false;}
if (Vusb > 4000) {state_Vusb = true;}
}

/*
 * 4d - Mesure des tensions et calcul du courant ibat*/
  void setup_d() {
  analogReadResolution(12);
  }
  //5d - Mesure des tensions et calcul du courant ibat
