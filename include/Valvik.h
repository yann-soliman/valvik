#include <Arduino.h>
#include "Clock.h"
#include "Data.h"
#include "FileService.h"
#include "ccronexpr.h"

class Valvik {

public:
    Valvik(uint8_t pinCapteurHudimite, uint8_t pinElectrovanne);
    bool isHumid();
    void turnElectrovanneOn();
    void turnElectrovanneOff();
    void setTime(TIMESTAMP time);
    long getTime();
    size_t getHistory(WATERING_HISTO * &history);

private : 
    uint8_t pinCapteurHumidite;
    uint8_t pinElectrovanne;
    Clock clock;
    WATERING currentWattering; // Etat courant de l'arrosage
    WATERING_HISTO wateringHistories[31]; // Historique des arrosages
    unsigned int historyIndex = 0; // index d'écriture de l'historique
    FileService fileService;

    void saveWateringToHistory(WATERING watering);
};