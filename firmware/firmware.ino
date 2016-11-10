////////////////////////////////////////////////////////////////
//                                                            //
// 4-Bike Pedal Powered Challenge Firmware for Arduino Nano   //
// ========================================================== //
//                                                            //
// Copyright (C) 2016 Renewable Energy Innovation Ltd.        //
//                                                            //
// Author:              Mouse (Orthogonal Systems Ltd.)       //
// Project Start Date:  2016-11-03                            //
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
#include "PwmConfig.h"
#include "Heartbeat.h"
#include "ResetButton.h"
#include "ModeButton.h"
#include "WaitMode.h"
#include "CountdownMode.h"
#include "GameMode.h"
#include "ArduinoVin.h"
#include "ClockDisplay.h"
#include "Players.h"
#include "Util.h"

// General Arduino features
#include <Arduino.h>

// For watchdog
#include <avr/wdt.h>

// See Config.h for pin and other configuration

// Global variables - we begin in Wait Mode
//Mode* mode = &WaitMode;
Mode* mode = &GameMode;

#ifdef DEBUGTIME
unsigned long lastLoop = 0;
#endif

void setup()
{
    Serial.begin(115200);

    // Use external reference
    analogReference(VIN_REF);

    // Set up PWM clocks
    PwmConfig();

    // Set up the blinker
    Heartbeat.begin();

    // Init buttons (set pin modes)
    ResetButton.begin();
    ModeButton.begin();

    // Init pins for clock display
    ClockDisplay.begin();
    ClockDisplay.clear();

    // Init player objects
    for (uint8_t i=0; i<PLAYER_COUNT; i++) {
        Players[i].begin();
    }

    // Init game modes
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
#ifdef DEBUGMODE
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

    // Dump debugging to serial (if #defined)
    loopDebug();

    // Give a time slice to all system components
    Heartbeat.update();
    ResetButton.update();
    ModeButton.update();
    for (uint8_t i=0; i<PLAYER_COUNT; i++) {
        Players[i].update();
    }

    // Detect button presses and behave appropriately
    if (ResetButton.isPressed()) {
        if (mode == &WaitMode) {
            switchMode(&CountdownMode);
        } else if (mode == &CountdownMode) {
            ClockDisplay.clear();
            switchMode(&WaitMode);
        } else if (mode == &GameMode) {
            ClockDisplay.clear();
            switchMode(&WaitMode);
        }
    }

    if (ModeButton.isPressed() && mode == &CountdownMode) {
        switchMode(&GameMode);
    }

    // Give a timeslice to the current mode
    mode->update();

    // Handle modes timing out
    if (mode->isFinished()) {
        if (mode == &CountdownMode) { switchMode(&GameMode); }
        else if (mode == &GameMode) { switchMode(&WaitMode); }
    }
}

