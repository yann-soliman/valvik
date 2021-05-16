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
        Serial.print("debug electrovanne ON");
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

        //TODO: sauvegarder l'état à l'allumage ?
        
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
        WATERING_HISTO  * wateringHisto = new WATERING_HISTO(); // Pas réussi à le faire inline...
        wateringHisto->start = watering.start;
        wateringHisto->end = watering.end;
        this->wateringHistories[this->historyIndex++] = *wateringHisto;
    }

    unsigned int Valvik::getHistory(WATERING_HISTO ** history) {
        Serial.println((unsigned long) this->wateringHistories, HEX);
        *history = this->wateringHistories; // On veut envoyer le tableau ET la taille du tableau... pas trouvé mieux que de prendre un pointeur de pointeur pour setter l'adresse du tableau dans le paramètre...
        return this->historyIndex;
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