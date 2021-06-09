#include "Electrovanne.h"

Electrovanne::Electrovanne() {    
    pinMode(PIN, OUTPUT);
    digitalWrite(PIN, HIGH); // <-- HIGH car test avec led à anode commune
}

void Electrovanne::on() {
    Serial.println("Turning electrovanne ON");
    digitalWrite(PIN, LOW); // <-- LOW car test avec led à anode commune
    Serial.println("Electrovanne turned ON");

    Serial.println("Turning electrovanne ON");

    // 0 -> numéro du timer (entre 0 et 3 inclus)
    // 80 -> diviseur, 80MHz -> 80, comme ça t'es "synchro" pour les calculs (voir point 5)

    // onTimer -> fonction perso que je te donnerai après ce message
    // true -> à quel signal d'horloge tu veux te déclencher (true = signal montant, false = signal descendant)

    // 5000000 -> 80Mhz / diviseur (80) = 1 000 000 => 1 sec = 1 000 000 donc 5 000 000 = 5sec de timer (c'est à ça que sert le 80, à pouvoir bosser en secondes plus facilement)
    // false -> ne déclenche le timer qu'une fois (true pour le déclencher toutes les 5sec)

    // timerRestart -> réinitialise le timer interne, par défaut il est lancé au timerBegin (c'est là que j'en ai chié, je pensais que le timer se lançait au enable et comme je bossais en microsecondes, c'était compliqué à débugger au début ^^)

    // timerAlarmEnable -> active les interruptions pour ce timer

    // timer = timerBegin(0, 80, true);
    // timerAttachInterrupt(timer, (void (*)()) &off, true);
    // timerAlarmWrite(timer, secondBeforeTurnOff * 1000000, false);
    // delay(1000);
    // timerRestart(timer);
    // timerAlarmEnable(timer);    
}

void Electrovanne::off() {    
    Serial.println("Turning electrovanne OFF");
    digitalWrite(PIN, HIGH); // <-- HIGH car test avec led à anode commune
    Serial.println("Electrovanne turned OFF");
}

bool Electrovanne::isOn() {
    return !digitalRead(PIN);  // <-- ! car test avec led à anode commune
}