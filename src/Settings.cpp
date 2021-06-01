#include "Settings.h"

Settings::Settings() {
    uint8_t * buffer;
    size_t size = fileService.get(SETTINGS_FILE_PATH, buffer);
    memcpy(&settings, buffer, size);
    delete buffer;    
}

void Settings::toggleMoistureSensor() {
    settings.shouldUseMoistureSensor = !settings.shouldUseMoistureSensor;
    fileService.save(SETTINGS_FILE_PATH, reinterpret_cast<uint8_t*>(&settings), sizeof(SETTINGS));
}

void Settings::toggleProgrammableWatering() {
    settings.shouldUseProgrammableWatering = !settings.shouldUseProgrammableWatering;
    fileService.save(SETTINGS_FILE_PATH, reinterpret_cast<uint8_t*>(&settings), sizeof(SETTINGS));
}

void Settings::setMoistureSensorThreshold(int threshold) {
    settings.moistureSensorThreshold = threshold;
    fileService.save(SETTINGS_FILE_PATH, reinterpret_cast<uint8_t*>(&settings), sizeof(SETTINGS));
}

bool Settings::shouldUseMoistureSensor() {
    return settings.shouldUseMoistureSensor;
}

bool Settings::shouldUseProgrammableWatering() {
    return settings.shouldUseProgrammableWatering;
}

int Settings::getMoistureSensorThreshold(){
    return settings.moistureSensorThreshold;
}
