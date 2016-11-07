#include "CurrentSampler.h"
#include "Util.h"
#include <string.h>

CurrentSampler::CurrentSampler(const uint8_t pin, float vSupply) :
    _pin(pin),
    _vSupply(vSupply),
    _count(0),
    _idx(0),
    _lastAvg(0.),
    _updated(false)
{
    for(uint8_t i=0; i<CURRENT_SAMPLES; i++) {
        _samples[i] = 0.;
    }
}

void CurrentSampler::begin()
{
#ifdef DEBUG
    Serial.println(F("CurrentSampler::begin"));
#endif
    // no need to set pinMode for analog inputs
}

void CurrentSampler::update() {
#ifdef DEBUG
    Serial.println(F("CurrentSampler::update"));
#endif
    _samples[_idx] = currentConversion(_pin, _vSupply);
    _count = _count >= CURRENT_SAMPLES ? CURRENT_SAMPLES : _count+1;
    _idx = (_idx + 1) % CURRENT_SAMPLES;
    _updated = true;
}

float CurrentSampler::getCurrent() {
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

