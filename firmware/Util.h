#pragma once

#include <stdint.h>

// Returns Volts measured using voltage divider with r1KOhm and r2KOhm
float voltageConversion(const uint8_t pin, const uint16_t r1KOhm, const uint16_t r2KOhm);

// Used to convert a linear response into a more cubic one (to change "feel" of response
// for various pedal powered applications)
float calculateLinearity(float percent, float linearity);

// From the MemoryFree library, https://github.com/maniacbug/MemoryFree
#ifdef __cplusplus
extern "C" {
#endif

int freeMemory();

#ifdef  __cplusplus
}
#endif


