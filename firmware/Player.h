#pragma once

#include "VoltageSampler.h"
#include "CurrentSampler.h"
#include <Adafruit_NeoPixel.h>
#include <stdint.h>

class Player : public VoltageSampler, public CurrentSampler {
public:
    Player(uint8_t vinPin, uint16_t r1KOhm, uint16_t r2KOhm, 
           uint8_t curPin, float vSupply,
           uint8_t ledPin, uint16_t ledCount, neoPixelType ledType, uint32_t ledColor);
    ~Player();

    // Call from setup(), initializes pins and so on
    virtual void begin();

    // Call as frequently as possible
    virtual void update();

private:
    Adafruit_NeoPixel _LED;
    uint32_t _ledColor;

};
