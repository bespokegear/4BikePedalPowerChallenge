#pragma once

#include <stdint.h>

#define DEBOUNCECOUNT   3
#define DEBOUNCETIME    10
#define NOREPRESSDELAY  300

class DebouncedButton {
public:
    DebouncedButton(uint8_t pin, bool pullup=true);
    virtual void begin();
    virtual void update();
    bool isPressed(bool reset=true);
    bool valueNow();
    void set(bool on);

private:
    uint8_t _pin;
    bool _pullup;
    uint8_t _count;
    unsigned long _last;
    unsigned long _lastPress;
};

