#include <Arduino.h>

float _MillisOffsetMs = 0.;

unsigned long MillisOffset() {
    return millis() + (unsigned long)_MillisOffsetMs;
}

void addMillisOffset(float ms)
{
    _MillisOffsetMs += ms;
}

