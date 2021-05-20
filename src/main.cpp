#include "WifiStation.h"
#include "Webserver.h"
#include "Credentials.h" // non commité

WifiStation * wifiStation;
Webserver * server;
Valvik * valvik;

void setup() {
  Serial.begin(115200);
  
  wifiStation = new WifiStation(SSID, PASS_PHRASE);
  valvik = new Valvik();
  server = new Webserver(valvik);
}

void loop(){
}

//TODO LIST : 
// * OTA
// * DNS redirection index.html
// * Statistiques
// * Réglage plage horaire
// * Réglage utilisation capteur ou pas
// * endpoint reset stats/config
// * favicon
// * corriger décalage de 2h