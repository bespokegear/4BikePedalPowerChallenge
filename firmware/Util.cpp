#include "Util.h"
#include <Arduino.h>

float voltageConversion(const uint8_t pin, const uint16_t r1KOhm, const uint16_t r2KOhm)
{
    float raw = analogRead(pin);
    return (raw*3.3*(r1KOhm+r2KOhm)) / (1024*r1KOhm);
}

float calculateLinearity(const float percent, const float linearity)
{
    float cube = percent * percent * percent;
    return cube+((percent-cube)*linearity);
}

float currentConversion(const uint8_t pin, const float vSupply)
{
    // return (analogRead(pin)-(vSupply/2.0)) / (0.04*vSupply/5.0);
    float r = ((5.0*analogRead(pin)/1024.0)-(vSupply/2.0)) / (0.04*vSupply/5.0);
    return r;
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
