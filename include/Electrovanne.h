#include <Arduino.h>

const int PIN = 2;
class Electrovanne {
public:
    Electrovanne();
    void on();
    void off();
    bool isOn();
};