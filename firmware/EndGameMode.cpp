#include <Arduino.h>
#include "EndGameMode.h"
#include "ClockDisplay.h"
#include "Settings.h"
#include "Players.h"
#include "CorrectedMillis.h"

_EndGameMode EndGameMode;

_EndGameMode::_EndGameMode()
{
}

void _EndGameMode::start()
{
#ifdef DEBUG
    Serial.println(F("EndGameMode::start()"));
    Serial.print(F("Settings: MaximumPowerWatts="));
    Serial.print(MaximumPowerWatts.get());
    Serial.print(F(" GameDurationSeconds="));
    Serial.print(GameDurationSeconds.get());
    Serial.print(F(" NumberOfLedSegments="));
    Serial.println(NumberOfLedSegments.get());
    Serial.println(F("setup() E"));
#endif
    // Clean button presses from other modes
    ClockDisplay.display('P', getWinner(), '!');
    _start = millis();
}

void _EndGameMode::stop()
{
#ifdef DEBUG
    Serial.println(F("EndGameMode::stop()"));
#endif
    // ensure we leave the display turned on
    ClockDisplay.setEnable(true);
}

void _EndGameMode::modeUpdate()
{
    // flash clock output
    ClockDisplay.setEnable(((millis() - _start)/800)%2==0);
    _last = millis();
}

uint8_t _EndGameMode::getWinner()
{
    float max = 0;
    uint8_t winner = 0;
    for(uint8_t i=0; i<PLAYER_COUNT; i++) {
        if (Players[i].getMaxPower() > max) {
            max = Players[i].getMaxPower();
            winner = i;
        }
    }
    return winner+1;
}

