#include <Arduino.h>
#include <EEPROM.h>
#include "GameMode.h"
#include "Util.h"
#include "ClockDisplay.h"
#include "Players.h"
#include "Settings.h"
#include "SerialOut.h"
#include "CorrectedMillis.h"

_GameMode GameMode;

_GameMode::_GameMode()
{
}

void _GameMode::begin()
{
#ifdef DEBUGFUNC
    Serial.print(F("GameMode::_begin"));
#endif
}

void _GameMode::start()
{
#ifdef DEBUG
    Serial.println(F("GameMode start"));
#endif
    for (uint8_t i=0; i<5; i++) {
        SerialOutln(F("aSTART"));
    }
    _startMillis = millis();
    _lastUpdate = _startMillis;
    _lastLEDUpdate = _startMillis;
    for (uint8_t i=0; i<PLAYER_COUNT; i++) {
        Players[i].reset();
    }
    writePixels();
}

void _GameMode::stop()
{
#ifdef DEBUG
    Serial.print(F("GameMode stop"));
#endif
    for (uint8_t i=0; i<5; i++) {
        SerialOutln(F("aEND"));
    }
    for (uint8_t i=0; i<5; i++) {
        dumpResults();
    }
}

void _GameMode::dumpResults()
{
    // 6 chars per player, 7 for "aResult", 1 for tailing "t", and one NULL stop char
    char buf[(PLAYER_COUNT*6)+7+1+1];
    memset(buf, 0, sizeof(char)*(PLAYER_COUNT*6)+7+1+1);
    memcpy(buf, "aRESULT", 7);
    uint8_t idx = 7;
    int32_t powerInt;
    for (uint8_t i=0; i<PLAYER_COUNT; i++) {
        powerInt = Players[i].getMaxPower() > 0 ? Players[i].getMaxPower() * 100 : 0;
#ifdef DEBUG
        Serial.print(F("player="));
        Serial.print(i);
        Serial.print(F("powerInt="));
        Serial.println(powerInt);
#endif
        buf[idx++] = 'A' + i;
        buf[idx++] = '0' + ((powerInt/10000) % 10);
        buf[idx++] = '0' + ((powerInt/1000) % 10);
        buf[idx++] = '0' + ((powerInt/100) % 10);
        buf[idx++] = '0' + ((powerInt/10) % 10);
        buf[idx++] = '0' + (powerInt % 10);
    }
    // append time to buf
    buf[idx++] = 't';
    SerialOutln(buf);
}

void _GameMode::reset()
{
    start();
}

void _GameMode::modeUpdate()
{
    float elapsed = (millis() - _lastUpdate) / 1000.;
    _lastUpdate = millis();
    writeClock();
    // Throttle writing of neopixels as too-frequent writes
    // throws off millis
    if (_lastUpdate - _lastLEDUpdate > PLAYER_LED_UPDATE_MS) {
        writePixels();
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
    // 6 chars per player, 8 for the time, 1 each for: leading a, tailing t; NULL stop
    char buf[(PLAYER_COUNT*6)+8+1+1+1];
    memset(buf, 0, sizeof(char)*(PLAYER_COUNT*6)+8+1+1+1);
    buf[0] = 'a';
    uint8_t idx = 1;
    uint16_t powerInt;
    for (uint8_t i=0; i<PLAYER_COUNT; i++) {
        powerInt = Players[i].getPower() > 0 ? Players[i].getPower() * 100 : 0;
        if (powerInt<0) powerInt = 0;
        buf[idx++] = 'A' + i;
        buf[idx++] = '0' + ((powerInt/10000) % 10);
        buf[idx++] = '0' + ((powerInt/1000) % 10);
        buf[idx++] = '0' + ((powerInt/100) % 10);
        buf[idx++] = '0' + ((powerInt/10) % 10);
        buf[idx++] = '0' + (powerInt % 10);
        // TODO: send power, instead of constant (for testing)
        Players[i].displayPower(Players[i].getPower());
    }
    // append time to buf
    long time100ths = (millis()-_startMillis);
    buf[idx++] = 'T';
    buf[idx++] = '0' + ((time100ths/100000) % 10);
    buf[idx++] = '0' + ((time100ths/10000) % 10);
    buf[idx++] = '0' + ((time100ths/1000) % 10);
    buf[idx++] = '0' + ((time100ths/100) % 10);
    buf[idx++] = '0' + ((time100ths/10) % 10);
    buf[idx++] = '0' + (time100ths%10);
    buf[idx++] = 't';
    SerialOutln(buf);

}

bool _GameMode::isFinished()
{
    if (millis() > _startMillis+((unsigned long)GameDurationSeconds.get()*1000)) {
        ClockDisplay.display("EOG");
        return true;
    } else {
        return false;
    }
}

void _GameMode::writeClock()
{
    if (millis()-_startMillis < GO_DISPLAY_MS) {
        ClockDisplay.display("Go!");
    } else {
        long tenths = (GameDurationSeconds.get()*10)-((millis()-_startMillis)/100);
        if (tenths == _lastClock || tenths < 0) { return; }
        uint8_t c1, c2, c3, decPt;
        if (tenths < 1000) {
            c1 = (tenths / 100) % 10;
            c2 = (tenths / 10) % 10;
            c3 = tenths % 10;
            decPt = 2;
        } else if (tenths > -1) {
            c1 = (tenths / 1000) % 10;
            c2 = (tenths / 100) % 10;
            c3 = (tenths / 10) % 10;
            decPt = 1;
        } else {
            ClockDisplay.display("Err");
        }
        ClockDisplay.display(c1==0 ? ' ' : c1, c2, c3, decPt);
        _lastClock = tenths;
    }
}


