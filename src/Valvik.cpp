#include "Valvik.h"

    Valvik::Valvik() {    
        currentWattering.start = 0;
        currentWattering.end = 0;
    }

    bool Valvik::isHumid() {
        return moistureSensor.isHumid();
    }
    void Valvik::turnElectrovanneOn() {
        if(electrovanne.isOn()) {
            Serial.println("Valvik is already watering");
            return ;
        }
        
        TIMESTAMP now = this->clock.now();
        electrovanne.on();
        this->currentWattering.start = now;
        this->currentWattering.end = 0;       
    }

    void Valvik::turnElectrovanneOff() {
        if(!electrovanne.isOn()) {
            Serial.println("Valvik is NOT watering, cannot turn it off");
            return ;
        }
        electrovanne.off();
        TIMESTAMP now = this->clock.now();
        this->currentWattering.end = now;

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

    Clock& Valvik::getClock() {
        return clock;
    }

    Settings& Valvik::getSettings() {
        Serial.print("Getting settings, shouldUseHumiditySensor : ");
        Serial.println(settings.shouldUseHumiditySensor());
        return settings;
    }

    WateringHisto& Valvik::getWateringHisto() {
        return wateringHisto;
    }