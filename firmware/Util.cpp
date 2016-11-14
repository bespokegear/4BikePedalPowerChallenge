#include <Arduino.h>
#include "Util.h"
#include "Config.h"
#include "Settings.h"

float voltageConversion(const uint8_t pin, const uint16_t r1KOhm, const uint16_t r2KOhm)
{
    return (analogRead(pin)*VIN_REF_VOLTS*(r1KOhm+r2KOhm)) / (1024*r1KOhm);
}

float calculateLinearity(const float percent, const float linearity)
{
    float cube = percent * percent * percent;
    return cube+((percent-cube)*linearity);
}

float currentConversion(const uint8_t pin, const float vSupply)
{
    //return (((VIN_REF_VOLTS+CURRENT_REF_VOLTS_OFFSET)*analogRead(pin)/1024.0)-(vSupply/2.0)) / (0.04*vSupply/(VIN_REF_VOLTS+CURRENT_REF_VOLTS_OFFSET));
    return ((vSupply/2.0)-((VIN_REF_VOLTS+CURRENT_REF_VOLTS_OFFSET)*analogRead(pin)/1024.0)) / (0.04*vSupply/(VIN_REF_VOLTS+CURRENT_REF_VOLTS_OFFSET));
}

uint16_t playerLedCount() {
    return NumberOfLedSegments.get()*PLAYER_SEGMENT_LEDS;
}

uint32_t colorBrightness(uint32_t color, float brightness)
{
    uint16_t r = (color >> 16) * brightness;
    uint16_t g = ((color >> 8) % 256) * brightness;
    uint16_t b = (color % 256) * brightness;
    // prevent integer overflow
    r = r > 255 ? 255 : r;
    g = g > 255 ? 255 : g;
    b = b > 255 ? 255 : b;

    uint32_t c = (uint8_t)r; c <<= 8;
    c += (uint8_t)g; c <<= 8;
    c += (uint8_t)b;
    return c;
}

// From the MemoryFree library, https://github.com/maniacbug/MemoryFree
extern unsigned int __bss_end;
extern unsigned int __heap_start;
extern void *__brkval;

int freeMemory() {
    int free_memory;

    if((int)__brkval == 0)
        free_memory = ((int)&free_memory) - ((int)&__bss_end);
    else
        free_memory = ((int)&free_memory) - ((int)__brkval);

    return free_memory;
}
