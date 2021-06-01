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

  server->on("/sensor/moisture/state", HTTP_GET, [valvik](AsyncWebServerRequest *request)
  {
    bool isHumid = valvik->getMoistureSensor().isHumid();
    request->send(200, "text/plain", String(isHumid));
  });

  server->on("/sensor/moisture/percentage", HTTP_GET, [valvik](AsyncWebServerRequest *request)
  {
    int value = valvik->getMoistureSensor().getPercentage();
    request->send(200, "text/plain", String(value));
  });

  server->on("/valvik/state", HTTP_GET, [valvik](AsyncWebServerRequest *request)
  {
    bool state = valvik->isOn();
    request->send(200, "text/plain", String(state));
  });
  
  server->on("/valvik/toggle", HTTP_POST, [](AsyncWebServerRequest * request){}, NULL, [valvik](AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total) {

    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject((const char*)data);
    int minutes = 10;
    int seconds = 0;
    if (root.success()) {
      minutes = root["minutes"];
      seconds = root["seconds"];
    }
    valvik->toggleElectrovanne(minutes, seconds);
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
    Settings& settings = valvik->getSettings();
    DynamicJsonBuffer jsonBuffer; 
    JsonObject &root = jsonBuffer.createObject();
    root["timestamp"] = timestamp;
    root["shouldUseMoistureSensor"] = settings.shouldUseMoistureSensor();
    root["shouldUseProgrammableWatering"] = settings.shouldUseProgrammableWatering();
    root["moistureSensorThreshold"] = settings.getMoistureSensorThreshold();
    root["currentMoistureSensorPercentage"] = valvik->getMoistureSensor().getPercentage();

    root.printTo(*response);

    request->send(response);
  });

  server->on("/settings/sensor/moisture/toggle", HTTP_PUT, [valvik](AsyncWebServerRequest *request)
  {
      valvik->getSettings().toggleMoistureSensor();
      request->send(200);
  });

  server->on("/settings/sensor/moisture/threshold", HTTP_PUT, [valvik](AsyncWebServerRequest * request){}, NULL, [valvik](AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total) {
      valvik->setMoistureSensorThreshold(atoi(reinterpret_cast<char*>(data)));
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
