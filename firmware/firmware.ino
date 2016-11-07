#include <Arduino.h>
#include "Players.h"
#include "CurrentSampler.h"
#include "Config.h"

CurrentSampler cs(PLAYER_IIN_PINS[0], PLAYER_VSUP[0]);

void setup()
{
    Serial.begin(115200);
    for (uint8_t i=0; i<PLAYER_COUNT; i++) {
        Players[i].begin();
    }
    cs.begin();
    delay(500);
    Serial.println(F("E:setup"));
}

void loop()
{
    cs.update();
    Serial.print(F("cur="));
    Serial.print(cs.getCurrent());
    Serial.print(F(" "));
    for (uint8_t i=0; i<PLAYER_COUNT; i++) {
        Players[i].update();
        Serial.print(i+1);
        Serial.print(F("UP vin="));
        Serial.print(Players[i].getVoltage());
        Serial.print(F(", pwm="));
        Serial.print(Players[i].getPwm());
        Serial.print(F(";  "));
    }
    Serial.println(F(""));
}

