#include <Arduino.h>
#include "SPIFFS.h"
#include "Data.h"

class FileService {
public:    
    FileService();
    void save(WATERING_HISTO & wateringHisto);
    void save(SETTINGS & settings);
    size_t getWateringHisto(WATERING_HISTO * &history);
    SETTINGS getSettings;

};