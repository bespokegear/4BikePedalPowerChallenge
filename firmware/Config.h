#pragma once

#include <Arduino.h>

// Per-player config
const uint8_t  PLAYER_VIN_PINS[]    = {  A0,  A2,  A4,  A6 };
const uint8_t  PLAYER_IIN_PINS[]    = {  A1,  A3,  A5,  A7 };
const uint8_t  PLAYER_PWM_PINS[]    = {   6,   7,   8,   9 };
const uint8_t  PLAYER_LED_PINS[]    = {  14,  15,  16,  17 };
// Player config (applies to all players)
#define PLAYER_COUNT                4
#define PLAYER_VIN_R1               10
#define PLAYER_VIN_R2               560
#define PLAYER_LED_COUNT            180
#define PLAYER_LED_TYPE             (NEO_GRB + NEO_KHZ800)
#define PLAYER_LED_BRIGHTNESS       255
#define PLAYER_LED_UPDATE_MS        100

// General config
#define PEDAL1_VOLTAGE_PIN          A1
#define PEDAL1_VOLTAGE_R1           10
#define PEDAL1_VOLTAGE_R2           560
#define PEDAL1_DUMP_R               4.0
#define PEDAL1_FUDGE_FACTOR         2.1
#define PEDAL1_THRESHOLD            PEDAL1_FUDGE_FACTOR + 0.2
#define PEDAL2_VOLTAGE_PIN          A0
#define PEDAL2_VOLTAGE_R1           10
#define PEDAL2_VOLTAGE_R2           560
#define PEDAL2_DUMP_R               4.0
#define PEDAL2_FUDGE_FACTOR         2.1
#define PEDAL2_THRESHOLD            PEDAL2_FUDGE_FACTOR + 0.2
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
#define P1_ON_COLOR                 0xFF0000UL
#define P1_OFF_COLOR                0x000000UL
#define P2_ON_COLOR                 0x00FF00UL
#define P2_OFF_COLOR                0x000000UL
#define GAME_LEVEL_ENERGY_STEP      1000
#define GAME_LEVEL_MAX              20
#define GAME_LENGTH_SECONDS         30

// Load control constants
#define LOAD_CONTROLLER_PERIOD_MS   10
#define LOAD_CONTROLLER_SET_POINT   15.0
#define LOAD_CONTROLLER_HYSTERESIS  3.0
#define PWM_LOAD_PIN1               6

// Other mode settings
#define COUNTDOWN_SECONDS           3

