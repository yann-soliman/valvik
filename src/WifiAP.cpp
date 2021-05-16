#include "WifiAP.h"


WifiAP::WifiAP(const char* ssid, const char* passphrase) {
    Serial.println("Setting AP (ssid : " + String(ssid) + ")");
    bool success = WiFi.softAP(ssid, passphrase);
    if(!success) {
        Serial.println("Failed to init AP");
    }
    Serial.print("AP IP address: ");
    Serial.println(getIp().toString());
}

IPAddress WifiAP::getIp() {
    return  WiFi.softAPIP();
}