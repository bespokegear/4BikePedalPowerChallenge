#pragma once

#include <Adafruit_NeoPixel.h>
#include <stdint.h>
#include "VoltageSampler.h"
#include "CurrentSampler.h"

class Player : public VoltageSampler, public CurrentSampler {
public:
    Player(uint8_t vinPin, uint16_t r1KOhm, uint16_t r2KOhm, 
           uint8_t curPin, float vSupply,
           uint8_t ledPin, uint16_t ledCount, neoPixelType ledType, 
           uint32_t ledColor, uint32_t maxColor);
    ~Player();

    // Call from setup(), initializes pins and so on
    void begin();

    // Call as frequently as possible
    void update();

    // VoltageSampler::getVoltage + diode compensation
    float getVoltage();

    // Get power in Watts
    float getPower();

    // Get max power in Watts since last reset()
    float getMaxPower();

    // Get max power in Watts since last reset()
    uint16_t getMaxIlluminatedRow() { return _maxIlluminatedRow; }

    // Set LED row (of 2) to color
    void setRowColor(uint16_t row, uint32_t color);

    // Update LED graph with power (p) in watts
    void displayPower(float p);

    // reset the recent maximum value
    void reset();

    // get a reference to _LED
    Adafruit_NeoPixel& LED() { return _LED; }

    // updates LEDs, and adds clock offset
    void showLED();

    void fillup();

private:
    Adafruit_NeoPixel _LED;
    uint32_t _ledColor;
    uint32_t _maxIlluminatedRowColor;
    uint16_t _maxIlluminatedRow;
    float _maxPower;

};
