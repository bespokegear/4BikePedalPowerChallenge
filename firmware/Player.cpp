#include "Player.h"
#include "Config.h"
#include <Arduino.h>

Player::Player(uint8_t vinPin, uint16_t r1KOhm, uint16_t r2KOhm, 
               uint8_t ledPin, uint16_t ledCount, neoPixelType ledType, uint32_t ledColor) :
    VoltageSampler(vinPin, r1KOhm, r2KOhm),
    _LED(ledCount, ledPin, ledType),
    _ledColor(ledColor)
{
}

Player::~Player()
{
}

// Call from setup(), initializes pins and so on
void Player::begin()
{   
#ifdef DEBUG
    Serial.println(F("Player::begin"));
#endif
    VoltageSampler::begin();
    _LED.begin();
    _LED.setBrightness(PLAYER_LED_BRIGHTNESS);
    _LED.clear();
    _LED.show();
}

void Player::update()
{
#ifdef DEBUG
    Serial.println(F("Player::update"));
#endif
    VoltageSampler::update();
}

