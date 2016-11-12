#include <Arduino.h>
#include "DebouncedButton.h"

DebouncedButton::DebouncedButton(uint8_t pin, bool pullup) :
    RawButton(pin, pullup)
{
}

void DebouncedButton::begin(uint8_t threshold, uint8_t delay)
{
    RawButton::begin();
    _threshold = threshold;
    _delay = delay;
    _lastUpdate = 0;
    _wasPressed = false;
    setState(false);
}

// over-rides RawButton::isPressed
bool DebouncedButton::isPressed(bool once)
{
    if (!once)
        return _state;

    if (_state) {
        if (_released) {
            _released = false;
            return true;
        } 

    }
    return false;
}

bool DebouncedButton::wasPressed()
{
    bool w = _wasPressed;
    _wasPressed = false;
    return w;
}

void DebouncedButton::update()
{
    if (millis() > _lastUpdate + _delay) {
        if (RawButton::isPressed() != _state) {
            _counter++;
            if (_counter > _threshold) {
                setState(!_state);
            }
        } else if (_counter > 0) {
            _counter = 0;
        }
        _lastUpdate = millis();
    }
}

void DebouncedButton::setState(bool newState)
{
    if (newState) { 
        _wasPressed = true;
    } else {
        _released = true;
    }
    _state = newState;
    _counter = 0;
    _lastStateChange = millis();
}

