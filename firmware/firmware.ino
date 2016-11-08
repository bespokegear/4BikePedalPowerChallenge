#include <Arduino.h>
#include <stdint.h>
#include "Config.h"
#include "CurrentSampler.h"
#include "ClockDisplay.h"
#include "ModeButton.h"
#include "ResetButton.h"
#include "VoltageSampler.h"

void setup()
{
    Serial.begin(115200);

    ModeButton.begin();
    ResetButton.begin();
    ClockDisplay.begin();
    ClockDisplay.display("123");

    pinMode(PLAYER_PWM_PINS[0], OUTPUT);
    analogWrite(PLAYER_PWM_PINS[0], 0);

    delay(500);
    Serial.println(F("E:setup"));
}

void loop()
{
}

