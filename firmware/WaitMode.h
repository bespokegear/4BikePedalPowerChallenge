#pragma once

#include "Mode.h"

class _WaitMode : public Mode {
public:
    _WaitMode();
    void start();
    void stop();
    void modeUpdate();
    bool isFinished();

private:
    uint16_t _wipe;
    unsigned long _last;
    unsigned long _start;

};

extern _WaitMode WaitMode;
