#include <Arduino.h>
#include "Players.h"
#include "Config.h"

void setup()
{
    Serial.begin(115200);
    for (uint8_t i=0; i<PLAYER_COUNT; i++) {
        Players[i].begin();
    }
    delay(500);
    Serial.println(F("E:setup"));
}

void loop()
{
    for (uint8_t i=0; i<PLAYER_COUNT; i++) {
        Players[i].update();
        Serial.print(F("player "));
        Serial.print(i);
        Serial.print(F(" vin="));
        Serial.print(Players[i].getVoltage());
        Serial.print(F(", pwm="));
        Serial.println(Players[i].getPwm());
    }
    delay(100);
}

