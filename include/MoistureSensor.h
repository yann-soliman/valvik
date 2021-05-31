#include <Arduino.h>

const int PIN =  4;

class MoistureSensor {
public:
    MoistureSensor();
    bool isHumid();
    int getPercentage();
};