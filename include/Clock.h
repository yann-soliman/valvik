#include <Arduino.h>
#include "Data.h"

class Clock {
public:
    void setTime(TIMESTAMP time);
    TIMESTAMP now();
    void serialPrintHumanReadable();

private:
    unsigned long lastSetTimeMCU = 0; // à quel timestamp (du processeur), la clock a été configurée
    TIMESTAMP time = 0; // un snapshot du timestamp de l'heure réelle
};