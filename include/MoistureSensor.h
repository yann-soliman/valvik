#include <Arduino.h>


class MoistureSensor {
public:
    MoistureSensor(int threshold = 50);
    bool isHumid();
    int getPercentage();
    void setThreshold(int threshold);
private:
    const int PIN =  35;
    int threshold;
};