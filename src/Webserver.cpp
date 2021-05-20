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
    ultoa (valvik->getTime(),buffer,10);
    request->send(200, "text/plain", buffer);
  });

  server->on("/settings", HTTP_GET, [valvik](AsyncWebServerRequest *request)
  {
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    TIMESTAMP timestamp = valvik->getTime();
    DynamicJsonBuffer jsonBuffer; 
    JsonObject &root = jsonBuffer.createObject();
    root["timestamp"] = timestamp;

    root.printTo(*response);

    request->send(response);
  });

  server->on("/valvik/history", HTTP_GET, [valvik](AsyncWebServerRequest *request)
  {
    WATERING * history = NULL;
    int size = valvik->getHistory(history);
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

  server->serveStatic("/", SPIFFS, "/");

  server->begin();
  Serial.println("Serveur actif!");
}
