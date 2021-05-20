#include "MoistureSensor.h"

#define PIN 13

MoistureSensor::MoistureSensor() {
    pinMode(PIN, INPUT);
}

bool MoistureSensor::isHumid() {
    return digitalRead(PIN);
}