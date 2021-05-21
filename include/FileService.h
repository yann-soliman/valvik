#ifndef FILE_SERVICE_H
#define FILE_SERVICE_H

#include <Arduino.h>
#include "SPIFFS.h"

class FileService { //TODO cette classe ne devrait être instanciée qu'une fois... namespace pour ça ?
public:    
    FileService();
    void save(const char * filePath, uint8_t * fileContent, size_t size);
    void add(const char * filePath, uint8_t * content, size_t size);
    size_t get(const char * filePath, uint8_t * &fileContent);
    void remove(const char * filePath);
};

#endif