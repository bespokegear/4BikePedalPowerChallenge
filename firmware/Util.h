#pragma once

#include <stdint.h>

// Returns Volts measured using voltage divider with r1KOhm and r2KOhm
float voltageConversion(const uint8_t pin, const uint16_t r1KOhm, const uint16_t r2KOhm);

// Used to convert a linear response into a more cubic one (to change "feel" of response
// for various pedal powered applications)
float calculateLinearity(float percent, float linearity);

// Calculate current based on a value from an analog pin and supply voltage
// Note: device is Allegro ACS756SCB-050B-PFF-T Bi-directional 50A hall effect sensor
float currentConversion(const uint8_t pin, const float vSupply);

// Tell us how many LEDs there are in use (note: number of segments is runtime
// configurable).
uint16_t playerLedCount();

// Change a color's brightness. A brightness value of 0.5 dims the color to
// 50% intensity.
uint32_t colorBrightness(uint32_t color, float brightness);

// From the MemoryFree library, https://github.com/maniacbug/MemoryFree
#ifdef __cplusplus
extern "C" {
#endif

int freeMemory();

#ifdef  __cplusplus
}
#endif


