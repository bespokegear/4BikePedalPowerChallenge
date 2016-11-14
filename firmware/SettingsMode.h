#pragma once

#include <stdint.h>
#include "Mode.h"
#include "Settings.h"

#define SETTINGS_COUNT 3

class _SettingsMode : public Mode {
public:
    _SettingsMode();
    void start();
    void stop();
    void modeUpdate();
    void display();
    bool isFinished();


private:
    int8_t _idx;
    bool _done;
};

extern _SettingsMode SettingsMode;
