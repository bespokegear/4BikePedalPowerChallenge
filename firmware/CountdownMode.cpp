#include "Config.h"
#include "CountdownMode.h"
#include "ClockDisplay.h"
#include <stdint.h>
#include <Arduino.h>

_CountdownMode CountdownMode;

_CountdownMode::_CountdownMode()
{
}

void _CountdownMode::begin()
{
#ifdef DEBUG
    Serial.println(F("CountdownMode::begin()"));
#endif
    start();
}

void _CountdownMode::start()
{
#ifdef DEBUG
    Serial.println(F("CountdownMode::start()"));
#endif
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
#ifdef DEBUG
    Serial.print(F("CountdownMode::modeUpdate() left="));
    Serial.println(left);
#endif
    if (_lastSent != left) {
        _lastSent = left;
        if (left > 0) {
            ClockDisplay.display(' ', left, ' ');
        } else {
            ClockDisplay.display("Go!");
        }
    }
    //for (int i=LED1_COUNT-1; i>=0; i--) {
    //    if (LED1.getPixelColor(i) != P1_OFF_COLOR) {
    //        LED1.setPixelColor(i, P1_OFF_COLOR);
    //        LED1.show();
    //        break;
    //    }
    //} 
}

int8_t _CountdownMode::seconds()
{
    return COUNTDOWN_SECONDS - ((millis()-_start)/1000);
}

bool _CountdownMode::isFinished()
{
    return seconds() < 0;
}

