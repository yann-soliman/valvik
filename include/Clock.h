#include <Arduino.h>
#include "Data.h"
#include "FileService.h"

class Clock {
public:
    Clock();
    void setTime(TIMESTAMP time);
    TIMESTAMP now();
    void serialPrintHumanReadable();

private:
    TIMESTAMP bootime = 0; // heure réelle de boot de l'esp
    FileService fileService;
};