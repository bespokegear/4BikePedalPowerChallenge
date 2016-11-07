#include <Arduino.h>
#include "VoltageSampler.h"
#include "LoadController.h"
#include "Config.h"

VoltageSampler vin(PEDAL1_VOLTAGE_PIN, PEDAL1_VOLTAGE_R1, PEDAL1_VOLTAGE_R2);
LoadController load(vin, PWM_LOAD_PIN1);

void setup()
{
    Serial.begin(115200);
    vin.begin();
    load.begin();
    delay(500);
    Serial.println(F("E:setup"));
}

void loop()
{
    vin.update();
    load.update();
    Serial.print(F("vin="));
    Serial.print(vin.getVoltage());
    Serial.print(F(", pwm="));
    Serial.println(load.getPwm());
    delay(5);
}


