#pragma once

#include <Arduino.h>

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

// LED strip parameters
// This is for initialising the Adafruit_NeoPixel library
// and will depend on the LED type
#define LED1_TYPE                   (NEO_GRB + NEO_KHZ800)
#define LED1_DATA_PIN               3
#define LED1_COUNT                  109
#define LED1_BRIGHTNESS             255
#define LED_UPDATE_DELAY_MS         100

#define LED_BRIGHTNESS              255

// GameMode parameters
#define P1_ON_COLOR                 0xFF0000UL
#define P1_OFF_COLOR                0x000000UL
#define P2_ON_COLOR                 0x00FF00UL
#define P2_OFF_COLOR                0x000000UL
#define GAME_LEVEL_ENERGY_STEP      1000
#define GAME_LEVEL_MAX              20
#define GAME_LENGTH_SECONDS         30

// Other mode settings
#define COUNTDOWN_SECONDS           3

