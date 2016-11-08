#include "LatchedButton.h"
#include <Arduino.h>

LatchedButton::LatchedButton(uint8_t pin, bool pullup) :
    DebouncedButton(pin, pullup),
    _pressed(false)
{
}

void LatchedButton::update()
{
    DebouncedButton::update();
    if (isPressed(false, false)) {
        _pressed = true;
    }
}

bool LatchedButton::wasPressed()
{
    if (_pressed && !isPressed(false, false)) {
        _pressed = false;
        return true;
    } else {
        return false;
    }
    
}

