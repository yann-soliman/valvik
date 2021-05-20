#include <Arduino.h>
#include "Clock.h"
#include "Data.h"
#include "FileService.h"
#include "Electrovanne.h"
#include "MoistureSensor.h"
#include "ccronexpr.h"

class Valvik {

public:
    Valvik();
    bool isHumid();
    void turnElectrovanneOn();
    void turnElectrovanneOff();
    void setTime(TIMESTAMP time);
    TIMESTAMP getTime();
    size_t getHistory(WATERING * &history);

private : 
    SETTINGS settings;
    MoistureSensor moistureSensor;
    Electrovanne electrovanne;
    Clock clock;
    WATERING currentWattering; // Etat de l'arrosage courant
    unsigned int historyIndex; // index d'écriture de l'historique
    FileService fileService;

    void saveWateringToHistory(WATERING watering);
};