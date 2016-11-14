#pragma once

#include "Mode.h"

class _EndGameMode : public Mode {
public:
    _EndGameMode();
    void start();
    void stop();
    void modeUpdate();

private:
    unsigned long _start;
    unsigned long _last;
    uint8_t _winner;
    int16_t _wipe;

    uint8_t getWinner();
};

extern _EndGameMode EndGameMode;
