#include <Arduino.h>
#include <WiFi.h>

class WifiStation {
public:
    WifiStation(const char* ssid, const char* passphrase = NULL);
    IPAddress getIp();
};