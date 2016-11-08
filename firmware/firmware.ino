#include <Arduino.h>
#include "Players.h"
#include "Config.h"
#include "ModeButton.h"
#include "ResetButton.h"

void setup()
{
    Serial.begin(115200);
    for (uint8_t i=0; i<PLAYER_COUNT; i++) {
        Players[i].begin();
    }
    analogReference(VIN_REF);
    ModeButton.begin();
    ResetButton.begin();
    delay(500);
    Serial.println(F("E:setup"));
}

void loop()
{
    // Give everything a timeslice
    ModeButton.update();
    ResetButton.update();
    for (uint8_t i=0; i<PLAYER_COUNT; i++) {
        Players[i].update();
    }

    for (uint8_t i=0; i<PLAYER_COUNT; i++) {
        Serial.print(i+1);
        Serial.print(F("UP vin="));
        Serial.print(Players[i].getVoltage());
        Serial.print(F(" cur="));
        Serial.print(Players[i].getCurrent());
        Serial.print(F(", pwm="));
        Serial.print(Players[i].getPwm());
        Serial.print(F(";  "));

        if (ModeButton.isPressed(true)) {
            Serial.print(F(" ModeButton=1"));
        }
        if (ResetButton.isPressed(true)) {
            Serial.print(F(" ResetButton=1"));
        }
    }
    Serial.println(F(""));
}

