#include <Arduino.h>
#include <WiFi.h>
#include <esp_wps.h>
#include <esp_wifi.h>

#define ESP_WPS_MODE      WPS_TYPE_PBC
#define ESP_MANUFACTURER  "ESPRESSIF"
#define ESP_MODEL_NUMBER  "ESP32"
#define ESP_MODEL_NAME    "ESPRESSIF IOT"
#define ESP_DEVICE_NAME   "ESP STATION"

//TOFIX : jamais testé
class WPS {
public:
    WPS(char * manufacturer, char * model_number, char * model_name, char * device_name);


private:
    void initConfig(char * manufacturer, char * model_number, char * model_name, char * device_name);
    void start();
    void stop();
    void wiFiEvent(WiFiEvent_t event, system_event_info_t info);

    esp_wps_config_t config;
};