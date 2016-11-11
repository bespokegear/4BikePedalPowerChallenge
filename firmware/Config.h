#pragma once

#include <Arduino.h>

// Per-player config
// If the number of players is changes, edit Players.cpp so the
// Players global variable has the correct number of entries...
#define PLAYER_COUNT                4
const uint8_t  PLAYER_VIN_PINS[]    = {         A6,         A4,         A2,         A0 };
const uint8_t  PLAYER_IIN_PINS[]    = {         A7,         A5,         A3,         A1 };
const uint8_t  PLAYER_PWM_PINS[]    = {          6,          7,          8,          9 };
const uint8_t  PLAYER_LED_PINS[]    = {         14,         15,         16,         17 };
const float    PLAYER_VSUP[]        = {        5.0,        5.0,        5.0,        5.0 };
const uint32_t PLAYER_LED_COLOR[]   = { 0xFF2222UL, 0x22FF22UL, 0x2222FFUL, 0xFFFF22UL };
const uint32_t PLAYER_MAX_COLOR[]   = { 0xFFFFFFUL, 0xFFFFFFUL, 0xFFFFFFUL, 0xFFFFFFUL };
// Player config (applies to all players)
#define PLAYER_VIN_R1               10
#define PLAYER_VIN_R2               560
#define PLAYER_VIN_FUDGE_FACTOR     2.1
#define PLAYER_VIN_THRESHOLD        (PLAYER_VIN_FUDGE_FACTOR + 0.2)
#define PLAYER_SEGMENT_LEDS         60
#define PLAYER_SEGMENT_MAX          3 
#define PLAYER_LED_TYPE             (NEO_GRB + NEO_KHZ800)
#define PLAYER_LED_BRIGHTNESS       255
#define PLAYER_LED_UPDATE_MS        250

// Load control constants
// Target delay for load controller updates in ms
#define LOAD_CONTROLLER_PERIOD_MS   10
// Generates warnings if happens less than this...
#define LOAD_CONTROLLER_WARNING_MS  20
#define LOAD_CONTROL_MIN_VOLTS      12.0
#define LOAD_CONTROL_MAX_VOLTS      25.0
#define LOAD_DUMP_R_OHM             3.0

// General config
// VIN_REF is passed to analogReference in setup(). See arduino docs for valid values
#define VIN_REF                     DEFAULT
// Voltage reference.  Depends on VIN_REF and hardware
#define VIN_REF_VOLTS               5.0
// Current calculation offset to compensate for VIN_REF_VOLTS variation
#define CURRENT_REF_VOLTS_OFFSET    0.028
#define WIRED_A_BUTTON_PIN          21
#define WIRED_B_BUTTON_PIN          20
#define REMOTE_A_BUTTON_PIN         10
#define REMOTE_B_BUTTON_PIN         11
#define HEARTBEAT_LED_PIN           13
#define VOLTAGE_SAMPLES             10
#define CURRENT_SAMPLES             50
#define SLATCH_PIN                  22
#define SCLK_PIN                    27
#define SDATA_PIN                   24
#define SENABLE_PIN                 25
#define ARDUINO_VOLTAGE_PIN         A8
#define ARDUINO_VOLTAGE_R1          10
#define ARDUINO_VOLTAGE_R2          100
#define BROWNOUT_HIGH               1300
#define BROWNOUT_LOW                300

// EEPROM data addresses
#define EEPROM_LEVEL_ADDRESS        0

// GameMode parameters
#define GAME_LEVEL_ENERGY_STEP      1000
#define GAME_LEVEL_MAX              20

// Other mode settings
#define COUNTDOWN_SECONDS           3

// Button config
#define BUTTON_DEBOUNCE_COUNT       3
#define BUTTON_DEBOUNCE_MS          10
#define BUTTON_NOREPEAT_MS          500

// For calculating clock offset when Adafruit_NeoPixel.show() is called
// increasing this number makes the clock go FASTER
#define LED_CLOCK_CORRECTION        24.5

