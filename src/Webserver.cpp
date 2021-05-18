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

  server->on("/chart.min.js", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/chart.min.js", "text/javascript");
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
    int size = valvik->getHistory(history);
    Serial.print("History size : ");
    Serial.println(size);
    AsyncResponseStream *response = request->beginResponseStream("application/json");

    Serial.println("oh la k 1 ");
    DynamicJsonBuffer jsonBuffer; 
    Serial.println("oh la k 2 ");   
    JsonArray &arr = jsonBuffer.createArray();
    Serial.println("oh la k 3 ");

    for(int i = 0; i < size; i++) {
    Serial.println("oh la k 4 ");
      JsonObject& obj = arr.createNestedObject();
    Serial.println("oh la k 5 ");
      obj["start"] = history[i].start; 
    Serial.println("oh la k 6 ");
      obj["end"] =  history[i].end;
    }
    
    Serial.println("oh la k 7 ");
    arr.printTo(*response);

    Serial.println("oh la k 8 ");
    request->send(response);
    delete[] history;
  });

  server->begin();
  Serial.println("Serveur actif!");
}
