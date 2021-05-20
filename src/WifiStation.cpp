#include "WifiStation.h"

WifiStation::WifiStation(const char* ssid, const char* passphrase) {
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.mode(WIFI_MODE_STA);
    // // Set your Static IP address
    // IPAddress local_IP(192, 168, 1, 184);
    // // Set your Gateway IP address
    // IPAddress gateway(192, 168, 1, 1);

    // IPAddress subnet(255, 255, 255, 0);
    // IPAddress primaryDNS(8, 8, 8, 8);   // optional
    // IPAddress secondaryDNS(8, 8, 4, 4); // optional
    // if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    //     Serial.println("STA Failed to configure");
    // }
    // WiFi.setHostname("Valvik");
    // WiFi.disconnect();
    WiFi.begin(ssid, passphrase);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(WiFi.status());
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