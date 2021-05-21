#include <Arduino.h>
#include "Data.h"
#include "FileService.h"

#define WATERING_HISTO_FILE_PATH "/watering_histo.dat"

class WateringHisto{
public:
    void saveWateringToHistory(WATERING watering);
    size_t getHistory(WATERING * &history);
    void reset();

private:
    FileService fileService;
};