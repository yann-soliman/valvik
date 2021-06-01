#include <Arduino.h>
#include "Clock.h"
#include "Data.h"
#include "FileService.h"
#include "Electrovanne.h"
#include "MoistureSensor.h"
#include "Settings.h"
#include "WateringHisto.h"
#include "ccronexpr.h"

class Valvik {

public:
    Valvik();
    bool isOn();
    void toggleElectrovanne();
    void turnElectrovanneOn();
    void turnElectrovanneOff();
    void setTime(TIMESTAMP time);
    void setMoistureSensorThreshold(int threshold);
    Clock& getClock();
    Settings& getSettings();
    WateringHisto& getWateringHisto();
    MoistureSensor& getMoistureSensor();


private : 
    MoistureSensor moistureSensor;
    Electrovanne electrovanne;
    Clock clock;
    WATERING currentWattering; // Etat de l'arrosage courant
    FileService fileService;
    Settings settings;
    WateringHisto wateringHisto;
};