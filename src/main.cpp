#include "WifiStation.h"
#include "Webserver.h"
#include "Credentials.h" // non commité

String header;

const uint8_t CAPTEUR_HUMIDITE = 13;
const uint8_t LED = BUILTIN_LED;

WifiStation * wifiStation;
Webserver * server;
Valvik * valvik;

void setup() {
  Serial.begin(115200);

  wifiStation = new WifiStation(SSID, PASS_PHRASE);
  valvik = new Valvik(CAPTEUR_HUMIDITE, LED);
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