#include "SettingsMode.h"
#include "ButtonA.h"
#include "ButtonB.h"
#include "ClockDisplay.h"
#include "GameMode.h"
#include <Arduino.h>
#include <EEPROM.h>

_SettingsMode SettingsMode;

_SettingsMode::_SettingsMode() :
    _idx(SETTINGS_COUNT),
    _done(false)
{
#ifdef DEBUG
    Serial.println(F("SettingsMode::SettingsMode()"));
#endif
}

void _SettingsMode::start()
{
#ifdef DEBUG
    Serial.println(F("SettingsMode::start()"));
#endif
    // Clear pressed buttons
    ButtonA.wasPressed();
    ButtonB.wasPressed();
    ClockDisplay.display("SEt");
}

void _SettingsMode::stop()
{
#ifdef DEBUG
    Serial.println(F("SettingsMode::stop()"));
#endif
}

void _SettingsMode::modeUpdate()
{
    if (ButtonB.wasPressed()) {
        _idx = (_idx+1) % (SETTINGS_COUNT+1);
        if (_idx == SETTINGS_COUNT) {
            ClockDisplay.display("SAv");
        } else {
            ClockDisplay.display(_idx, ' ', ' ');
        }
    }

    if (ButtonA.wasPressed()) {
        if (_idx == SETTINGS_COUNT) {
            _done = true;
        } else {
            ClockDisplay.display(_idx, ' ', 'C');
        }
    }
}

bool _SettingsMode::isFinished()
{
    return _done;
}

