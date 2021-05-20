#include "Clock.h"

Clock::Clock() {
    bootime = fileService.getTime(); // On récupère le dernier timestamp sauvegardé sur le FS
}

void Clock::setTime(TIMESTAMP timestamp) {
    this->bootime = timestamp - millis();
    fileService.save(timestamp); // On sauvegarde un timestamp plus récent dès qu'on met à jour la Clock
}

TIMESTAMP Clock::now() {
    return this->bootime + millis();
}

void Clock::serialPrintHumanReadable() {
    //TODO
}