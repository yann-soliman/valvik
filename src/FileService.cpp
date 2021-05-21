#include "FileService.h"

FileService::FileService() {
    if (SPIFFS.begin()){
        Serial.println(F("SPIFFS mounted correctly."));
    }else{
        Serial.println(F("!An error occurred during SPIFFS mounting"));
    }
}

void FileService::save(const char * filePath, uint8_t * fileContent, size_t size) {
    File file = SPIFFS.open(filePath, "w");
    if(!file) {
        Serial.print("Failed to open");
        Serial.println(filePath);
        return;
    } else {
        file.write(fileContent, size);
        file.close();
    }
}

void FileService::add(const char * filePath, uint8_t * content, size_t size) {
    File file = SPIFFS.open(filePath, "a+");
    if(!file) {
        Serial.print("Failed to open");
        Serial.println(filePath);
        return;
    } else {
        file.write(content, size);
        file.close();
    }
}

size_t FileService::get(const char * filePath, uint8_t * &fileContent) {
    File file = SPIFFS.open(filePath, "r");
    if(!file) {
        Serial.print("Failed to open");
        Serial.println(filePath);
        return 0;
    } else {
        fileContent = new uint8_t[file.size()];
        size_t size = file.read(fileContent, file.size());
        file.close();
        return size;
    }
    
}

void FileService::remove(const char * filePath) {
    SPIFFS.remove(filePath);
}