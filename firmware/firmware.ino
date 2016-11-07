#include <Arduino.h>
#include "Player.h"
#include "LoadController.h"
#include "Config.h"

Player p1(PEDAL1_VOLTAGE_PIN, PEDAL1_VOLTAGE_R1, PEDAL1_VOLTAGE_R2,
          LED1_DATA_PIN, LED1_COUNT, LED1_TYPE);
LoadController load(p1, PWM_LOAD_PIN1);

void setup()
{
    Serial.begin(115200);
    p1.begin();
    load.begin();
    delay(500);
    Serial.println(F("E:setup"));
}

void loop()
{
    p1.update();
    load.update();
    Serial.print(F("p1.getVoltage()="));
    Serial.print(p1.getVoltage());
    Serial.print(F(", pwm="));
    Serial.println(load.getPwm());
    delay(5);
}


