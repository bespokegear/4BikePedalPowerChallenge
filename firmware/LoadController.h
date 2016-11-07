#pragma once

#include "Config.h"
#include "VoltageSampler.h"

class LoadController {
public:
    LoadController(VoltageSampler& vin, uint8_t pwmPin);
    void begin();
    void update();
    uint8_t getPwm() { return (uint8_t)_pwm; }

private:
    VoltageSampler& _vin;
    uint8_t _pwmPin;
    long _pwm;
    float _integral;
    unsigned long _last;

};


