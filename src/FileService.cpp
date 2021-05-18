#include "FileService.h"

FileService::FileService() {
    if (SPIFFS.begin()){
        Serial.println(F("SPIFFS mounted correctly."));
    }else{
        Serial.println(F("!An error occurred during SPIFFS mounting"));
    }
}

void FileService::save(WATERING_HISTO & wateringHisto) {
    File file = SPIFFS.open("/wateringHisto", "a+");
    if(!file) {
        Serial.println("Failed to open wateringHisto file");
        return;
    } else {
        file.write((uint8_t *) &wateringHisto, sizeof(WATERING_HISTO));
        file.close();
    }
}

size_t FileService::getWateringHisto(WATERING_HISTO * &history) {
    File file = SPIFFS.open("/wateringHisto", "r");
    if(!file) {
        Serial.println("Failed to open wateringHisto file");
        return 0;
    } else {
        
        Serial.print("wateringHisto size = ");
        Serial.println(file.size());
        Serial.print("nb histo");
        size_t size = file.size() / sizeof(WATERING_HISTO);
        Serial.println(size);
        history = new WATERING_HISTO[size];
        
        Serial.println("about to read wateringHisto");
        size_t sizeRead = file.read((uint8_t *) &history, file.size());
        Serial.print("Read wateringHisto with size : ");
        Serial.println(sizeRead);

        Serial.println("about to close file");
        file.close();
        Serial.println("file closed");
        return size;
    }
    
}