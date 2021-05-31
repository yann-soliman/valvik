#include "Electrovanne.h"

Electrovanne::Electrovanne() {    
    pinMode(PIN, OUTPUT);
    digitalWrite(PIN, LOW);
}

void Electrovanne::on() {
    Serial.println("Turning electrovanne ON");
    digitalWrite(PIN, HIGH);
    Serial.println("Electrovanne turned ON");
}

void Electrovanne::off() {    
    Serial.println("Turning electrovanne OFF");
    digitalWrite(PIN, LOW);
    Serial.println("Electrovanne turned OFF");
}

bool Electrovanne::isOn() {
    return digitalRead(PIN);
}