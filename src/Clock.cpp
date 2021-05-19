#include "Clock.h"

void Clock::setTime(TIMESTAMP time) {
    this->time = time - millis();
}

TIMESTAMP Clock::now() {
    return this->time + millis();
}

void Clock::serialPrintHumanReadable() {
    //TODO
}