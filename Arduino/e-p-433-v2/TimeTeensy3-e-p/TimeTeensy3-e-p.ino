/*
 * TimeRTC.pde
 * example code illustrating Time library with Real Time Clock.
 * Ce programme gère la mise à l'heure de l'horloge temps réel (RTC) du Teensy 3.2.
 * Si une remise à l'heure est nécessaire, l'opérateur intervient (voir ci-dessous).
 * Dans ce cas l'heure du PC est récupéré.
 */

#include <TimeLib.h>

void setup()  {
  // set the Time library to use Teensy 3.2's RTC to keep time
  // configurer la bibliothèque Time pour utiliser le RTC de Teensy 3.2 afin de conserver l'heure
  setSyncProvider(getTeensy3Time);
  
  Serial.begin(9600);
  while (!Serial);  // Wait for Arduino Serial Monitor to open
  delay(100);
  Serial.println("test1");
//timeStatus();
//Returns the status of time sync. Three type of status are defined, with these names:
//timeNotSet     Time's clock has not been set.  The time & date are unknown.
//timeSet        Time's clock has been set.
//timeNeedsSync  Time's clock is set, but the sync has failed, so it may not be accurate.

  if (timeStatus()!= timeSet) {
    Serial.println("Unable to sync with the RTC");
  } else {
    Serial.println("RTC has set the system time");
  }
}

void loop() {
  //Pour effectuer la mise à l'heure du Teensy 3.2.
  //L'opérateur est invité à intervenir par l'intermédiaire de la console du moniteur série.
  //En tapant sucessivement à partir du clavier de l'ordinateur : un caractère quelconque puis "entrée".
  //La frappe de ces 2 caractères incrémentent un compteur associé au serial port.
  //La fonction Serial.available() permet d'obtenir le nombre contenu dans ce compteur.
  //Get the number of bytes (characters) available for reading from the serial port.
  //This is data that’s already arrived and stored in the serial receive buffer (which holds 64 bytes).
  Serial.println("Pour effectuer la mise à l'heure du Teensy 3.2, taper un caractère quelconque au clavier puis le valider en tapant sur entrée.");
  if (Serial.available() > 0) {
    Serial.println("test2");
    time_t t = processSyncMessage();
    Serial.print(" t = ");
    Serial.print(t);
    if (t != 0) {
      Serial.println("test2a");
      Teensy3Clock.set(t); // set the RTC
      setTime(t);
    }
  }
  digitalClockDisplay();  
  delay(1000);
}

void digitalClockDisplay() {
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
}

time_t getTeensy3Time()
{
  Serial.println("test4");
  return Teensy3Clock.get(); //Fonction qui récupère la date et l'heure de l'horloge temps réel du Teensy 3.2
}

/*  code to process time sync messages from the serial port   */
/*  code pour traiter les messages de synchronisation temporelle du port série */
#define TIME_HEADER  "T"   // Header tag for serial time sync message

unsigned long processSyncMessage() {
  Serial.println("test3");
  unsigned long pctime = 0L;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013 
  Serial.print(" pctime = ");
  Serial.print(pctime);
  Serial.print(" TIME_HEADER : ");
  Serial.print(TIME_HEADER);
  Serial.print(" DEFAULT_TIME ");
  Serial.print(DEFAULT_TIME);
  // Serial.find() reads data from the serial buffer until the target string of given length is found.
  //The function returns true if target string is found, false if it times out. 
  if(Serial.find(TIME_HEADER)) {
     Serial.println("test4");
     pctime = Serial.parseInt(); // parseInt() returns the first valid (long) integer number from the serial buffer.
     // Characters that are not integers (or the minus sign) are skipped. 
     return pctime;
     if( pctime < DEFAULT_TIME) { // check the value is a valid time (greater than Jan 1 2013)
       pctime = 0L; // return 0 to indicate that the time is not valid
     }
  }
  return pctime;
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
