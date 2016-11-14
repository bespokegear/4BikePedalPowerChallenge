#include <Arduino.h>
#include "EndGameMode.h"
#include "ClockDisplay.h"
#include "Settings.h"
#include "Players.h"
#include "CorrectedMillis.h"
#include "Util.h"

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
    _winner = getWinner();
    Players[_winner].fillup();
    ClockDisplay.display('P', _winner+1, '!');
    _start = millis();
    _wipe = (int16_t)(playerLedCount() / 2);
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

    // wipe the loser displays
    if (_wipe >= 0) {
        for (uint8_t p=0; p<PLAYER_COUNT; p++) {
            if (p != _winner) {
                if (_wipe == (int16_t)Players[p].getMaxLED()) {
                    // dim the max indicator for non-winners
                    Players[p].LED().setPixelColor((_wipe*2), colorBrightness(PLAYER_MAX_COLOR[p], 0.5));
                    Players[p].LED().setPixelColor((_wipe*2)+1, colorBrightness(PLAYER_MAX_COLOR[p], 0.5));
                } else {
                    // for non-winners, turn off other pixels
                    Players[p].LED().setPixelColor(_wipe, 0x000000UL);
                }
                // send changed pixel data to LEDs
                Players[p].showLED();
            }
        } 
        _wipe--;
    }

    if (millis() > _last + END_GAME_UPDATE_MS) {
#ifdef DEBUG
    Serial.println(F("throb update"));
#endif
        // throb the winner
        float throb = (millis() - _start) % END_GAME_THROB_MS;
        if (throb > (END_GAME_THROB_MS/2)) {
            throb = (END_GAME_THROB_MS-throb)/(END_GAME_THROB_MS/2);
        } else {
            throb = throb/(END_GAME_THROB_MS/2);
        }
#ifdef DEBUG
        Serial.print(F("throb="));
        Serial.println(throb);
#endif
        for (int16_t i=0; i<(Players[_winner].getMaxLED()+1)*2; i++) {
            uint32_t col = colorBrightness(PLAYER_LED_COLOR[_winner], throb);
            Players[_winner].LED().setPixelColor(i, col);
            Serial.println(i);
        }
        Players[_winner].showLED();

        _last = millis();
    }
}

uint8_t _EndGameMode::getWinner()
{
    float max = 0;
    uint8_t winner = 0;
    for(uint8_t i=0; i<PLAYER_COUNT; i++) {
#ifdef DEBUG
        Serial.print(i+1);
        Serial.print(F("UP maxPower="));
        Serial.println(Players[i].getMaxPower());
#endif
        if (Players[i].getMaxPower() > max) {
            max = Players[i].getMaxPower();
            winner = i;
        }
    }
    return winner;
}

