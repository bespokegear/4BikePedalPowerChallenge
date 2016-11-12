#pragma once

#include <stdint.h>
#include "RawButton.h"
#include "Config.h"

class DebouncedButton : public RawButton {
public:
    DebouncedButton(uint8_t pin, bool pullup=true);

    // should be caled before use, i.e. from setup()
    void begin(uint8_t threshold=DEBOUNCED_BUTTON_THRESHOLD, uint8_t delay=DEBOUNCED_BUTTON_DELAY);

    // returns true if button pressed, false otherwise
    // If once==true, only returns true once until button
    // is released.
    bool isPressed(bool once=true);

    // returns true is button was pressed since the last 
    // time wasPressed has been called
    bool wasPressed();

    // must be called frequently, e.g. from interrupt callback or loop()
    void update();

private:
    uint8_t _threshold;
    uint8_t _delay;
    unsigned long _lastUpdate;
    uint8_t _counter;
    bool _state;
    unsigned long _lastStateChange;
    bool _released;
    bool _wasPressed;

    void setState(bool newState);

};


