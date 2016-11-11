#include <Arduino.h>
#include "WaitMode.h"
#include "ClockDisplay.h"
#include "Settings.h"

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
    Serial.print(F("Settings: MaximumPowerWatts="));
    Serial.print(MaximumPowerWatts.get());
    Serial.print(F(" GameDurationSeconds="));
    Serial.print(GameDurationSeconds.get());
    Serial.print(F(" NumberOfLedSegments="));
    Serial.println(NumberOfLedSegments.get());
    Serial.println(F("setup() E"));
#endif
    // Clean button presses from other modes
    ClockDisplay.display("Hi!");
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

