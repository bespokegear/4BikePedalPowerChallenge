#pragma once

#include "Config.h"
#include <stdint.h>

class CurrentSampler {
public:
    CurrentSampler(const uint8_t pin, float vSupply);
    ~CurrentSampler() {;}
    void begin();
    void update();
    float getCurrent();
    uint8_t getPin() { return _pin; }

private:
    uint8_t _pin;
    float _vSupply;
    uint8_t _count;
    uint8_t _idx;
    float _lastAvg;
    bool _updated;
    float _samples[CURRENT_SAMPLES];

};

