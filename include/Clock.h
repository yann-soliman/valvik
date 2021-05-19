#include <Arduino.h>
#include "Data.h"

class Clock {
public:
    void setTime(TIMESTAMP time);
    TIMESTAMP now();
    void serialPrintHumanReadable();

private:
    TIMESTAMP time = 0; // un snapshot du timestamp de l'heure réelle (recalculé pour avoir le timestamp au boot de l'esp)
};