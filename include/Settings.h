#ifndef SETTINGS_H
#define SETTINGS_H
#include <Arduino.h>
#include "FileService.h"
#include "Data.h"

#define SETTINGS_FILE_PATH "/settings.dat"


struct Settings : FileService{
public:

    Settings();

    void toggleHumiditySensor();
    void toggleProgrammableWatering();
    bool shouldUseHumiditySensor();
    bool shouldUseProgrammableWatering();
    void reset();

private:
    FileService fileService;
    SETTINGS settings;
};
#endif