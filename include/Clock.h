#include <Arduino.h>

#define TIMESTAMP unsigned long long int

class Clock {
public:
    void setTime(TIMESTAMP time);
    TIMESTAMP now();
    void serialPrintHumanReadable();

private:
    unsigned long lastSetTimeMCU; // à quel timestamp (du processeur), la clock a été configurée
    TIMESTAMP time; // un snapshot du timestamp de l'heure réelle
};