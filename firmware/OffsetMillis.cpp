#include <Arduino.h>

unsigned long _MillisOffsetMs = 0;

unsigned long MillisOffset() {
    unsigned long m = millis();
    if (_MillisOffsetMs > m)
        return 0;
    else
        return m - _MillisOffsetMs;
}

void addMillisOffset(unsigned long ms)
{
    _MillisOffsetMs += ms;
}

