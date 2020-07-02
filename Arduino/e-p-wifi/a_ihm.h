/*
**************************
* Les IHM wifi et clavier*
**************************
 *
 *Définition des IHM et de leur fonction associée
 *En référence à Wikipédia, les IHM (Interactions Homme-machines) définissent les moyens mis en œuvre
 *afin qu'un humain puisse contrôler et communiquer avec une machine.
 *Dans le cadre de ce projet, les moyens mis en œuvre sont soit ceux de l'ordinateur (clavier, souri, écran) ;
 *soit ceux du smartphone ; dans les deux cas, ils sont complétés par ceux propres du microcontrôleur,
 *c'est à dire : 3 inverseurs ("ON/OFF" "sleep" et "start stop") et un jeu de leds.
 *Les IHM permettent de dialoguer avec le microcontrôleur, d'y introduire des données et de visualiser des résultats.
 *Ces IHM et leur fonction associée sont :
 * 1) le smartphone qui communique avec le microcontrôleur à l'aide de leur interface wifi respective,
 *    ou l'ordinateur via son clavier qui communique avec le microcontrôleur à l'aide du moniteur série
 *    l'un ou l'autre permet la saisie des paramètres de cuisson par l'utilisateur et leur acquisition par le microcontrôleur.
 * 2) le moniteur série permet la visualisation du contenu des échantillons ainsi que les durées de cuisson (DC1 et DC2).
 * 3) le jeu de leds permet la visualisation des états de fonctionnement (BITE)
 * 4) l'inverseur ON/OFF permet d'alimenter le microcontrôleur à partir de la batterie
 * 5) l'inverseur "sleep" à deux positions qui fournit deux états logiques (0 et 1) permet au microcontreur de fonctionner
 *    selon l'un des deux modes : normal ou sleep
 * 6) l'inverseur "start stop" à deux positions fournit deux états logiques (0 et 1) interprétés lors du déroullement du firmware
 *    de deux manières différentes liées à la fonction en cours d'exécution :
 *     - dans le cas de la fonction setup() la transition de 0 -> 1 lui permet de quitter cette même fonction pour transiter vers la fonction loop()
 *     - dans le cas de la fonction loop() la transition de 1 -> 0 lui permet d'inhiber l'autorisation de chauffe Ach.
 *Le code source des fonctions associées aux IHM se différencie en fonction du moyen de communication mis en œuvre,
 *smartphone ou ordinateur, dans la suite du programme, l'un et l'autre se distinguent par l'appellation "wifi" ou "clavier".
 *
 * 1a Les IHM
 * 1a-1 Le code source des IHM en mode "wifi"
 * Le code source des IHM en mode "wifi" s'inspire de l'exemple Arduino "simple web server" SimpleWebServerWiFi.ino
 * associé au fichier arduino_secrets.h qui permet de gérer le nom du réseau wifi ainsi que le mot de passe pour y accéder
 * Le programme SimpleWebServerWiFi.ino a été conçu pour allumer ou èteindre une led?
 * Un serveur Web permet de communiquer les paramètres de cuisson via le Web.
 * Le principe est basé sur la connection au serveur wifi "freebox_a3c" de la Freebox puis à la création d'une page web
 * dont l'adresse IP est imprimé sur le moniteur série.
 * A partir du navigateur Web, d’un ordinateur ou d’un smartphone,
 * ouvrir cette adresse IP : http: // « adresse IP » / cde
 * Où « cde » est la commande à transmettre variable en fonction du contexte.
 * Les libraries utilisées sont :
 * - SPI allows to communicate with SPI (Serial Peripheral Interface) devices, with the Arduino as the master device.
 * - WiFiNINA allows to use the Arduino MKR 1010 capabilities.
 * - RTCZero allows to use the RTC functionalities for MKR1000
 * La fonction client.print() permet d'envoyer au smarphone via le serveur Web du code HTML, par exemple :
 * client.print("<!DOCTYPE html>");
 *
 * 1a-2 - Le code source des IHM en mode "clavier"
 * Le code source des IHM en mode "clavier" utilise principalement des fonctions de la librarie Arduino
 * qui permettent d'accéder au buffer de la liaison série :
 * - Serial.available() permet de connaître le nombre de caractères disponibles dans le buffer de la liaison série
 * - Serial.read() permet de lire le caractère disponible (utilisée pour lire le gabarit)
 * - Serial.parseInt() permet de lire plusieurs nombres entiers saisis l'un à la suite de l'autre
 *   (utilisée pour lire la Durée de Cuisson (DC)).
 */

/*
 * 2a Les IHM
 * Les paramètres de cuisson sont la Durée de Cuisson (DC) et le Gabarit de cuisson (Gabarit).
 * DC est exprimée en mn sur 3 chiffres
 * Le Gabarit est un nombre entier compris entre 1 et 9.
 * Chaque Gabarit est associé à 9 paramètres :
 * la période (p),
 * le gain (G),
 * l'Intensité de chauffe(I),
 * la température d'utilisation (Tu),
 * le temps de montée Tm (mn)
 * la constante de temps Tau (mn)
 * la vitesse de consigne Vc (°C/mn)
 * l'accélération de consigne A_c (°C/mn2)
 * la durée d'anticipation ta (nombre d'itérations).
 * Ces paramètres sont décrits dans le document "brevet" (page 6 et 28) dont la version Word est accessible par le lien ci-dessous:
 * https://github.com/AIREL46/SCAO/blob/master/Brevet/SCAO/word/La%20description%20du%20SCAO%20-%20d.doc
 * La commande start stop (stsp) permet de quitter le setup pour entrer dans la boucle loop
 * Elle est commandée par un switch ON/OFF SW2 et elle se concrétise par une variable booléenne.
 * En position OFF, la variable est false correspondant à l'état stop.
 * En position ON, la variable est true correspondant à l'état start.
 * A l'état stop l'exécution du programme est maintenu dans une boucle de saisie du setup().
 * A l'état start l'exécution du programme transite dans la boucle loop().
 */
 //Initialisation des paramètres communs
#include <Arduino.h>

bool val_stsp = false;//Création de la variable booléenne start stop (stsp)
//Création des tableaux (array) des gabarits de cuisson
float Gabarit1[] = {30, 0.4, 0.275, 70, 25, 30, 2, 1.0, 4};
float Gabarit2[] = {30, 0.4, 0.275, 72.5, 22.5, 28, 2.5, 1.25, 4};
float Gabarit3[] = {30, 0.4, 0.275, 75, 20, 24, 3, 1.5, 4};
float Gabarit4[] = {30, 0.4, 0.275, 77.5, 17.5, 22, 3.5, 1.75, 4};
float Gabarit5[] = {30, 0.4, 0.275, 80, 15, 20, 4, 2.0, 4};
float Gabarit6[] = {30, 0.4, 0.342, 82.5, 12.5, 18, 4.5, 2.25, 4};
float Gabarit7[] = {30, 0.4, 0.409, 85, 10, 16, 5, 2.5, 4};
float Gabarit8[] = {30, 0.4, 0.685, 87.5, 7.5, 14, 5.5, 2.75, 4};
float Gabarit9[] = {30, 0.4, 0.685, 90, 5, 12, 6, 3.0, 4};
//Création des variables "paramètres de cuisson"
int p;//période
float G;//Gain
float I;//Intensité
float Tu;//Température d'utilisation
float Tm;//Temps de montée
int Tau;//Tau
float Vc;//Vitesse de consigne
float A_c;//Accélération de consigne
int ta;//temps d'anticipation
//Création de la variable Durée de Cuisson (DC)
long DC;
//Création de la variable Gabarit
int Gabarit;

/*
 * 2a-1 IHM WiFi
 */

#include <SPI.h> //allows to communicate with SPI (Serial Peripheral Interface) devices, with the Arduino as the master device.
#include <WiFiNINA.h> //allows to use the Arduino MKR 1010 capabilities.
#include "arduino_secrets.h"
#include <RTCZero.h> //allows to use the RTC functionalities for MKR1000

RTCZero rtc; //Create an rtc object

String gabarit_url = "GET /?g=";
String time_url = "&t=";
String check_gabarit;
String get_gabarit;
String get_time;

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                // your network key Index number (needed only for WEP)

int led =  LED_BUILTIN;
int status = WL_IDLE_STATUS;
WiFiServer server(80);

 /*
  * 2a-2 IHM clavier
  */
//Initialisation des paramètres "clavier"
//Création de la variable flag dédiée à la saisie du N° de gabarit
int flag=1;
//Création du paramètre i correspondant au nombre de chiffres à saisir pour définir la durée de cuisson
int i=3;
int reponse;

  /*
   * 3a Les IHM - Fonctions spécifiques communes
   */
   //F1 - Visualisation DC et N° de gabarit
  void visu_DC_G() {
  Serial.print ("Duree de cuisson "), Serial.print (DC); Serial.println (" mn - ");
  //Visualisation des parametres correspondants au N° du gabarit choisi
  delay (1000);
  //Affectation des paramètres de cuisson en fonction du gabarit choisi
  switch (Gabarit) {
  case 1: p=Gabarit1[0]; G=Gabarit1[1]; I=Gabarit1[2]; Tu=Gabarit1[3]; Tm=Gabarit1[4]; Tau=Gabarit1[5]; Vc=Gabarit1[6]; A_c=Gabarit1[7]; ta=Gabarit1[8];  break;
  case 2: p=Gabarit2[0]; G=Gabarit2[1]; I=Gabarit2[2]; Tu=Gabarit2[3]; Tm=Gabarit2[4]; Tau=Gabarit2[5]; Vc=Gabarit2[6]; A_c=Gabarit2[7]; ta=Gabarit2[8];  break;
  case 3: p=Gabarit3[0]; G=Gabarit3[1]; I=Gabarit3[2]; Tu=Gabarit3[3]; Tm=Gabarit3[4]; Tau=Gabarit3[5]; Vc=Gabarit3[6]; A_c=Gabarit3[7]; ta=Gabarit3[8];  break;
  case 4: p=Gabarit4[0]; G=Gabarit4[1]; I=Gabarit4[2]; Tu=Gabarit4[3]; Tm=Gabarit4[4]; Tau=Gabarit4[5]; Vc=Gabarit4[6]; A_c=Gabarit4[7]; ta=Gabarit4[8];  break;
  case 5: p=Gabarit5[0]; G=Gabarit5[1]; I=Gabarit5[2]; Tu=Gabarit5[3]; Tm=Gabarit5[4]; Tau=Gabarit5[5]; Vc=Gabarit5[6]; A_c=Gabarit5[7]; ta=Gabarit5[8];  break;
  case 6: p=Gabarit6[0]; G=Gabarit6[1]; I=Gabarit6[2]; Tu=Gabarit6[3]; Tm=Gabarit6[4]; Tau=Gabarit6[5]; Vc=Gabarit6[6]; A_c=Gabarit6[7]; ta=Gabarit6[8];  break;
  case 7: p=Gabarit7[0]; G=Gabarit7[1]; I=Gabarit7[2]; Tu=Gabarit7[3]; Tm=Gabarit7[4]; Tau=Gabarit7[5]; Vc=Gabarit7[6]; A_c=Gabarit7[7]; ta=Gabarit7[8];  break;
  case 8: p=Gabarit8[0]; G=Gabarit8[1]; I=Gabarit8[2]; Tu=Gabarit8[3]; Tm=Gabarit8[4]; Tau=Gabarit8[5]; Vc=Gabarit8[6]; A_c=Gabarit8[7]; ta=Gabarit8[8];  break;
  case 9: p=Gabarit9[0]; G=Gabarit9[1]; I=Gabarit9[2]; Tu=Gabarit9[3]; Tm=Gabarit9[4]; Tau=Gabarit9[5]; Vc=Gabarit9[6]; A_c=Gabarit9[7]; ta=Gabarit9[8];  break;
  }//switch
  Serial.print ("N° de gabarit choisi : ");  Serial.println(Gabarit); Serial.print("Ce gabarit correspond aux paramètres (p, G, I, Tu, Tm, Tau, Vc, Ac, ta) : ");
  Serial.print ("{");Serial.print (p); Serial.print (", "); Serial.print (G); Serial.print (", "); Serial.print (I); Serial.print (", "); Serial.print (Tu); Serial.print (", "); Serial.print (Tm); Serial.print (", "); Serial.print (Tau); Serial.print (", "); Serial.print (Vc); Serial.print (", "); Serial.print (A_c); Serial.print (", "); Serial.print (ta);Serial.println ("}");
  }
  //F2 - Clignotements des 4 leds
  void cli_4leds() {
    digitalWrite(led_pin_v, HIGH);
    digitalWrite(led_pin_j, HIGH);
    digitalWrite(led_pin_r, HIGH);
    digitalWrite(led_pin_b, HIGH);
    delay(1000);
    digitalWrite(led_pin_v, LOW);
    digitalWrite(led_pin_j, LOW);
    digitalWrite(led_pin_r, LOW);
    digitalWrite(led_pin_b, LOW);
    delay(1000);
    }
 /*
   * 3a-1 IHM WiFi - Fonstions spécifiques wifi
   * Les fonctions sont les suivantes :
   * F1-printWiFiStatus()
   * F2-setup_wifi()
   * F3-saisie_wifi()
   *
   */
//F1-printWiFiStatus()
void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");

  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}

//F2-setup_wifi()
  void setup_wifi() {
 rtc.begin();//Initializes the internal RTC.

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < "1.0.0") {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.print(ssid);                   // print the network name (SSID);
    Serial.println (" (10 secondes d'attente)");
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }
  server.begin();                           // start the web server on port 80
  printWiFiStatus();                        // you're connected now, so print out the status
  }

//F3-saisie_wifi() - Saisie des paramètres de cuisson en wifi
 // compare the previous status to the current status
  void saisie_wifi() {
  IPAddress ip = WiFi.localIP();
  Serial.print("Choisir gabarit et DC en ouvrant à l'aide du navigateur une fenêtre à l'adresse http://");
  Serial.print (ip);
  Serial.println (" puis valider stsp.");
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Quiet cook");
            client.print("<br>");
            //client.print("<center><img srcset=images/quietcook-01.jpg></center>");
            client.print("<form method='get'>");//Tells the browser how to send form data to a web server.
            client.print("<select name=g required>");//The HTML <select> name Attribute is used to specify a name for the drop-down list.
            client.print("<option value='0'>Select a Gabarit</option>");//Defines the data sent to the server when a form option item is selected.
            client.print("<option value='1'>Gabarit 1</option>");
            client.print("<option value='2'>Gabarit 2</option>");
            client.print("<option value='3'>Gabarit 3</option>");
            client.print("<option value='4'>Gabarit 4</option>");
            client.print("<option value='5'>Gabarit 5</option>");
            client.print("<option value='6'>Gabarit 6</option>");
            client.print("<option value='7'>Gabarit 7</option>");
            client.print("<option value='8'>Gabarit 8</option>");
            client.print("<option value='9'>Gabarit 9</option></select><br>");
            client.print("<br>");
            client.print("<br>");
            client.print("<br>");
            client.print("<input type='number' name='t'>DC(mn)<br>");//Defines the input type.
            client.print("<input type='submit' value='Submit'></form>");
            client.print(Gabarit);
            client.print("<br>");
            client.print(DC);
            client.print("<br>");
            client.print(get_gabarit);
            client.print("<br>");
            client.print(get_time);
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
        // Check to see the client request

         int x=0;

         while(x!=10){
            check_gabarit = gabarit_url + x;
            //Tests whether or not a String ends with the characters of another String.
            if(currentLine.endsWith(check_gabarit)){
                Gabarit = x;
                get_gabarit = gabarit_url + Gabarit;//Par exemple si le gabarit est 5 : GET/?=5

              }
              x++;
          }

        int i=0;

        while(i!=1000){
          get_time = (get_gabarit + time_url) + i;//Par exemple si le gabarit est 5 et la durée 60 mn : GET/?=5&t=60
          if(currentLine.endsWith(get_time)){
            DC = i;
            break;
          }
          i++;
        }
      }//if (client.available())
    }//while (client.connected())
    // close the connection:
    //printWiFiStatus();
    client.stop();
    visu_DC_G();
    Serial.println("client disonnected");
  }//if (client)
}//saisie_wifi()

/*
 * 3a-2 IHM clavier
 */

 //F1 - Fonction spécifique de saisie en mode "clavier"
 void saisie(){
  //Saisie des paramètres de cuisson
  //Saisie de la duree de cuisson DC
  byte x=(15);
  Serial.println ("Entrer DC (mn) > 0 (attention : après la frappe du premier chiffre, vous avez 5 secondes pour saisir la valeur)");
  bool bidon = true;
  Serial.setTimeout(5000);//Laps de temps pour saisir la valeur
  while (bidon) {while (Serial.available () > 0) DC = Serial.parseInt(); if (DC>0) bidon=false;}
  Serial.print (DC);
  Serial.println (" mn ");
  delay(1000);
  //Saisie du gabarit
  Gabarit=5;
  Serial.println ("Par defaut le gabarit est 5, voulez-vous le changer o/n ?");
   flag=1;
   while (flag>0) {if (Serial.available () > 0) {
   reponse=Serial.read();
   if (reponse==111 | reponse==79) {
   Serial.println ("Choisir le gabarit 1 -> 9 ");
   while (flag>0) {if (Serial.available () > 0) {
   reponse=Serial.read();
   Gabarit=reponse&x;
   if (Gabarit > 0 & Gabarit <=9){flag=flag-1;}
   delay (1000);
 }//if serial.available b
 }//while
 }//if
   if (reponse==110 | reponse==78) {flag=flag-1;}
   delay (1000);
 }//if Serial.available a
 }//while

  Serial.println ("Voulez-vous continuer ? taper O");
  flag=1;
  while (flag>0) {if (Serial.available() > 0)
    {reponse=Serial.read(); if (reponse==111 | reponse==79){flag=flag-1;}//Si le caractère frappé est O ou o

    }
  }
  }
   /*
   * 4a Les IHM - Commun
   */
   //Affectation du switch SW2 sur l'entrée digitale D1 du microcontrôleur
   //sets the digital pin 1 as input (SW2)
 void setup_a () {
  pinMode(inPin_stsp, INPUT);
  //Message d'accueil
  Serial.println ("Systeme de Cuisson Intelligent (SCI) ");
  //Choix du mode de saisie des paramètres de cuisson : mode wifi (à l'aide du smartphone)  ou mode clavier
  Serial.println("Saisie wifi (O) ou clavier (N)");
  bool wifi_clavier;//Initialisation de la variable logique wifi_clavier (true -> wifi false -> clavier)
  flag=1;
  while (flag>0) {if (Serial.available() > 0)
    {reponse=Serial.read(); if (reponse==111 | reponse==79){flag=flag-1; wifi_clavier = true;}//Si le caractère frappé est O ou o
    else {flag=flag-1; wifi_clavier = false;}
    }
  }
  delay(2000);

  //Appel de la fonction "saisie clavier"
  //cette fonction est appellée si les conditions suivantes sont remplies :
  //1) le moniteur série est connecté par l'intermédiaire du câble série entre l'ordinateur et la plateforme MKR wifi 1010
  //c'est la variable Serial qui atteste de cette connexion
  //2) le mode clavier a été choisi par l'utilisateur
  //3) la commande stsp est à l'état 0 -> stop
  if (Serial && !wifi_clavier && !val_stsp) {saisie();}
  //Appel du setup wifi
  if (wifi_clavier) {setup_wifi();}
  //Appel de la fonction saisie_wifi suivie de la lecture périodique toutes les secondes de la variable val-stsp qui permet la sortie du "while" quand elle est égale à "true"
  while (!val_stsp && wifi_clavier) {saisie_wifi(); val_stsp = digitalRead(inPin_stsp); delay(1000);}//Harmoniser avec la fonction clavier

  //Appel de la fonction v const int led_pin_b = 19;//blue led connected to digital pin 19isu_DC_G() qui affiche la durée de cuisson et le contenu du gabarit sélectionnés par l'utilisateur
  visu_DC_G();

  //Fonction boucle d'attente de la commande stsp
  //Les 4 leds clignotent
  //Dès que le switch (SW2) stsp est en position active val_stsp est "true"
  //le progamme quitte la fonction setup pour entrer dans la fonction loop
  while (!val_stsp) {val_stsp = digitalRead(inPin_stsp); cli_4leds(); Serial.print(val_stsp); Serial.println (" - attente de la cmd start");}
  //Appel du setup et de la fonction de saisie wifi
 }
  /*
   * 4a-1 IHM wifi : Vide
   */

  /*
   * 4a-2 IHM clavier : vide
   */
