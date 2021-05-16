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
    Serial.println(file.name());
    file.close();
    file = root.openNextFile();
  }

  initRoutes();

}


void Webserver::initRoutes() {
  Valvik * valvik = this->valvik;

//TODO: option serveStatic ?
   server->on("/", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/index.html", "text/html");
  });

  server->on("/w3.css", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/w3.css", "text/css");
  });

  server->on("/fontawesome/css/all.css", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/fontawesome/css/all.css", "text/css");
  });

  server->on("/fontawesome/webfonts/fa.woff2", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/fontawesome/webfonts/fa.woff2", "application/octet-stream");
  });

  server->on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/script.js", "text/javascript");
  });

  server->on("/led", HTTP_GET, [valvik](AsyncWebServerRequest *request)
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
    char buffer [sizeof(unsigned long long int)*8+1];
    ultoa (valvik->getTime(),buffer,10);
    request->send(200, "text/plain", buffer);
  });

  server->on("/valvik/history", HTTP_GET, [valvik](AsyncWebServerRequest *request)
  {
    WATERING_HISTO * history = NULL;
    int size = valvik->getHistory(&history);
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
  });

  server->begin();
  Serial.println("Serveur actif!");
}
