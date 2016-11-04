#include "VoltageSampler.h"
#include "Util.h"
#include <string.h>

VoltageSampler::VoltageSampler(const uint8_t pin, uint16_t r1KOhm, uint16_t r2KOhm) :
    _pin(pin),
    _r1KOhm(r1KOhm),
    _r2KOhm(r2KOhm),
    _count(0),
    _idx(0),
    _lastAvg(0.),
    _updated(false)
{
    for(uint8_t i=0; i<VOLTAGE_SAMPLES; i++) {
        _samples[i] = 0.;
    }
}

void VoltageSampler::update() {
    _samples[_idx] = voltageConversion(_pin, _r1KOhm, _r2KOhm);
    _count = _count >= VOLTAGE_SAMPLES ? VOLTAGE_SAMPLES : _count+1;
    _idx = (_idx + 1) % VOLTAGE_SAMPLES;
    _updated = true;
}

float VoltageSampler::get() {
    if (!_updated) {
        return _lastAvg;
    }
    float sum = 0;
    for(uint8_t i=0; i<_count; i++) {
        sum += _samples[i];
    }
    _lastAvg = sum / _count;
    _updated = false;
    return _lastAvg;
}

