#include <Arduino.h>

class Electrovanne {
public:
    Electrovanne();
    void on(int minutes, int seconds);
    static void off(); // static needed pour faire un attachInterrupt...
    bool isOn();
private:
    static const int PIN = 15;    
    hw_timer_t * timer;
};