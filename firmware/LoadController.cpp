#include "Config.h"
#include "LoadController.h"
#include <Arduino.h>

LoadController::LoadController(VoltageSampler& vin, uint8_t pwmPin) :
    _vin(vin),
    _pwmPin(pwmPin),
    _pwm(0),
    _integral(0),
    _last(0)
{
}

void LoadController::begin()
{
    pinMode(_pwmPin, OUTPUT);
    digitalWrite(_pwmPin, LOW);
}

void LoadController::update()
{
    if (millis() < _last + LOAD_CONTROL_PERIOD_MS) {
        return;
    }
    _last = millis();
    if (_vin.getVoltage() >= VPWMSETPOINT - VPWMHYSTERESIS) {
        float error;
        float proportional;
        // in float V and vary up to > 1
        // if the value is 1000 then the voltage is at 14V and the FET should be fully ON
        error = _vin.getVoltage() - VPWMSETPOINT;
        // _integral value will go down when _error is negative
        _integral = _integral + error;
        // proportional gain
        proportional = error;
        // this gives us a setpoint
        _pwm = (proportional + _integral) / 0.120;
        // apply limits
        if (_pwm <= 0) {
            _pwm = 0;
            _integral = 0;
        }
        if (_pwm >= 255) {
            _pwm = 255;
        }
    } else {
        _pwm = 0;
        _integral = 0;
    }

#ifndef NO_LOAD_CONTROL
    // Set the PWM value 
    analogWrite(_pwmPin, _pwm);
#endif

#ifdef DEBUGLOAD
#ifndef NO_LOAD_CONTROL
    Serial.print(F("PWM="));
#else
    Serial.print(F("PWM (dis)="));
#endif
    Serial.println(_pwm);
#endif
}

