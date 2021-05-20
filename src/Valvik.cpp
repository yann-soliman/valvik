#include "Valvik.h"

    Valvik::Valvik() {    
        currentWattering.start = 0;
        currentWattering.end = 0;
        historyIndex = 0;
        settings = fileService.getSettings();
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

        saveWateringToHistory(this->currentWattering);        
    }
    void Valvik::turnElectrovanneOff() {
        if(!electrovanne.isOn()) {
            Serial.println("Valvik is NOT watering, cannot turn it off");
            return ;
        }
        electrovanne.off();
        TIMESTAMP now = this->clock.now();
        this->currentWattering.end = now;

        saveWateringToHistory(this->currentWattering);
    }

    void Valvik::saveWateringToHistory(WATERING watering) {        
        Serial.println("Saving new watering history");
        WATERING * wateringHisto = new WATERING(); // Pas réussi à le faire inline...
        wateringHisto->start = watering.start;
        wateringHisto->end = watering.end;

        if(watering.end != 0) { // Si on sauvegarde l'état final, on change l'index pour la prochaine sauvegarde
            this->fileService.save(*wateringHisto);
            this->historyIndex++;
        }
    }

    size_t Valvik::getHistory(WATERING * &history) {
        return this->fileService.getWateringHisto(history);
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

    TIMESTAMP Valvik::getTime() {
        return clock.now();
    }