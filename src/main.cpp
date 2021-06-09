#include "WifiStation.h"
#include "WifiAP.h"
#include "Webserver.h"
#include "Credentials.h" // non commité
#include <DNSServer.h>

//WifiAP * wifiAP;
WifiStation * wifiStation;
Webserver * server;
Valvik * valvik;
//DNSServer dnsServer;

void setup() {
  Serial.begin(115200);
  
  wifiStation = new WifiStation(SSID, PASS_PHRASE);
  //wifiAP = new WifiAP("Valvik");
  valvik = new Valvik();
  server = new Webserver(valvik);
    
  //Serial.print("Settings captive portal");
  //dnsServer.start(53, "*", wifiAP->getIp());
}

void loop(){
  valvik->process();
  
  //dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  //dnsServer.processNextRequest();
}

//TODO LIST : 
// * OTA
// * Réglage plage horaire
// * deep sleep strategy
// * websocket récupération état capteur
// * Serial over Wifi ?
// * Activation X minutes
