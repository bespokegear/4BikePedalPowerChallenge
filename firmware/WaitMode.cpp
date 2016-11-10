#include "WaitMode.h"
#include "ClockDisplay.h"
#include <Arduino.h>

_WaitMode WaitMode;

_WaitMode::_WaitMode()
{
#ifdef DEBUG
    Serial.println(F("WaitMode::WaitMode()"));
#endif
}

void _WaitMode::start()
{
#ifdef DEBUG
    Serial.println(F("WaitMode::start()"));
#endif
    // Clean button presses from other modes
    ClockDisplay.display("=-=");
}

void _WaitMode::stop()
{
#ifdef DEBUG
    Serial.println(F("WaitMode::stop()"));
#endif
}

void _WaitMode::modeUpdate()
{
}

