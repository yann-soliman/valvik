#include "MoistureSensor.h"

// tout sec = 4095
// un peu d'eau = ?
// min = 1000
// humide = 0

MoistureSensor::MoistureSensor(int threshold) {
    pinMode(PIN, INPUT);
    this->threshold = threshold;
}

bool MoistureSensor::isHumid() {    
    Serial.printf("threshold : %d\n", threshold);
    return getPercentage() >= threshold;
}

int MoistureSensor::getPercentage() {
    int value = analogRead(PIN);
    Serial.printf("Moisture sensor value : %d\n", value);
    return map(value, 0, 4096, 100, 0);
}

void MoistureSensor::setThreshold(int threshold) {
    this->threshold = threshold;
}