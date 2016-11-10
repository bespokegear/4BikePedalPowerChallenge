#pragma once

#include "VoltageSampler.h"
#include "CurrentSampler.h"
#include <Adafruit_NeoPixel.h>
#include <stdint.h>

class Player : public VoltageSampler, public CurrentSampler {
public:
    Player(uint8_t vinPin, uint16_t r1KOhm, uint16_t r2KOhm, 
           uint8_t curPin, float vSupply,
           uint8_t ledPin, uint16_t ledCount, neoPixelType ledType, 
           uint32_t ledColor, uint32_t maxColor);
    ~Player();

    // Call from setup(), initializes pins and so on
    virtual void begin();

    // Call as frequently as possible
    virtual void update();

    // VoltageSampler::getVoltage + diode compensation
    virtual float getVoltage();

    // Get power in Watts
    virtual float getPower() { return getVoltage() * getCurrent(); }

    // Update LED graph with value (n=0 is none, n=1 is all)
    virtual void displayLED(float n);

    // reset the recent maximum value
    void reset();

private:
    Adafruit_NeoPixel _LED;
    uint32_t _ledColor;
    uint32_t _maxColor;
    uint16_t _max;

};
