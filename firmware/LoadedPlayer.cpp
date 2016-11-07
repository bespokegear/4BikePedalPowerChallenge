#include "Config.h"
#include "LoadedPlayer.h"
#include <Arduino.h>

LoadedPlayer::LoadedPlayer(uint8_t vinPin, uint16_t r1KOhm, uint16_t r2KOhm, 
                           uint8_t ledPin, uint16_t ledCount, neoPixelType ledType,
                           uint8_t pwmPin) :
    Player(vinPin, r1KOhm, r2KOhm, ledPin, ledCount, ledType),
    _pwmPin(pwmPin),
    _pwmLoad(0),
    _integral(0),
    _last(0)
{
}

void LoadedPlayer::begin()
{
#ifdef DEBUG
    Serial.println(F("LoadedPlayer::begin"));
#endif
    Player::begin();
    pinMode(_pwmPin, OUTPUT);
    digitalWrite(_pwmPin, LOW);
}

void LoadedPlayer::update()
{
    Player::update();
#ifdef DEBUG
    Serial.println(F("LoadedPlayer::update"));
#endif
    if (millis() < _last + LOAD_CONTROLLER_PERIOD_MS) {
        return;
    }
    _last = millis();
    if (this->getVoltage() >= LOAD_CONTROLLER_SET_POINT - LOAD_CONTROLLER_HYSTERESIS) {
        float error;
        float proportional;
        // in float V and vary up to > 1
        // if the value is 1000 then the voltage is at 14V and the FET should be fully ON
        error = this->getVoltage() - LOAD_CONTROLLER_SET_POINT;
        // _integral value will go down when _error is negative
        _integral = _integral + error;
        // proportional gain
        proportional = error;
        // this gives us a setpoint
        _pwmLoad = (proportional + _integral) / 0.120;
        // apply limits
        if (_pwmLoad <= 0) {
            _pwmLoad = 0;
            _integral = 0;
        }
        if (_pwmLoad >= 255) {
            _pwmLoad = 255;
        }
    } else {
        _pwmLoad = 0;
        _integral = 0;
    }

#ifndef NO_LOAD_CONTROL
    // Set the PWM value 
    analogWrite(_pwmPin, _pwmLoad);
#endif

#ifdef DEBUGLOAD
#ifndef NO_LOAD_CONTROL
    Serial.print(F("PWM="));
#else
    Serial.print(F("PWM (dis)="));
#endif
    Serial.println(_pwmLoad);
#endif
}

