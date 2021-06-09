#include "Valvik.h"

    Valvik::Valvik() {    
        currentWattering.start = 0;
        currentWattering.end = 0;
        wateringDuration = 0;
    }

    void Valvik::process() {
        if(shouldStopWatering()) {
            turnElectrovanneOff();
            wateringDuration = 0;
        }
    }

    bool Valvik::shouldStopWatering() {        
        if(electrovanne.isOn() && wateringDuration != 0) {
            TIMESTAMP duration = clock.now() - currentWattering.start;
            return duration > wateringDuration;
        }
        return false;
    }


    bool Valvik::isOn() {
        return electrovanne.isOn();
    }

    void Valvik::toggleElectrovanne(int minutes, int seconds) {
        Serial.println("Valvik : toggleElectrovanne");
        if(electrovanne.isOn()) {
            this->turnElectrovanneOff();
        }
        else {
            this->turnElectrovanneOn(minutes, seconds);
        }
    }    
    
    void Valvik::turnElectrovanneOn(int minutes, int seconds) {
        if(electrovanne.isOn()) {
            Serial.println("Valvik is already watering");
            return ;
        }        
        wateringDuration = (minutes * 60 + seconds) * 1000;
        Serial.printf("Turning electrovanne on for %d ms", wateringDuration);
        electrovanne.on();
        this->currentWattering.start = this->clock.now();
        this->currentWattering.end = 0;            
    }

    void IRAM_ATTR Valvik::turnElectrovanneOff() {
        Serial.println("Valvik : turnElectrovanneOff");
        Serial.println("test off");
        if(!electrovanne.isOn()) {
            Serial.println("Valvik is NOT watering, cannot turn it off");
            return ;
        }
        electrovanne.off();
        this->currentWattering.end = this->clock.now();

        wateringHisto.saveWateringToHistory(this->currentWattering);
    }

    void Valvik::setTime(TIMESTAMP time) {
        // Si on a un décalage de moins de 5 minutes, on considère qu'on a la bonne heure
        if(time - clock.now() > 300000) {
            Serial.print("Setting time to : ");
            Serial.println(time);
            clock.setTime(time);
        } 
        else {
            Serial.println("Tried to set time but was already within 5 minutes of the registered one");
        }
    }

    void Valvik::setMoistureSensorThreshold(int threshold) {
        settings.setMoistureSensorThreshold(threshold);
        moistureSensor.setThreshold(threshold);
    }

    Clock& Valvik::getClock() {
        return clock;
    }

    Settings& Valvik::getSettings() {
        Serial.print("Getting settings, shouldUseMoistureSensor : ");
        Serial.println(settings.shouldUseMoistureSensor());
        return settings;
    }

    WateringHisto& Valvik::getWateringHisto() {
        return wateringHisto;
    }

    MoistureSensor& Valvik::getMoistureSensor() {
        return moistureSensor;
    }

    void Valvik:: setProgrammableWateringCron(char * cron) {
        settings.prog
    }