#ifndef DATA_H
#define DATA_H
#define TIMESTAMP unsigned long long int

typedef struct {
    TIMESTAMP start = 0;
    TIMESTAMP end = 0;
    bool isRunning = false;
} WATERING;

typedef struct {
    TIMESTAMP start = 0;
    TIMESTAMP end = 0;
} WATERING_HISTO;

typedef struct {
    bool isStarted = true;
    bool shouldUseSensor = true;
    bool shouldUseProgrammableWatering = false;
    //cron_expr programmableWateringCron;
} SETTINGS;

#endif