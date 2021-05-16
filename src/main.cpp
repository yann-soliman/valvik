#include "WifiAP.h"
#include "Webserver.h"

String header;

const uint8_t CAPTEUR_HUMIDITE = 13;
const uint8_t LED = BUILTIN_LED;

WifiAP * wifiAP;
Webserver * server;
Valvik * valvik;

void setup() {
  Serial.begin(115200);

  wifiAP = new WifiAP("Valvik");
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