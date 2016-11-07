#pragma once

#include "VoltageSampler.h"
#include <Adafruit_NeoPixel.h>
#include <stdint.h>

class Player : public VoltageSampler {
public:
    Player(uint8_t vinPin, uint16_t r1KOhm, uint16_t r2KOhm, 
           uint8_t ledPin, uint16_t ledCount, neoPixelType ledType,
           uint8_t pwmPin);
    ~Player();

    // Call from setup(), initializes pins and so on
    void begin();

    void update();

private:
    Adafruit_NeoPixel _LED;

};
