/******************************************************************************
# Description
Connect to a dashbutton and get the provided information

##Settings
* SSID of the dash button
* IP of the start pare on the dash button

## tested with 
* ESP32 
+ ESP01 (not working)

## Credits 
* Licence: AGPL3
* Author:  S. Fambach
Visit http://www.fambach.net if you want
******************************************************************************/
#include "my_settings.h"  // copy settings file and enter own data
// #include "settings.h" // or simply use the settings file itself
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
// Libs
#ifdef ESP32
#include <WiFi.h>
#include <HTTPClient.h>

#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

//ESP8266WiFiSTAClass::enableInsecureWEP (true);

#else
#error unknown processor
#endif




/*****************************************************************************/
// XXXXXXXX

/*****************************************************************************/
// XXXXXXXX

/*****************************************************************************/
// XXXXXXXX

/*****************************************************************************/
// Try to connect to dash button and get the data


void connectToDashButton() {

  bool apFound = false;
  uint8_t channel;
  const char* ssid;

  // scan network until dashbutton appears
  DEBUG_PRINT(F("Hold dash button, pressed as long as the led begans to blink blue. Scanning: "));

  
  WiFi.mode(WIFI_STA);
  
  
  while (!apFound) {
    int n = WiFi.scanNetworks(false);
    for (int i = 0; i < n; i++) {
      //Serial.printf("%d: %s, Ch:%d (%ddBm) %s\n", i+1, WiFi.SSID(i).c_str(), WiFi.channel(i), WiFi.RSSI(i), WiFi.encryptionType(i) == ENC_TYPE_NONE ? "open" : "");
      if (String(WiFi.SSID(i).c_str()).equals(DASH_SSID)) {
        Serial.println("Button AP found");
        ssid = WiFi.SSID(i).c_str();
        channel = WiFi.channel(i);
        apFound = true;
      }
    }
    
  }

  WiFi.setHostname(HOSTNAME);
  WiFi.begin(ssid, NULL);
  int retry = RETRY_TIMES;
  while (!WiFi.status() != WL_CONNECTED && retry != 0) {
    DEBUG_PRINT(".");
    retry--;
    delay(1000);
  }

  if(WiFi.status() == WL_CONNECTED){
    DEBUG_PRINTLN(F("Connected to Dash button!"));
  } 
  WiFi.scanDelete();
  // connect to dash button
}

void disconnect() {
  WiFi.disconnect();
}

/*****************************************************************************/
// reading webpage data
const String URL = String("http://") + String(DASH_IP);

void printDashButtonGetData() {
  // check if connection is still open
  if (WiFi.status() != WL_CONNECTED) {
    DEBUG_PRINTLN(F("ERROR: Connection closed!"));
    return;
  }

  WiFiClient client;  // handling the connectgion
  HTTPClient http;    // send http requests
  DEBUG_PRINT(F("Connect to page: "));
  DEBUG_PRINT(URL);
  // check if connection is possible
  if (!http.begin(client, URL)) {
    DEBUG_PRINTLN(" ERROR: Connection possible!");
    return;
  }

  DEBUG_PRINTLN(" Success! Start to get Website Data: ");

  // get Website data
  int httpCode = http.GET();
  if (httpCode < 0) {
    DEBUG_PRINT(" ERROR: Not posisble code: ");
    DEBUG_PRINTLN(httpCode);
    return;
  }
  delay(1000);
  DEBUG_PRINTLN(F("Success. Get Payload"));
  // file found at server
  if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {

    
    String payload = http.getString();
      int ind = -1;
      if( payload.indexOf("Serial Number") > 0){

       /* int start = payload.indexOf("<td>", ind);
        DEBUG_PRINT("Start: ");
        DEBUG_PRINTLN(start);

        int end = payload.indexOf("</td>", start);
        DEBUG_PRINT("end: ");
        DEBUG_PRINTLN(end);

        DEBUG_PRINTLN(payload.substring(start,end));*/
        DEBUG_PRINTLN("Serial found");
      }
      if(payload.indexOf("MAC Address") > 0){
        DEBUG_PRINTLN("Mac found");
      }
      if(payload.indexOf("Firmware") > 0){
        DEBUG_PRINTLN("Firmware found");
      }
      if(payload.indexOf("Battery") > 0){
        DEBUG_PRINTLN("Battery found");
      }
  
  } else {
    DEBUG_PRINTLN(F("[HTTP] GET... failed, error: "));
    DEBUG_PRINTLN(http.errorToString(httpCode).c_str());
  }

  http.end();
}

/*String removeLine(String* source){
  int ind = source->indexOf("\r");

  if(ind < 0 ){
    return emptyString;
  }

  String ret = source->substring(0, ind);
  source = source->substring(ind);
  return ret;
}*/

/*****************************************************************************/
// Main Programm

void setup() {
  Serial.begin(115200);
  DEBUG_PRINTLN("Setup");
}


void loop() {

  // connect to dash button
  connectToDashButton();

  // display data
  printDashButtonGetData();

  // close connection
  disconnect();

  // wait a short time to try this again
  delay(2000);
}

// activate for serial event
/*void serialEvent(){
  DEBUG_PRINTLN("Serial Event");
}*/

/*****************************************************************************/
// Rest of implementations