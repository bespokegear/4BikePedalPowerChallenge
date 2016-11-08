#include <Arduino.h>
#include <EEPROM.h>
#include "GameMode.h"
#include "Util.h"
#include "ClockDisplay.h"
#include "Players.h"

_GameMode GameMode;

_GameMode::_GameMode()
{
    _difficulty = EEPROM.read(EEPROM_LEVEL_ADDRESS);
    if (_difficulty < 1 || _difficulty > GAME_LEVEL_MAX) {
        // bad value from EEPROM
        _difficulty = 1;
    }
}

void _GameMode::begin()
{
#ifdef DEBUGFUNC
    Serial.print(F("GameMode::_begin"));
#endif
    start();
}

void _GameMode::start()
{
#ifdef DEBUG
    Serial.println(F("GameMode start"));
#endif
    _energy1 = 0;
    _startMillis = millis();
    _lastUpdate = _startMillis;
    _lastLEDUpdate = _startMillis;
    writePixels();
}

void _GameMode::stop()
{
#ifdef DEBUG
    Serial.print(F("GameMode stop"));
#endif
}

void _GameMode::reset()
{
    start();
}

void _GameMode::modeUpdate()
{
    float elapsed = (millis() - _lastUpdate) / 1000.;
    _lastUpdate = millis();
    for (uint8_t i=0; i<PLAYER_COUNT; i++) {
#ifdef DEBUG
        Serial.print(i+1);
        Serial.print(F("UP V="));
        Serial.print(Players[i].getVoltage(), 1);
        Serial.print(F(" I="));
        Serial.print(Players[i].getCurrent(), 1);
        Serial.print(F(" P="));
        Serial.print(Players[i].getPower(), 1);
        Serial.print(F("; "));
#endif
    }
#ifdef DEBUG
    Serial.println(F(""));
#endif
    writeClock();
    // Throttle writing of neopixels as too-frequent writes
    // throws off millis
    if (_lastUpdate - _lastLEDUpdate > PLAYER_LED_UPDATE_MS) {
        //writePixels();
        _lastLEDUpdate = _lastUpdate;
    }
}

void _GameMode::enterBrownout()
{
#ifdef DEBUG
    Serial.println(F("GameMode::enterBrownout"));
#endif
}

void _GameMode::exitBrownout()
{
#ifdef DEBUG
    Serial.println(F("GameMode::exitBrownout"));
#endif
}

void _GameMode::saveToEEPROM()
{
#ifdef DEBUG
    Serial.println(F("GameMode::saveToEEPROM"));
#endif
}

void _GameMode::restoreFromEEPROM()
{
#ifdef DEBUG
    Serial.println(F("GameMode::restoreFromEEPROM -> "));
#endif
}

void _GameMode::writePixels()
{
#ifdef DEBUGFUNC
    Serial.println(F("GameMode::writePixels"));
#endif
    uint16_t i;
    bool lit;
    //for (i=0; i<LED1_COUNT; i++) {
    //    bool lit = ((_energy1*LED1_COUNT) / goalEnergy()) > i;
    //    LED1.setPixelColor(i, lit ? P1_ON_COLOR : P1_OFF_COLOR);
    //}
    //LED1.show();
}

bool _GameMode::isFinished()
{
    if ((millis() - _startMillis) > GAME_LENGTH_SECONDS * 1000) {
        ClockDisplay.display("EOG");
        return true;
    } else {
        return false;
    }
}

void _GameMode::writeClock()
{
    long left10ths = ((_startMillis + GAME_LENGTH_SECONDS * 1000) - millis())/100;
    if (left10ths == _lastClock) { return; }
    uint8_t c1 = (left10ths / 100) % 10;
    uint8_t c2 = (left10ths / 10) % 10;
    uint8_t c3 = left10ths % 10;
    _lastClock = left10ths;
    ClockDisplay.display(c1==0 ? ' ' : c1, c2, c3, 2);
}

void _GameMode::setLevel(uint8_t d)
{
    _difficulty = d;
}

uint8_t _GameMode::getLevel()
{
    return _difficulty;
}

float _GameMode::goalEnergy() 
{
    return _difficulty * GAME_LEVEL_ENERGY_STEP;
}

