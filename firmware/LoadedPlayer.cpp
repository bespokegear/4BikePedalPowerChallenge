#include "Config.h"
#include "LoadedPlayer.h"
#include <Arduino.h>

LoadedPlayer::LoadedPlayer(uint8_t vinPin, uint16_t r1KOhm, uint16_t r2KOhm, 
                           uint8_t curPin, float vSupply,
                           uint8_t ledPin, uint16_t ledCount, neoPixelType ledType,
                           uint32_t ledColor, uint32_t maxColor, uint8_t pwmPin) :
    Player(vinPin, r1KOhm, r2KOhm, curPin, vSupply, ledPin, ledCount, ledType, ledColor, maxColor),
    _pwmPin(pwmPin),
    _pwmLoad(0),
    _last(0)
{
}

void LoadedPlayer::begin()
{
#ifdef DEBUGFUNC
    Serial.println(F("LoadedPlayer::begin"));
#endif
    Player::begin();
    pinMode(_pwmPin, OUTPUT);
    digitalWrite(_pwmPin, LOW);
}

void LoadedPlayer::update()
{
    Player::update();
#ifdef DEBUGFUNC
    Serial.println(F("LoadedPlayer::update"));
#endif
    // Set _pwmLoad based on the input volts from the pedal generator and the
    // upper and lower load control settings from Config.h
    float vin = getVoltage();
    float load;
    if (vin<=LOAD_CONTROL_MIN_VOLTS) load = 0.; 
    else load = (vin - LOAD_CONTROL_MIN_VOLTS) / (LOAD_CONTROL_MAX_VOLTS-LOAD_CONTROL_MIN_VOLTS);
    _pwmLoad = load >= 1.0 ? 255 : (uint8_t)(255*load);

#ifndef NO_LOAD_CONTROL
    // Set the PWM value 
    analogWrite(_pwmPin, _pwmLoad);
#endif

#ifdef DEBUGLOAD
#ifndef NO_LOAD_CONTROL
    Serial.print(F("PWM, pin="));
#else
    Serial.print(F("PWM (dis), pin="));
#endif
    Serial.print(_pwmPin);
    Serial.print(F(" v="));
    Serial.print(vin);
    Serial.print(F(" i="));
    Serial.print(getCurrent());
    Serial.print(F(" pwm="));
    Serial.print(_pwmLoad);
    Serial.print(F(" delay="));
    Serial.println(millis() - _last);
#endif
    _last = millis();
}

