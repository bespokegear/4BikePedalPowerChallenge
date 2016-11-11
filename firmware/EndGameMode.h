#pragma once

#include "Mode.h"

class _EndGameMode : public Mode {
public:
    _EndGameMode();
    void start();
    void stop();
    void modeUpdate();
    uint8_t getWinner();

private:
    unsigned long _start;
    unsigned long _last;

};

extern _EndGameMode EndGameMode;
