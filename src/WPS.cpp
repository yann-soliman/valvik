#include "WPS.h"

WPS::WPS(char * manufacturer, char * model_number, char * model_name, char * device_name) {

  //WiFi.onEvent(this->wifiEvent); <-- TOFIX
  WiFi.mode(WIFI_MODE_STA);
  Serial.println("Starting WPS");
  initConfig(manufacturer, model_number, model_name, device_name);
  start();

}

void WPS::initConfig(char * manufacturer, char * model_number, char * model_name, char * device_name){
  this->config.crypto_funcs = &g_wifi_default_wps_crypto_funcs;
  this->config.wps_type = ESP_WPS_MODE;
  strcpy(config.factory_info.manufacturer, manufacturer);
  strcpy(config.factory_info.model_number, model_number);
  strcpy(config.factory_info.model_name, model_name);
  strcpy(config.factory_info.device_name, device_name);
}


void WPS::start(){
    int ret = esp_wifi_wps_enable(&(this->config));
    if(ret){
    	Serial.println("WPS Enable Failed");
    } else if(esp_wifi_wps_start(0)){
    	Serial.println("WPS Start Failed");
    }
}


void WPS::stop(){
    if(esp_wifi_wps_disable()){
    	Serial.println("WPS Disable Failed");
    }
}

void WPS::wiFiEvent(WiFiEvent_t event, system_event_info_t info){
  switch(event){
    case SYSTEM_EVENT_STA_START:
      Serial.println("Station Mode Started");
      break;
    case SYSTEM_EVENT_STA_GOT_IP:
      Serial.println("Connected to :" + String(WiFi.SSID()));
      Serial.print("Got IP: ");
      Serial.println(WiFi.localIP());
      break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      Serial.println("Disconnected from station, attempting reconnection");
      WiFi.reconnect();
      break;
    case SYSTEM_EVENT_STA_WPS_ER_SUCCESS:
      Serial.println("WPS Successfull, stopping WPS and connecting to: " + String(WiFi.SSID()));
      stop();
      delay(10);
      WiFi.begin();
      break;
    case SYSTEM_EVENT_STA_WPS_ER_FAILED:
      Serial.println("WPS Failed, retrying");
      stop();
      start();
      break;
    case SYSTEM_EVENT_STA_WPS_ER_TIMEOUT:
      Serial.println("WPS Timedout, retrying");
      stop();
      start();
      break;
    case SYSTEM_EVENT_STA_WPS_ER_PIN:
      Serial.println("WPS_PIN = ?");// + wpspin2string(info.wps_er_pin.pin_code));
      break;
    default:
      break;
  }
}