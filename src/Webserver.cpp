#include "Webserver.h"


Webserver::Webserver(Valvik * valvik){
  this->server = new AsyncWebServer(80);
  this->valvik = valvik;

  if(!SPIFFS.begin()) {
    Serial.println("Erreur SPIFFS...");
    return;
  }

  File root = SPIFFS.open("/");
  File file = root.openNextFile();

  while(file)
  {
    Serial.print("File: ");
    Serial.print(file.name());
    Serial.print(" | size : ");
    Serial.println(file.size());
    file.close();
    file = root.openNextFile();
  }

  initRoutes();

}


void Webserver::initRoutes() {
  Valvik * valvik = this->valvik;

   server->on("/", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/index.html", "text/html");
  });

  server->on("/moisture-sensor", HTTP_GET, [valvik](AsyncWebServerRequest *request)
  {
    int val = valvik->isHumid();
    String humidite = String(val);
    request->send(200, "text/plain", humidite);
  });

  server->on("/valvik/on", HTTP_POST, [valvik](AsyncWebServerRequest *request)
  {
        Serial.print("/valvik/on");
    valvik->turnElectrovanneOn();
    request->send(200);
  });

  server->on("/valvik/off", HTTP_POST, [valvik](AsyncWebServerRequest *request)
  {
    valvik->turnElectrovanneOff();
    request->send(200);
  });

  server->on("/time", HTTP_PUT, [](AsyncWebServerRequest * request){}, NULL, [valvik](AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total) {
 
      // Conversion du body (le timestamp) en unsigned long long int
      TIMESTAMP timestamp = strtoull(reinterpret_cast<char*>(data), NULL, 10);
      valvik->setTime(timestamp);
 
      request->send(200);
  });

  server->on("/time", HTTP_GET, [valvik](AsyncWebServerRequest *request)
  {
    char buffer [sizeof(TIMESTAMP)*8+1];
    ultoa (valvik->getClock().now(),buffer,10);
    request->send(200, "text/plain", buffer);
  });

  server->on("/settings", HTTP_GET, [valvik](AsyncWebServerRequest *request)
  {
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    TIMESTAMP timestamp = valvik->getClock().now();
    Serial.print("Getting time settings ");
    Serial.println(timestamp);
    Settings& settings = valvik->getSettings();
    Serial.print("Settings instance : ");
    Serial.println((int) &settings, HEX);
    DynamicJsonBuffer jsonBuffer; 
    JsonObject &root = jsonBuffer.createObject();
    root["timestamp"] = timestamp;
    root["shouldUseHumiditySensor"] = settings.shouldUseHumiditySensor();
    root["shouldUseProgrammableWatering"] = settings.shouldUseProgrammableWatering();

    root.printTo(*response);

    request->send(response);
  });

  server->on("/settings/sensor/humidity/toggle", HTTP_PUT, [valvik](AsyncWebServerRequest *request)
  {
      Settings &ptr = valvik->getSettings();
      Serial.print("Settings instance : ");
      Serial.println((int) &ptr, HEX);
      valvik->getSettings().toggleHumiditySensor();
      request->send(200);
  });

  server->on("/settings/programmable-watering/toggle", HTTP_PUT, [valvik](AsyncWebServerRequest *request)
  {
      valvik->getSettings().toggleProgrammableWatering();
      request->send(200);
  });

  server->on("/valvik/history", HTTP_GET, [valvik](AsyncWebServerRequest *request)
  {
    WATERING * history = NULL;
    size_t size = valvik->getWateringHisto().getHistory(history);
    Serial.print("History size : ");
    Serial.println(size);
    AsyncResponseStream *response = request->beginResponseStream("application/json");

    DynamicJsonBuffer jsonBuffer; 
    JsonArray &arr = jsonBuffer.createArray();

    for(int i = 0; i < size; i++) {
      JsonObject& obj = arr.createNestedObject();
      obj["start"] = history[i].start; 
      obj["end"] =  history[i].end;
    }
    
    arr.printTo(*response);

    request->send(response);
    delete[] history;
  });

  server->on("/valvik/history", HTTP_DELETE, [valvik](AsyncWebServerRequest *request)
  {
      valvik->getWateringHisto().reset();
      request->send(200);
  });

  server->serveStatic("/", SPIFFS, "/");

  server->begin();
  Serial.println("Serveur actif!");
}
