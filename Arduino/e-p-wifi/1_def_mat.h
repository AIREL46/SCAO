/*
 * Définitions matérielles du microcontrôleur MKR wifi 1010
 * Ci-dessous le lien pour visualiser le PinOut du MKR wifi 1010
 * https://www.google.com/imgres?imgurl=https%3A%2F%2Fwww.henschke-geraetebau.de%2Fdr%2Fpic%2FMKR_WiFi_1010_Pinout.jpg&imgrefurl=https%3A%2F%2Fwww.henschke-geraetebau.de%2Fdr%2FZeitwaage.html&docid=k1tNmEdeWa_BMM&tbnid=jTcrNXzsoax6QM%3A&vet=10ahUKEwjMhcnf_YXnAhUBQkEAHYL5Bb8QMwgrKAAwAA..i&w=1585&h=1123&client=ubuntu&bih=951&biw=1853&q=dr-hemschke.de%2FZeitwaage.html&ved=0ahUKEwjMhcnf_YXnAhUBQkEAHYL5Bb8QMwgrKAAwAA&iact=mrc&uact=8
 * Ci-dessous le lien pour visualiser le schéma électrique du shield du MKR wifi 1010
 * https://github.com/AIREL46/SCAO/blob/master/kicad/e-p-wifi-shield/e-p-wifi.png
 */
 //Les 28 pins correspondantes au PinOut du microcontrôleur MKR wifi 1010 sont représentées ci-dessous
 //En rapport au schéma électrique, une variable est initialisée si la pin est utilisée
 //AREF
 const int V33_demie = A0; //Initialisation de la variable V33_demie sur l'entrée analogique A0
 const int Vusb_demie = A1; //Initialisation de la variable Vusb_demie sur l'entrée analogique A1
 const int Vbat_demie_2 = A2; //Initialisation de la variable Vbat_demie_2 et affectation à l'entrée analogique A2 (demie valeur de la tension Vbat après la résistance de 1 Ohm)
 const int relay = 18; //Relais connecté sur l'entrée digitale D18 (A3)
 const int led_pin_b = 19;//blue led connected to digital pin D19 (A4)
 const int BPmeross = A5;//Initialisation de la variable BPmeross et affectation de l'entrée analogique A5 (bouton poussoir de test de la prise meross)
 const int P230V = 21;//Initialisation de la variable P230V et affectation de l'entrée analogique A6 (un chargeur 5V atteste de la présence 230V)
 //const int meross = A6;//Initialisation de la variable meross et affectation de l'entrée analogique A6 (un chargeur 5V atteste de la présence 230V)
 const byte BROCHE_ONEWIRE_1 = 0;//Initialisation de la variable BROCHE_ONEWIRE_1 et affectation de l'entrée digitale D0 (connection du thermomètre digital DS18B20 pour la mesure T2)
 const int inPin_stsp = 1;    //Initialisation de la variable inPin_stsp et affectation  de l'entrée digitale D1 (connection de SW2 stsp)
 const int inPin_sleep = 2;//Initialisation de la variable inPin_sleep et affectation de l'entrée digitale D2 (connection de SW3 sleep)
 const byte BROCHE_ONEWIRE_2 = 3;//Initialisation de la variable BROCHE_ONEWIRE_2 et affectation de l'entrée digitale D3 (connection du thermomètre digital DS18B20 pour la mesure T1)
 const int speaker = 4;//Speaker connecté sur l'entrée digitale D4
 const int led_pin_v = 5;//Led verte connectée sur l'entrée digitale D5
 const int led_pin_j = 6;//Led jaune connectée sur l'entrée digitale D6
 const int led_pin_r = 7;//Led rouge connectée sur l'entrée digitale D7
 //MOSI - Interface SPI - (D8)
 //SCK  - Interface SPI - (D9)
 //MISO  - Interface SPI - (D10)
 //SDA - interface I2C - (D11)
 //const int P230V = 11;//P203V connecté sur l'entrée digitale D11
 //SCL - interface I2C - (D12)
 //Rx - Interface UART (D13)
 //Tx - Interface UART (D14)
 //RESET
 //GND
 //+3V3
 //VIN
 //+5V
