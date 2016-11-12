#pragma once

#include <stdint.h>

// Button class, lets you know the immediate state of a button
// Progagbly you don't want to use this as it is not debounced!
class RawButton {
public:
    RawButton(uint8_t pin, bool pullup=true);
    void begin();
    bool isPressed();

private:
    uint8_t _pin;
    bool _pullup;

};

