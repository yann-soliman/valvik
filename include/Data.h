#ifndef DATA_H
#define DATA_H
#define TIMESTAMP unsigned long long int

typedef struct {
    TIMESTAMP start = 0;
    TIMESTAMP end = 0;
} WATERING;

typedef struct {
    bool shouldUseHumiditySensor = true;
    bool shouldUseProgrammableWatering = false;
    int humiditySensorThreshold = 50;
    //cron_expr programmableWateringCron;
} SETTINGS;

#endif