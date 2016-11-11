#include <Arduino.h>
#include "DebouncedButton.h"
#include "CorrectedMillis.h"

DebouncedButton::DebouncedButton(uint8_t pin, bool pullup) :
    _pin(pin),
    _pullup(pullup),
    _count(0),
    _last(0),
    _lastPress(0)
{
}

void DebouncedButton::begin()
{
    if (_pullup)
        pinMode(_pin, INPUT_PULLUP);
    else
        pinMode(_pin, INPUT);
}

void DebouncedButton::update()
{
    bool on = valueNow();
    if (on) {
        if (millis() - _last >= BUTTON_DEBOUNCE_MS && _count < BUTTON_DEBOUNCE_COUNT) {
            _last = millis();
            _count++;
        }
    } else {
        _count = 0;
        _last = 0;
    }
}

bool DebouncedButton::isPressed(bool constant, bool reset)
{
    if (!constant && millis() < _lastPress + BUTTON_NOREPEAT_MS) {
        return false;
    }
    bool v = _count >= BUTTON_DEBOUNCE_COUNT;
    if (v && reset && !constant) {
        _lastPress = millis();   
    }
    return v;
}

bool DebouncedButton::valueNow()
{
    if (_pullup) {
        return !digitalRead(_pin);
    } else {
        return digitalRead(_pin);
    }
}

void DebouncedButton::set(bool on)
{
    if (on) {
        _count = BUTTON_DEBOUNCE_COUNT;
        _last = 0;
    } else {
        _count = 0;
        _last = 0;
    }
}

