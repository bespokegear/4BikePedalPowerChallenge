#include <Arduino.h>
#include "Player.h"
#include "Config.h"
#include "Settings.h"
#include "CorrectedMillis.h"

Player::Player(uint8_t vinPin, uint16_t r1KOhm, uint16_t r2KOhm, 
               uint8_t curPin, float vSupply,
               uint8_t ledPin, uint16_t ledCount, neoPixelType ledType, 
               uint32_t ledColor, uint32_t maxColor) :
    VoltageSampler(vinPin, r1KOhm, r2KOhm),
    CurrentSampler(curPin, vSupply),
    _LED(ledCount, ledPin, ledType),
    _ledColor(ledColor),
    _maxColor(maxColor)
{
}

Player::~Player()
{
}

// Call from setup(), initializes pins and so on
void Player::begin()
{   
#ifdef DEBUGFUNC
    Serial.println(F("Player::begin"));
#endif
    VoltageSampler::begin();
    _LED.begin();
    _LED.setBrightness(PLAYER_LED_BRIGHTNESS);
    _LED.clear();
    _LED.show();
    reset();
}

void Player::update()
{
#ifdef DEBUGFUNC
    Serial.println(F("Player::update"));
#endif
    VoltageSampler::update();
    CurrentSampler::update();
}

float Player::getVoltage()
{
#ifdef DEBUGFUNC
    Serial.println(F("Player::getVoltage"));
#endif
    return VoltageSampler::getVoltage() + PLAYER_VIN_FUDGE_FACTOR;
}

void Player::displayLED(float n)
{
#ifdef DEBUGFUNC
    Serial.println(F("Player::displayLED"));
#endif
    uint16_t i;
    uint16_t lastLit = 0;
    bool lit;
    uint16_t ledCount = (NumberOfLedSegments.get()*PLAYER_SEGMENT_LEDS) / 2;
    for (i=0; i<ledCount; i++) {
        bool lit = (n*ledCount) > i;
        _LED.setPixelColor(i*2, lit ? _ledColor : 0x000000UL);
        _LED.setPixelColor((i*2+1), lit ? _ledColor : 0x000000UL);
        if (lit) lastLit = i;
    }

    if (lastLit >= _max) {
        _max = lastLit;
    }

    if (_max>0) {
        _LED.setPixelColor(_max*2, _maxColor);
        _LED.setPixelColor((_max*2)+1, _maxColor);
    }

    showLED();
}

void Player::reset()
{
    _max = 0;
    displayLED(0.0);
}

void Player::showLED()
{
    _LED.show();
    // The _LED.show() call disabled interrupts while the LEDs are getting updated
    // which leads to innacuracy of millis(). We add an adjustment here, which is
    // used by our own implementation of millis(), which is enabled by including
    // CorrectedMillis.h.
    addMillisOffset(LED_CLOCK_CORRECTION*PLAYER_SEGMENT_LEDS*PLAYER_SEGMENT_MAX/1000.);

}

