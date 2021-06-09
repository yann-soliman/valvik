#ifndef SETTINGS_H
#define SETTINGS_H
#include <Arduino.h>
#include "FileService.h"
#include "Data.h"

#define SETTINGS_FILE_PATH "/settings.dat"


struct Settings : FileService{
public:

    Settings();

    void toggleMoistureSensor();
    void toggleProgrammableWatering();
    void setMoistureSensorThreshold(int threshold);
    bool shouldUseMoistureSensor();
    bool shouldUseProgrammableWatering();
    int getMoistureSensorThreshold();
    void setProgrammableWateringCron(char * cron);
    cron_expr getProgrammableWateringCron();
    void reset();

private:
    FileService fileService;
    SETTINGS settings;
};
#endif