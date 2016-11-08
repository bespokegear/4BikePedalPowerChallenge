#include <Arduino.h>
#include <stdint.h>
#include "Config.h"
#include "CurrentSampler.h"
#include "ModeButton.h"
#include "ResetButton.h"
#include "VoltageSampler.h"

#define ON_DURATION_MS 18000

unsigned long lastOn = 0;

uint8_t pwm = 0;

VoltageSampler vin(PLAYER_VIN_PINS[0], PLAYER_VIN_R1, PLAYER_VIN_R2);
CurrentSampler iin(PLAYER_IIN_PINS[0], PLAYER_VSUP[0]);

void setup()
{
    Serial.begin(115200);
    analogReference(VIN_REF);

    ModeButton.begin();
    ResetButton.begin();

    pinMode(PLAYER_PWM_PINS[0], OUTPUT);
    analogWrite(PLAYER_PWM_PINS[0], 0);

    delay(500);
    Serial.println(F("E:setup"));
}

void loop()
{
    vin.update();
    iin.update();
    ModeButton.update();
    ResetButton.update();

    if (ModeButton.wasPressed()) {
        pwm+=3;
        lastOn = millis();
    }
    if (ResetButton.wasPressed() || millis() > lastOn + ON_DURATION_MS) {
        pwm = 0;
    }

    analogWrite(PLAYER_PWM_PINS[0], pwm);

    Serial.print(F("pwm="));
    Serial.print(pwm);
    Serial.print(F(" ("));
    Serial.print(pwm*100./255., 1);
    Serial.print(F("%) vin="));
    Serial.print(vin.getVoltage() + PLAYER_VIN_FUDGE_FACTOR, 1);
    Serial.print(F(" iin="));
    Serial.println(iin.getCurrent(), 2);
}

