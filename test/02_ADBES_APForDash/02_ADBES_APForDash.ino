/******************************************************************************
# Description
This programm creates to which a dash button can connect. 
If a button connects the program prints the content of the request.

##Settings
* AP_SSID of this AP
* AP_PASSWD accesspoint password

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
  #include <WiFiClient.h>
  #include <WebServer.h>
  #include <mDNS.h>
#elif defined(ESP8266)
  #include <WiFiClient.h>
  #include <ESP8266WebServer.h>
  #include <ESP8266mDNS.h>

  ESP8266WebServer server(80);
  WiFiEventHandler stationConnectedHandler;

  void onStationConnected(const WiFiEventSoftAPModeStationConnected & station){
    DEBUG_PRINTLN("\n Station: ");
    DEBUG_PRINTLN(macToString(station.mac));
  }
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
// reading webpage data
//const String URL = String("http://") + String(DASH_IP);

/*
void handleRoot() {
  //server.request().send(200, "text/html", "<h1>You are connected</h1>");
  String addy = server.client().remoteIP().toString();
  //String mac = server.client().
  Serial.println(addy);
  
}*/
String macToString(const unsigned char* mac) {
  char buf[20];
  snprintf(buf, sizeof(buf), "%02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  return String(buf);
}



/*****************************************************************************/
// Main Programm

void setup() {
  Serial.begin(115200);
  DEBUG_PRINTLN("Setup");
  WiFi.persistent(false);
  WiFi.softAP(AP_SSID, AP_PASSWD);
  IPAddress myIP = WiFi.softAPIP();
  DEBUG_PRINT("AP IP address: ");
  DEBUG_PRINT(myIP);

#ifdef ESP32
  
#elif defined(ESP8266)
  stationConnectedHandler = WiFi.onSoftAPModeStationConnected(&onStationConnected);
#endif
  
}


void loop() {
    
  //server.handleClient();
}

// activate for serial event
/*void serialEvent(){
  DEBUG_PRINTLN("Serial Event");
}*/

/*****************************************************************************/
// Rest of implementations