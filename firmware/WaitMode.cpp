#include <Arduino.h>
#include "WaitMode.h"
#include "ClockDisplay.h"
#include "Config.h"
#include "Players.h"
#include "Settings.h"
#include "CorrectedMillis.h"
#include "Util.h"

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
    _wipe = playerLedCount();
    _last = millis();
}

void _WaitMode::stop()
{
#ifdef DEBUG
    Serial.println(F("WaitMode::stop()"));
#endif
}

void _WaitMode::modeUpdate()
{
    if (millis() - _last > 5) {
        ClockDisplay.redisplay();
        if (_wipe > 0) {
            _wipe--;
            for (uint8_t p=0; p<PLAYER_COUNT; p++) {
                Players[p].LED().setPixelColor(_wipe, 0x000000UL);
                Players[p].showLED();
            }
        }
        _last = millis();
    }
}

