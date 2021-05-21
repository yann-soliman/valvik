#include "WateringHisto.h"

void WateringHisto::saveWateringToHistory(WATERING watering) {        
    if(watering.end != 0) {
        Serial.println("Saving new watering history");
        fileService.add(WATERING_HISTO_FILE_PATH, reinterpret_cast<uint8_t*>(&watering), sizeof(WATERING));
    }
    else {
        Serial.println("Not saving history because it does not have an end timestamp");
    }
}

size_t WateringHisto::getHistory(WATERING * &history) {
    uint8_t * buffer;
    size_t size = fileService.get(WATERING_HISTO_FILE_PATH, buffer);
    Serial.print("Reading history from FS, size : ");
    Serial.println(size);
    history = reinterpret_cast<WATERING*>(buffer);  
    return size/sizeof(WATERING); // On retourne le nombre d'élément dans le tableau
}

void WateringHisto::reset() {
    fileService.remove(WATERING_HISTO_FILE_PATH);
}