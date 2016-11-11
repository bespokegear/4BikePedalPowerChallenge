#include "SettingsMode.h"
#include "ButtonA.h"
#include "ButtonB.h"
#include "ClockDisplay.h"
#include "GameMode.h"
#include <Arduino.h>
#include <EEPROM.h>

_SettingsMode SettingsMode;

_SettingsMode::_SettingsMode() :
    _idx(SETTINGS_COUNT)
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
    _done = false;
    ButtonA.wasPressed();
    ButtonB.wasPressed();
    ClockDisplay.display("SEt");
}

void _SettingsMode::stop()
{
#ifdef DEBUG
    Serial.println(F("SettingsMode::stop()"));
#endif
    MaximumPowerWatts.save();
    GameDurationSeconds.save();
    NumberOfLedSegments.save();
}

void _SettingsMode::modeUpdate()
{
    if (ButtonB.wasPressed()) {
        _idx = (_idx+1) % (SETTINGS_COUNT+1);
        display();
    }

    if (ButtonA.wasPressed()) {
        switch(_idx) {
        case 0:
            MaximumPowerWatts.increment();
            break;
        case 1:
            GameDurationSeconds.increment();
            break;
        case 2:
            NumberOfLedSegments.increment();
            break;
        case SETTINGS_COUNT:
        default:
            _done = true;
            return;
            break;
        }
        display();
    }
}

void _SettingsMode::display()
{
    switch(_idx) {
    case 0:
        ClockDisplay.displaySetting('P', MaximumPowerWatts.getUi8Repr(), false);
        break;
    case 1:
        ClockDisplay.displaySetting('G', GameDurationSeconds.getUi8Repr(), false);
        break;
    case 2:
        ClockDisplay.displaySetting('L', NumberOfLedSegments.getUi8Repr(), false);
        break;
    case SETTINGS_COUNT:
    default:
        ClockDisplay.display("SAv");
        break;
    }
}

bool _SettingsMode::isFinished()
{
    return _done;
}

