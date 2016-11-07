#pragma once

#include <Arduino.h>

// Per-player config
// If the number of players is changes, edit Players.cpp so the
// Players global variable has the correct number of entries...
#define PLAYER_COUNT                4
const uint8_t  PLAYER_VIN_PINS[]    = {  A0,  A2,  A4,  A6 };
const uint8_t  PLAYER_IIN_PINS[]    = {  A1,  A3,  A5,  A7 };
const uint8_t  PLAYER_PWM_PINS[]    = {   6,   7,   8,   9 };
const uint8_t  PLAYER_LED_PINS[]    = {  14,  15,  16,  17 };
const uint32_t PLAYER_LED_COLOR[]   = { 0xFF2222UL, 0x22FF22UL, 0x2222FFUL, 0xFFFF22UL };
// Player config (applies to all players)
#define PLAYER_VIN_R1               10
#define PLAYER_VIN_R2               560
#define PLAYER_LED_COUNT            180
#define PLAYER_LED_TYPE             (NEO_GRB + NEO_KHZ800)
#define PLAYER_LED_BRIGHTNESS       255
#define PLAYER_LED_UPDATE_MS        100
#define PLAYER_VIN_FUDGE_FACTOR     2.1
#define PLAYER_VIN_THRESHOLD        (PLAYER_VIN_FUDGE_FACTOR + 0.2)

// Load control constants
// Target delay for load controller updates in ms
#define LOAD_CONTROLLER_PERIOD_MS   10
// Generates warnings if happens less than this...
#define LOAD_CONTROLLER_WARNING_MS  20
#define LOAD_CONTROLLER_SET_POINT   15.0
#define LOAD_CONTROLLER_HYSTERESIS  3.0
#define LOAD_DUMP_R_OHM             4.0

// General config
#define ARDUINO_VOLTAGE_PIN         A6
#define ARDUINO_VOLTAGE_R1          10
#define ARDUINO_VOLTAGE_R2          100
#define RESET_BUTTON_PIN            2
#define MODE_BUTTON_PIN             5
#define HEARTBEAT_LED_PIN           13
#define INDICATOR_LED_PIN           9
#define BROWNOUT_HIGH               1300
#define BROWNOUT_LOW                300
#define VOLTAGE_SAMPLES             20
#define SLATCH_PIN                  10
#define SCLK_PIN                    11
#define SDATA_PIN                   12
#define EEPROM_LEVEL_ADDRESS        0

// GameMode parameters
#define GAME_LEVEL_ENERGY_STEP      1000
#define GAME_LEVEL_MAX              20
#define GAME_LENGTH_SECONDS         30


// Other mode settings
#define COUNTDOWN_SECONDS           3

