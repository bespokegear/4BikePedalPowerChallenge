#pragma once

#include "Mode.h"

class _WaitMode : public Mode {
public:
    _WaitMode();
    void start();
    void stop();
    void modeUpdate();

};

extern _WaitMode WaitMode;
