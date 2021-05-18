#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#define ARDUINOJSON_USE_LONG_LONG 1 // nécéssaire pour sérialiser des timestamps en ms...
#include "AsyncJson.h"
#include "ArduinoJson.h"
#include "Valvik.h"

class Webserver {
public : 
    Webserver(Valvik * valvik);

private : 
    AsyncWebServer * server;
    Valvik * valvik;

    void initRoutes();
};