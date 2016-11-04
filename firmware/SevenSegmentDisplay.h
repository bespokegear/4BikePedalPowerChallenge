#pragma once

#include <stdint.h>

class SevenSegmentDisplay {
public:
    SevenSegmentDisplay(uint8_t SLatchPin, uint8_t SClkPin, uint8_t SDataPin);
    ~SevenSegmentDisplay();

    // call this from setup() to init pins
    void begin();

    // blank the display
    void clear();

    // e.g. "Go!"
    void display(char str[3]);

    // integer from -99 -> 999
    void display(int16_t i, bool zeroPad=false);

    // send characters or digits, e.g.
    // display('-', '5', 5) displays -55
    void display(uint8_t c1, uint8_t c2, uint8_t c3, uint8_t decimalPosition=0);

private:
    uint8_t _SLatchPin;
    uint8_t _SClkPin;
    uint8_t _SDataPin;

    // Convert a digit into binary data to send to device
    uint8_t int7segment (uint8_t segmentData);

};

