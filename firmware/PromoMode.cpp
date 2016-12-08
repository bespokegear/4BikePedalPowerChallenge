#include <Arduino.h>
#include "PromoMode.h"
#include "ClockDisplay.h"
#include "Config.h"
#include "Players.h"
#include "Settings.h"
#include "CorrectedMillis.h"
#include "Util.h"

_PromoMode PromoMode;

_PromoMode::_PromoMode()
{
#ifdef DEBUG
    Serial.println(F("PromoMode::PromoMode()"));
#endif
}

void _PromoMode::start()
{
#ifdef DEBUG
    Serial.println(F("PromoMode::start()"));
    Serial.print(F("Settings: MaximumPowerWatts="));
    Serial.print(MaximumPowerWatts.get());
    Serial.print(F(" GameDurationSeconds="));
    Serial.print(GameDurationSeconds.get());
    Serial.print(F(" NumberOfLedSegments="));
    Serial.println(NumberOfLedSegments.get());
    Serial.println(F("setup() E"));
#endif
    // Clean button presses from other modes
    ClockDisplay.display("Hi!");
    _wipe = playerDisplayRowCount();
    _last = millis();
    _player = 0;
    _done = false;
    lightPlayer(_player);
}

void _PromoMode::stop()
{
#ifdef DEBUG
    Serial.println(F("PromoMode::stop()"));
#endif
    // in case we exit wait mode before the displays are wiped
    // just clear them
    for (uint8_t p=0; p<PLAYER_COUNT; p++) {
        Players[p].LED().clear();
        Players[p].LED().show();
    }
    
}

void _PromoMode::modeUpdate()
{
    unsigned long now = millis();
    if (now < _last + 5 || _done)
        return;
    _last = now;
    switch (_stage) {
    case PlayerLit:
        if (now > _stageStart + PROMO_MODE_LIT_TIME_MS) {
            startFade();
        }
        break;
    case PlayerFade:
        if (_wipe > 0) {
            for (uint8_t p=0; p<PLAYER_COUNT; p++) {
                Players[p].setRowColor(_wipe, 0x000000UL);
                Players[p].showLED();
            }
            _wipe--;
        } else {
            _player++;
            if (_player<PLAYER_COUNT ) {
                lightPlayer(_player);
            } else {
                _done = true;
            }
        }
        break;
    }
}

void _PromoMode::lightPlayer(uint8_t player) 
{
    setStage(PlayerLit);
    for(_wipe=0; _wipe<playerDisplayRowCount(); _wipe++) {
        Players[player].setRowColor(_wipe, PLAYER_LED_COLOR[player]);
    }
    Players[player].showLED();
}

void _PromoMode::startFade()
{
    setStage(PlayerFade);
    _wipe = playerDisplayRowCount(); 
}

void _PromoMode::setStage(Stage stage)
{
    _stage = stage;
    _stageStart = millis();
}


