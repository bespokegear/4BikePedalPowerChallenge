#include <Arduino.h>
#include "Player.h"
#include "Config.h"
#include "Settings.h"
#include "Util.h"
#include "CorrectedMillis.h"

Player::Player(uint8_t vinPin, uint16_t r1KOhm, uint16_t r2KOhm, 
               uint8_t curPin, float vSupply,
               uint8_t ledPin, uint16_t ledCount, neoPixelType ledType, 
               uint32_t ledColor, uint32_t maxColor) :
    VoltageSampler(vinPin, r1KOhm, r2KOhm),
    CurrentSampler(curPin, vSupply),
    _LED(ledCount, ledPin, ledType),
    _ledColor(ledColor),
    _maxIlluminatedRowColor(maxColor)
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

float Player::getPower() 
{ 
    float p = getVoltage() * getCurrent();
    if (p > _maxPower) {
        _maxPower = p;
    }
    return p;
}

float Player::getMaxPower() 
{
    return _maxPower;
}

void Player::setRowColor(uint16_t row, uint32_t color)
{
    _LED.setPixelColor(row*2, color);
    _LED.setPixelColor((row*2)+1, color);
}

void Player::displayPower(float p)
{
#ifdef DEBUGFUNC
    Serial.print(F("Player::displayPower p="));
    Serial.println(p, 1);
#endif
    uint16_t i;
    uint16_t lastRowLit = 0;
    bool lit;
    uint16_t rowCount = playerLedCount() / 2;
    uint16_t rowsToLight = (p*rowCount)/MaximumPowerWatts.get();
    for (i=0; i<rowCount; i++) {
        bool rowLit = rowsToLight > i;
        setRowColor(i, rowLit ? _ledColor : 0x000000UL);
        if (rowLit) 
            lastRowLit = i;
    }

    if (lastRowLit >= _maxIlluminatedRow) {
        _maxIlluminatedRow = lastRowLit;
    }

    if (_maxIlluminatedRow>0) {
        setRowColor(_maxIlluminatedRow, _maxIlluminatedRowColor);
    }

    showLED();
}

void Player::reset()
{
    _maxIlluminatedRow = 0;
    _maxPower = 0.;
    displayPower(0.0);
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

void Player::fillup()
{
    displayPower(_maxPower / MaximumPowerWatts.get());
}

