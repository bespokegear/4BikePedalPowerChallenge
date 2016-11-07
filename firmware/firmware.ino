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
        Serial.print(i+1);
        Serial.print(F("UP vin="));
        Serial.print(Players[i].getVoltage());
        Serial.print(F(", pwm="));
        Serial.print(Players[i].getPwm());
        Serial.print(F(";  "));
    }
    Serial.println(F(""));
}

