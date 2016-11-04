#include "DebouncedButton.h"
#include <Arduino.h>

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
        if (millis() - _last >= DEBOUNCETIME && _count < DEBOUNCECOUNT) {
            _last = millis();
            _count++;
        }
    } else {
        _count = 0;
        _last = 0;
    }
}

bool DebouncedButton::isPressed()
{
    if (millis() < _lastPress + NOREPRESSDELAY) {
        return false;
    }
    bool v = _count >= DEBOUNCECOUNT;
    if (v) {
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
        _count = DEBOUNCECOUNT;
        _last = 0;
    } else {
        _count = 0;
        _last = 0;
    }
}

