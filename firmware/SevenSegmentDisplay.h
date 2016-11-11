#pragma once

#include <stdint.h>

class SevenSegmentDisplay {
public:
    SevenSegmentDisplay(uint8_t SLatchPin, uint8_t SClkPin, uint8_t SDataPin, uint8_t SEnablePin);
    ~SevenSegmentDisplay();

    // call this from setup() to init pins
    void begin();

    // blank the display
    void clear();

    // e.g. "Go!"
    void display(const char* str);

    // integer from -99 -> 999
    void display(int16_t i, bool zeroPad=false);

    // display a character and small integer
    // display('L', 1)  displays "L 1"
    // display('P', 34) displays "P34"
    void displaySetting(char c, int8_t i, bool zeroPad=false);

    // send characters or digits, e.g.
    // display('-', '5', 5) displays -55
    void display(uint8_t c1, uint8_t c2, uint8_t c3, uint8_t decimalPosition=0);

    // re-display the last thing that was displayed (display could have been 
    // corrupted due to noise)
    void redisplay();

private:
    uint8_t _SLatchPin;
    uint8_t _SClkPin;
    uint8_t _SDataPin;
    uint8_t _SEnablePin;
    uint8_t _lastValues[4];

    // Convert a digit into binary data to send to device
    uint8_t int7segment (uint8_t segmentData);

};

