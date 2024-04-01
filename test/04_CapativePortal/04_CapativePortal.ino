/******************************************************************************
# Description
Example for a captive portal, taken from ESPAsyncWebserver.
https://github.com/lacamera/ESPAsyncWebServer

# Changes
* Emulate google dns server 8.8.8.8

# Settings


# Credits 
* Initial example from https://github.com/lacamera/ESPAsyncWebServer
* Licence: AGPL3
* Author:  S. Fambach
* Visit http://www.fambach.net if you want
/*****************************************************************************/
// Debuging
#include <ArduinoLog.h>

/*****************************************************************************/
// Wifi setup 

#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif

/*****************************************************************************/
// DNS setup
#include <DNSServer.h>
DNSServer dnsServer;
IPAddress apIP(8,8,8,8);
IPAddress apNetMask(255,255,255,0);
const byte DNS_PORT = 53;

/*****************************************************************************/
// Webserver setup
#include "ESPAsyncWebServer.h"
const byte HTTP_CODE = 200;
AsyncWebServer server(80);


/*****************************************************************************/
// test handler 
class TestRequestHandler : public AsyncWebHandler {
public:
  TestRequestHandler() {}
  virtual ~TestRequestHandler() {}

  bool canHandle(AsyncWebServerRequest *request){
    //request->addInterestingHeader("ANY");
     Log.traceln("URL : %s", request->url().c_str());
     Log.traceln("Host: %s", request->host().c_str());
     Log.traceln("Content Tpye: %s", request->contentType().c_str());
     //Log.traceln("%s", request->);


    return true;
  }

  void handleRequest(AsyncWebServerRequest *request) {
    AsyncResponseStream *response = request->beginResponseStream("text/html");
    response->print("<!DOCTYPE html><html><head><title>Captive Portal from Handler</title></head><body>");
    response->print("<p>This is out captive portal front page.</p>");
    response->printf("<p>You were trying to reach: http://%s%s</p>", request->host().c_str(), request->url().c_str());
    response->printf("<p>Try opening <a href='http://%s'>this link</a> instead</p>", WiFi.softAPIP().toString().c_str());
    response->print("</body></html>");
    request->send(response);
  }


};

/*****************************************************************************/
// Main Programm 

void setup(){
  //your other setup stuff...
  Serial.begin(115200);
  
  Log.begin(LOG_LEVEL_VERBOSE, &Serial);
  Log.traceln("Start setup");
  WiFi.softAPConfig(apIP, apIP, apNetMask);
  WiFi.softAP("captive-portal");
  
  dnsServer.setTTL(100);
  dnsServer.start(DNS_PORT , "*", WiFi.softAPIP());
    
  server.addHandler(new TestRequestHandler());
  server.begin();
}



void loop(){
  dnsServer.processNextRequest();
}

/*****************************************************************************/
// Rest of implementations