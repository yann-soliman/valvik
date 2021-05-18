#include "Valvik.h"

    Valvik::Valvik(uint8_t pinCapteurHudimite, uint8_t pinElectrovanne) {
        this->pinCapteurHumidite = pinCapteurHumidite;
        this->pinElectrovanne = pinElectrovanne;
        pinMode(pinCapteurHumidite, INPUT);
        pinMode(pinElectrovanne, OUTPUT);
        digitalWrite(pinElectrovanne, LOW);
    }

    bool Valvik::isHumid() {
        Serial.print("isHumid ?...");
        bool isHumid =  !digitalRead(this->pinCapteurHumidite);
        Serial.println(isHumid);
        return isHumid;
    }
    void Valvik::turnElectrovanneOn() {
        if(this->currentWattering.isRunning) {
            Serial.println("Valvik is already watering");
            return ;
        }

        Serial.println("Turning electrovanne ON");
        TIMESTAMP now = this->clock.now();
        digitalWrite(this->pinElectrovanne, HIGH);
        Serial.print("Electrovanne turned ON at ");
        Serial.println(now);
        this->currentWattering.start = now;
        this->currentWattering.end = 0;
        this->currentWattering.isRunning = true;

        saveWateringToHistory(this->currentWattering);
        
    }
    void Valvik::turnElectrovanneOff() {
        if(!this->currentWattering.isRunning) {
            Serial.println("Valvik is NOT watering, cannot turn it off");
            return ;
        }
        Serial.println("Turning electrovanne OFF");
        digitalWrite(this->pinElectrovanne, LOW);
        TIMESTAMP now = this->clock.now();
        Serial.println("Electrovanne turned OFF at");
        Serial.println(now);
        this->currentWattering.end = now;
        this->currentWattering.isRunning = false;

        saveWateringToHistory(this->currentWattering);
    }

    void Valvik::saveWateringToHistory(WATERING watering) {
        //TODO sauvegarder sur le filesystem ?
        
        Serial.println("Saving new watering history");
        WATERING_HISTO * previousHisto =  &this->wateringHistories[this->historyIndex];

        WATERING_HISTO * wateringHisto = new WATERING_HISTO(); // Pas réussi à le faire inline...
        wateringHisto->start = watering.start;
        wateringHisto->end = watering.end;
        this->wateringHistories[this->historyIndex] = *wateringHisto;

        if(watering.end != 0) { // Si on sauvegarde l'état final, on change l'index pour la prochaine sauvegarde
            //TODO: pourquoi ce delete plante ?
            //delete previousHisto; // libère la mémoire de l'état en cours (dans le cas où on a sauvegardé l'état start uniquement)
            this->fileService.save(*wateringHisto);
            this->historyIndex++;
        }
    }

    size_t Valvik::getHistory(WATERING_HISTO * &history) {
        Serial.println((unsigned long) this->wateringHistories, HEX);
        Serial.println("KLM IS A BITCH 1");
        return this->fileService.getWateringHisto(history);
    }

    void Valvik::setTime(unsigned long long int time) {
        // Si on a un décalage de moins de 5 minutes, on considère qu'on a la bonne heure
        if(time - clock.now() > 300000) {
            clock.setTime(time);
        } 
    }

    long Valvik::getTime() {
        return clock.now();
    }