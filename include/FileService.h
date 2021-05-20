#ifndef FILE_SERVICE_H
#define FILE_SERVICE_H

#include <Arduino.h>
#include "SPIFFS.h"
#include "Data.h"

class FileService {
public:    
    FileService();
    void save(WATERING & wateringHisto);
    void save(SETTINGS & settings);
    void save(TIMESTAMP timestamp);
    size_t getWateringHisto(WATERING * &history);
    SETTINGS getSettings();
    TIMESTAMP getTime();
};

#endif