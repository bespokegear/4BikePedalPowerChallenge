#pragma once

#include "Config.h"
#include "Mode.h"
#include <stdint.h>

class _GameMode : public Mode {
public:
    _GameMode();
    void begin();
    void start();
    void stop();
    void reset();
    void modeUpdate();
    void enterBrownout();
    void exitBrownout();
    bool isFinished();
    void saveToEEPROM();
    void restoreFromEEPROM();
    void writePixels();
    void writeClock();

private:
    unsigned long _startMillis;
    unsigned long _lastUpdate;
    unsigned long _lastLEDUpdate;
    long _lastClock;

};

extern _GameMode GameMode;

