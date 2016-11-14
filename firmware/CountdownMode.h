#pragma once

#include "Mode.h"
#include <stdint.h>

class _CountdownMode : public Mode {
public:
    _CountdownMode();
    void begin();
    void start();
    void stop();
    void modeUpdate();
    bool isFinished();

private:
    unsigned long _start;
    int8_t _lastSent;
    int8_t seconds();

};

extern _CountdownMode CountdownMode;


