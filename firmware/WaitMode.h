#pragma once

#include "Mode.h"

class _WaitMode : public Mode {
public:
    _WaitMode();
    void start();
    void stop();
    void modeUpdate();

private:
    uint16_t _wipe;
    unsigned long _last;

};

extern _WaitMode WaitMode;
