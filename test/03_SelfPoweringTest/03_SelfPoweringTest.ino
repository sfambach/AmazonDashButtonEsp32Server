/******************************************************************************
# Description
Self powering ESP01

##Settings
POWER_PIN Pin to power the micro controller


## Credits 
* Licence: AGPL3
* Author:  S. Fambach
Visit http://www.fambach.net if you want
******************************************************************************/

/*****************************************************************************/
// Debuging

#define DEBUG
#ifdef DEBUG
#define DEBUG_PRINTLN(x) Serial.println(x)
#define DEBUG_PRINT(x) Serial.print(x)
#else
#define DEBUG_PRINTLN(x)
#define DEBUG_PRINT(x)
#endif

/*****************************************************************************/
#include "my_settings.h"  // copy settings file and enter own data
// #include "settings.h" // or simply use the settings file itself
/*****************************************************************************/
// XXXXXXXX

/*****************************************************************************/
// XXXXXXXX

/*****************************************************************************/
// XXXXXXXX

/*****************************************************************************/
// XXXXXXXX

/*****************************************************************************/
// XXXXXXXX


/*****************************************************************************/
// Main Programm 

void setup() {

  pinMode(POWER_PIN, OUTPUT);
  digitalWrite(POWER_PIN, HIGH);

  Serial.begin(115200);
  DEBUG_PRINTLN("Done ");
  //digitalWrite(POWER_PIN, LOW);
}


void loop() {
  //DEBUG_PRINTLN("Main Loop");
}

// activate for serial event
/*void serialEvent(){
  DEBUG_PRINTLN("Serial Event");
}*/

/*****************************************************************************/
// Rest of implementations