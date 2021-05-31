#include "MoistureSensor.h"

// tout sec = 4095
// un peu d'eau = ?
// min = 1000
// humide = 0

MoistureSensor::MoistureSensor() {
    pinMode(PIN, INPUT);
}

bool MoistureSensor::isHumid() {
    uint16_t humidity = analogRead(PIN);
    Serial.printf("humidity : %i\n", humidity);
    return humidity < 512;
}

int MoistureSensor::getPercentage() {
    return map(analogRead(PIN), 0, 4095, 100, 0);
}