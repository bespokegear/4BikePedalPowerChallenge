////////////////////////////////////////////////////////////////
//                                                            //
// Two Bike Pedal Powered Challenge Firmware for Arduino Nano //
// ========================================================== //
//                                                            //
// Copyright (C) 2016 Renewable Energy Innovation Ltd.        //
//                                                            //
// Author:              Mouse (Orthogonal Systems Ltd.)       //
// Project Start Date:  2016-10-06                            //
//                                                            //
////////////////////////////////////////////////////////////////

// Even though these libraries are only used in other sources, we
// #include them here so the Ardino IDE knows to compile and link 
// them...
#include <EEPROM.h>
#include <Adafruit_NeoPixel.h>

// General configuration
#include "Config.h"

// One #include per system object we will use
#include "Heartbeat.h"
#include "ResetButton.h"
#include "ModeButton.h"
#include "WaitMode.h"
#include "CountdownMode.h"
#include "GameMode.h"
#include "LED1.h"
#include "Pedal1Vin.h"
#include "ArduinoVin.h"
#include "ClockDisplay.h"

// General Arduino features
#include <Arduino.h>

// For watchdog
#include <avr/wdt.h>

// See Config.h for pin and other configuration

// Global variables - we begin in Wait Mode
Mode* mode = &WaitMode;

#ifdef DEBUGTIME
unsigned long lastLoop = 0;
#endif

void setup()
{
    Serial.begin(115200);

    // Use external reference
    analogReference(EXTERNAL);

    // Set up the blinker
    Heartbeat.begin();

    // Init buttons (set pin modes)
    ResetButton.begin();
    ModeButton.begin();

    // init pins for clock display
    ClockDisplay.begin();
    ClockDisplay.clear();

    // Ensure load is disconnected at start, indicator off
    pinMode(INDICATOR_LED_PIN, OUTPUT);
    digitalWrite(INDICATOR_LED_PIN, LOW);

    // Configure global Adafruit_Neopixel objects (from LEDs.h)
    LED1.begin();
    LED1.setBrightness(LED1_BRIGHTNESS);
    LED1.clear();
    LED1.show(); // Initialize all pixels to 'off'

    // init various modes
    WaitMode.begin();
    CountdownMode.begin();
    GameMode.begin();

    // Let things settle
    delay(500);

    // Call start for current mode
    mode->start();

    // Enable watchdog reset at 1/4 sec
    wdt_enable(WDTO_250MS);

#ifdef DEBUG
    Serial.println(F("setup() E"));
#endif
}

void loopDebug()
{
#ifdef DEBUG
    if (mode == &WaitMode) {
        Serial.println(F("in WaitMode"));
    }
    else if (mode == &CountdownMode) {
        Serial.println(F("in CountdownMode"));
    }
    else if (mode == &GameMode) {
        Serial.println(F("in GameMode"));
    }
    else {
        Serial.println(F("Unknown mode!"));
    }
#endif 

#ifdef DEBUGTIME
    Serial.print(F("looptime="));
    Serial.println(millis() - lastLoop);
    lastLoop = millis();
#endif

#ifdef DEBUGVIN
    Serial.print(F("Vin p1="));
    Serial.print(Pedal1Vin.get());
    Serial.print(F(" ard="));
    Serial.println(ArduinoVin.get());
#endif

#ifdef DEBUGMEM
    Serial.print(F("free="));
    Serial.println(freeMemory());
#endif
}

void switchMode(Mode* newMode)
{
    mode->stop();
    mode = newMode;
    mode->start();
}

void loop()
{
    // Feed the watchdog
    wdt_reset();

    // Give a time slice to various peripheral functions
    Heartbeat.update();
    ResetButton.update();
    ModeButton.update();
    Pedal1Vin.update();
    ArduinoVin.update();

    // Dump debugging to serial (if #defined)
    loopDebug();

    // Detect button presses and behave appropriately
    if (ResetButton.isPressed()) {
        if (mode == &WaitMode) {
            switchMode(&CountdownMode);
        } else if (mode == &GameMode) {
            ClockDisplay.clear();
            switchMode(&WaitMode);
        }
    }

    // Give a timeslice to the current mode
    mode->update();

    // Handle modes timing out
    if (mode->isFinished()) {
        if (mode == &CountdownMode) { switchMode(&GameMode); }
        else if (mode == &GameMode) { switchMode(&WaitMode); }
    }
}

