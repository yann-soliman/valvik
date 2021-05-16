#include <Arduino.h>
#include <WiFi.h>

class WifiAP {
public:
    WifiAP(const char* ssid, const char* passphrase = NULL);
    IPAddress getIp();
};