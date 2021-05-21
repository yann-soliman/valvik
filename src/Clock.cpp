#include "Clock.h"

Clock::Clock() {
    uint8_t * buffer;
    size_t size = fileService.get(CLOCK_FILE_PATH, buffer);
    memcpy(&bootime, buffer, size); // On récupère le dernier timestamp sauvegardé sur le FS
    delete buffer; 
}

void Clock::setTime(TIMESTAMP timestamp) {
    this->bootime = timestamp - millis();
    fileService.save(CLOCK_FILE_PATH, reinterpret_cast<uint8_t*>(&timestamp), sizeof(TIMESTAMP)); // On sauvegarde un timestamp plus récent dès qu'on met à jour la Clock
}

TIMESTAMP Clock::now() {
    return this->bootime + millis();
}

void Clock::serialPrintHumanReadable() {
    //TODO
}