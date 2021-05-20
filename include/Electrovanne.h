#include <Arduino.h>

class Electrovanne {
public:
    Electrovanne();
    void on();
    void off();
    bool isOn();
};