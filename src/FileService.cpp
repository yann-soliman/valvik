#include "FileService.h"

FileService::FileService() {
    if (SPIFFS.begin()){
        Serial.println(F("SPIFFS mounted correctly."));
    }else{
        Serial.println(F("!An error occurred during SPIFFS mounting"));
    }
}

void FileService::save(WATERING & wateringHisto) {
    File file = SPIFFS.open("/watering_histo.dat", "a+");
    if(!file) {
        Serial.println("Failed to open watering_histo.dat file");
        return;
    } else {
        file.write((uint8_t *) &wateringHisto, sizeof(WATERING));
        file.close();
    }
}

void FileService::save(SETTINGS & settings) {
    File file = SPIFFS.open("/settings.dat", "w");
    if(!file) {
        Serial.println("Failed to open settings.dat file");
        return;
    } else {
        file.write((uint8_t *) &settings, sizeof(SETTINGS));
        file.close();
    }
}

void FileService::save(TIMESTAMP time) {
    File file = SPIFFS.open("/time.dat", "w");
    if(!file) {
        Serial.println("Failed to open time.dat file");
        return;
    } else {
        file.write((uint8_t *) &time, sizeof(TIMESTAMP));
        file.close();
    }
}

size_t FileService::getWateringHisto(WATERING * &history) {
    File file = SPIFFS.open("/watering_histo.dat", "r");
    if(!file) {
        Serial.println("Failed to open watering_histo.dat file");
        return 0;
    } else {
        size_t size = file.size() / sizeof(WATERING);
        history = new WATERING[size];
        file.read((uint8_t *) history, file.size());
        file.close();
        return size;
    }
    
}

SETTINGS FileService::getSettings() {
    File file = SPIFFS.open("/settings.dat", "r");
    if(!file) {
        Serial.println("Failed to open settings.dat file");
        SETTINGS settings; //TODO: empty settings ? NULL ?
        return settings;
    } else {
        SETTINGS settings;
        file.read((uint8_t *) &settings, sizeof(SETTINGS));
        file.close();
        return settings;
    }
}

TIMESTAMP FileService::getTime() {
    File file = SPIFFS.open("/time.dat", "r");
    if(!file) {
        Serial.println("Failed to open time.dat file");
        return 0;
    } else {
        TIMESTAMP time;
        file.read((uint8_t *) &time, sizeof(TIMESTAMP));
        file.close();
        return time;
    }
}