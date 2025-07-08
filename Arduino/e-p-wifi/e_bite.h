/*
1e - BITE -> e_bite.h
* L'objet du Build In Test Equipment (BITE) est d'assurer la sécurité de la e-poignée.
* Cette sécurité se concrétise par un réseau de surveillance qui détecte d'éventuelles anomalies.
* L'utilisateur est informé de l'état du fonctionnement par 3 leds (verte, orange, rouge).
* Le BITE surveille la température de la batterie, les tensions continues Vusb, Vbat et V33.
*/
//2e BITE
//Initialisation des variables de surveillence de la batterie
 float T1_cons = 41.5;//Température de consigne de la batterie à ne pas dépasser
 bool alarme_temperature_bat = false;//Alarme batterie (false=normal, true=alarme)
 const float Vbat_limite_sup = 4300; //Limite supérieure de Vbat
 const float Vbat_nominal = 3700; //Valeur nominale de Vbat
 const float Vbat_limite_inf = 3600; //Valeur minimun de Vbat
 const float Vbat_cut_off = 2800; //Cut off de Vbat
 bool alarme_Vbat_2 = false;//Initialisation de la variable alarme de la tension de batterie
//Initialisation de la variable coupure secteur
 bool alarme_coupure_secteur = false;
//Initialisation des variables de surveillance de la tension Vusb
 const float Vusb_limite_sup = 5250;//Initialisation de la variable Vusb limite supérieure
 const float Vusb_limite_inf = 4500;//Initialisation de la variable Vusb limite inférieure
 bool alarme_Vusb = false;
//Initialisation des variables de surveillance de la tension 3.3V
 const float V33_limite_sup = 3465;//Initialisation de la variable V33 limite supérieure
 const float V33_limite_inf = 3135;//Initialisation de la variable V33 limite inférieure
 bool alarme_V33 = false;//Initialisation de la variable alarme V33
//3e BITE
//Alarmes batterie
//Alarme dépassement de la température de consigne de la batterie
void bite() {
if (T1 >= T1_cons) {
  alarme_temperature_bat = true;
  digitalWrite(led_pin_r, HIGH);
}
else {
  alarme_temperature_bat = false;
  digitalWrite(led_pin_r, LOW);
}
//Alarme tension de batterie hors tolérance
if (Vbat_2 > Vbat_limite_sup || Vbat_2 < Vbat_limite_inf) {
  alarme_Vbat_2 = true;
  digitalWrite(led_pin_r, HIGH);
  }
else {
  alarme_Vbat_2 = false;
  digitalWrite(led_pin_r, LOW);
}
//Alarme la tensin Vusb est hors tolérance
if (Vusb > Vusb_limite_sup || Vusb < Vusb_limite_inf) {
  alarme_Vusb = true;
  digitalWrite(led_pin_r, HIGH);
}
else {
  alarme_Vusb = false;
  digitalWrite(led_pin_r, LOW);
}
//Alarme la tension V3.3 est hors tolérance
if (V33 > V33_limite_sup || V33 < V33_limite_inf) {
  alarme_V33 = true;
  digitalWrite(led_pin_r, HIGH);
}
else {
  alarme_V33 = false;
  digitalWrite(led_pin_r, LOW);
}
//Alarme coupure secteur
int val;
val = digitalRead(P230V);
if (val == 1) {
  alarme_coupure_secteur = true;
  digitalWrite(led_pin_r, HIGH);
}
else {
  alarme_coupure_secteur = false;
  digitalWrite(led_pin_r, LOW);
}
}
//4e BITE
void setup_e() {
  pinMode(P230V, INPUT);
}
//5e BITE
