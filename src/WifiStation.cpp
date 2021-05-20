#include "WifiStation.h"

WifiStation::WifiStation(const char* ssid, const char* passphrase) {
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, passphrase);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

IPAddress WifiStation::getIp() {
    return WiFi.localIP();
}