#include "WaitMode.h"
#include "ModeButton.h"
#include "ClockDisplay.h"
#include "GameMode.h"
#include <Arduino.h>
#include <EEPROM.h>

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
    // In case the mode button was pressed while in another mode, clear it.
    ModeButton.wasPressed();
    _modeSelect = false;
}

void _WaitMode::stop()
{
#ifdef DEBUG
    Serial.println(F("WaitMode::stop()"));
#endif
    // Check to see if the level in EEPROM is different from the level
    // in GameMode, and save if necessary
    if (GameMode.getLevel() != EEPROM.read(EEPROM_LEVEL_ADDRESS)) {
#ifdef DEBUG
        Serial.print("Saving modified GameMode level to EEPROM");
#endif
#ifndef NOEEPROM
        EEPROM.write(EEPROM_LEVEL_ADDRESS, GameMode.getLevel());
#endif
    }
}

void _WaitMode::modeUpdate()
{
    if (ModeButton.wasPressed()) {
#ifdef DEBUG
    Serial.println(F("WaitMode mode button pressed."));
#endif
        uint8_t d = GameMode.getLevel();
        if (_modeSelect) {
            d = (d%GAME_LEVEL_MAX) + 1;
            GameMode.setLevel(d);
        }
        Serial.print(F("Level="));
        Serial.println(d);
        ClockDisplay.display('L', (d/10)%10, d%10);
        _modeSelect = true;
    }
}

