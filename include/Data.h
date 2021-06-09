#ifndef DATA_H
#define DATA_H
#define TIMESTAMP unsigned long long int

#include "ccronexpr.h"


typedef struct {
    TIMESTAMP start = 0;
    TIMESTAMP end = 0;
} WATERING;

typedef struct {
    bool shouldUseMoistureSensor = true;
    bool shouldUseProgrammableWatering = false;
    int moistureSensorThreshold = 50;
    cron_expr programmableWateringCron;
} SETTINGS;

#endif