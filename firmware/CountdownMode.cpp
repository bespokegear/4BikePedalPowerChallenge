#include <stdint.h>
#include <Arduino.h>
#include "Config.h"
#include "CountdownMode.h"
#include "ClockDisplay.h"
#include "CorrectedMillis.h"
#include "SerialOut.h"

_CountdownMode CountdownMode;

_CountdownMode::_CountdownMode()
{
}

void _CountdownMode::begin()
{
#ifdef DEBUG
    Serial.println(F("CountdownMode::begin()"));
#endif
}

void _CountdownMode::start()
{
#ifdef DEBUG
    Serial.println(F("CountdownMode::start()"));
#endif
    SerialOutln(F("aRESET")); 
    _start = millis();
    _lastSent = -1;
}

void _CountdownMode::stop()
{
#ifdef DEBUG
    Serial.println(F("CountdownMode::stop()"));
#endif
    _start = 0;
}

void _CountdownMode::modeUpdate()
{
    int8_t left = seconds();
    if (_lastSent != left) {
        _lastSent = left;
        if (left > 0) {
            ClockDisplay.display(' ', left, ' ');
        } else {
            ClockDisplay.display("Go!");
        }
    }
}

int8_t _CountdownMode::seconds()
{
    return COUNTDOWN_SECONDS - ((millis()-_start)/1000);
}

bool _CountdownMode::isFinished()
{
    return seconds() < 0;
}

