#include "SevenSegmentDisplay.h"
#include <Arduino.h>

#define SEG_TYPE_REINNOVATION   1
#define SEG_TYPE_MATT_VENN      2

#define SEG_TYPE                SEG_TYPE_MATT_VENN

#if SEG_TYPE == SEG_TYPE_REINNOVATION
#define SEG_TOP_H               0B10000000
#define SEG_TOP_R               0B01000000
#define SEG_BOT_R               0B00100000
#define SEG_BOT_H               0B00010000
#define SEG_BOT_L               0B00001000
#define SEG_TOP_L               0B00000100
#define SEG_CEN_H               0B00000010
#define SEG_DEC_P               0B00000001
#elif SEG_TYPE == SEG_TYPE_MATT_VENN
#define SEG_TOP_H               0B00000001
#define SEG_CEN_H               0B01000000
#define SEG_BOT_H               0B00001000

#define SEG_TOP_L               0B00100000
#define SEG_TOP_R               0B00000010

#define SEG_BOT_L               0B00010000
#define SEG_BOT_R               0B00000100

#define SEG_DEC_P               0B10000000
#else
#error Must set SEG_TYPE to a valid value
#endif

SevenSegmentDisplay::SevenSegmentDisplay(uint8_t SLatchPin, uint8_t SClkPin, uint8_t SDataPin, uint8_t SEnablePin) :
    _SLatchPin(SLatchPin),
    _SClkPin(SClkPin),
    _SDataPin(SDataPin),
    _SEnablePin(SEnablePin)
{
#ifdef DEBUG7SEG
    Serial.print(F("SevenSegmentDisplay::SevenSegmentDisplay lat="));
    Serial.print(SLatchPin);
    Serial.print(F(" clk="));
    Serial.print(SClkPin);
    Serial.print(F(" dat="));
    Serial.println(SDataPin);
    Serial.print(F(" ebl="));
    Serial.println(SEnablePin);
#endif
}


SevenSegmentDisplay::~SevenSegmentDisplay()
{
}

void SevenSegmentDisplay::begin()
{
#ifdef DEBUG7SEG
    Serial.println(F("SevenSegmentDisplay::begin"));
#endif
    pinMode(_SLatchPin,  OUTPUT);
    pinMode(_SClkPin,    OUTPUT);
    pinMode(_SDataPin,   OUTPUT);
    pinMode(_SEnablePin, OUTPUT);
    digitalWrite(_SEnablePin, LOW);
}

void SevenSegmentDisplay::clear()
{
#ifdef DEBUG7SEG
    Serial.println(F("SevenSegmentDisplay::clear"));
#endif
    display(' ', ' ', ' ');
}

void SevenSegmentDisplay::display(char str[3])
{
    display((uint8_t)str[0], (uint8_t)str[1], (uint8_t)str[2]);
}

void SevenSegmentDisplay::display(int16_t i, bool zeroPad)
{
    if (i<0) {
        i *= -1;
        display('-',
                (!zeroPad && i<10) ? ' ' : (i/10)%10,
                i%10);
    } else {
        display((!zeroPad && i<100) ? ' ' : (i/100)%10,
                (!zeroPad && i<10) ? ' '  : (i/10)%10,
                i%10);
    }
}

void SevenSegmentDisplay::display(uint8_t c1, uint8_t c2, uint8_t c3, uint8_t decimalPosition)
{
#ifdef DEBUG7SEG
    Serial.print(F("SevenSegmentDisplay::display, digits: "));
    Serial.print(c1);
    Serial.print(' ');
    Serial.print(c2);
    Serial.print(' ');
    Serial.println(c3);
#endif
    // Set latch low so the LED1 don't change while sending in bits
    digitalWrite(_SLatchPin, LOW);
    c1 = int7segment(c1);
    c2 = int7segment(c2);
    c3 = int7segment(c3);
    if (decimalPosition == 1) {
        c1 |= int7segment('.');
    } else if (decimalPosition == 2) {
        c2 |= int7segment('.');
    } else if (decimalPosition == 3) {
        c3 |= int7segment('.');
    }
    // shift out the bits:
    // Send data via 3 shift registers:
    shiftOut(_SDataPin, _SClkPin, MSBFIRST, c1);  // Puts out data onto all three digits
    shiftOut(_SDataPin, _SClkPin, MSBFIRST, c2);
    shiftOut(_SDataPin, _SClkPin, MSBFIRST, c3);
    // set latch high to display new values
    digitalWrite(_SLatchPin, HIGH);
}

uint8_t SevenSegmentDisplay::int7segment (uint8_t segmentData)
{
    uint8_t displayData;

    switch (segmentData)
    {
    case 0:
    case '0':
    case 'O':
        displayData = SEG_TOP_H | SEG_TOP_R | SEG_BOT_R | SEG_BOT_H | SEG_BOT_L | SEG_BOT_L;
        break;
    case 1:
    case '1':
        displayData = SEG_TOP_R | SEG_BOT_R;
        break;
    case 2:
    case '2':
        displayData = SEG_TOP_H | SEG_TOP_R | SEG_BOT_H | SEG_BOT_L | SEG_CEN_H;
        break;
    case 3:
    case '3':
        displayData = SEG_TOP_H | SEG_TOP_R | SEG_BOT_R | SEG_BOT_H | SEG_CEN_H;
        break;
    case 4:
    case '4':
        displayData = SEG_TOP_R | SEG_BOT_R | SEG_BOT_L | SEG_CEN_H;
        break;
    case 5:
    case '5':
        displayData = SEG_TOP_H | SEG_BOT_R | SEG_BOT_H | SEG_BOT_L | SEG_CEN_H;
        break;
    case 6:
    case '6':
        displayData = SEG_TOP_H | SEG_BOT_R | SEG_BOT_H | SEG_BOT_L | SEG_BOT_L | SEG_CEN_H;
        break;
    case 7:
    case '7':
        displayData = SEG_TOP_H | SEG_TOP_R | SEG_BOT_R;
        break;
    case 8:
    case '8':
        displayData = SEG_TOP_H | SEG_TOP_R | SEG_BOT_R | SEG_BOT_H | SEG_BOT_L | SEG_BOT_L | SEG_CEN_H;
        break;
    case 9:
    case '9':
        displayData = SEG_TOP_H | SEG_TOP_R | SEG_BOT_R | SEG_BOT_H | SEG_BOT_L | SEG_CEN_H;
        break;
    case 10:
    case '.':
        // Decimal point ON
        displayData = SEG_DEC_P;
        break;
    case '_':
        displayData = SEG_BOT_H;
        break;
    case '-':
        displayData = SEG_CEN_H;
        break;
    case '=':
        displayData = SEG_BOT_H | SEG_CEN_H;
        break;
    case 'o':
        displayData = SEG_BOT_R | SEG_BOT_H | SEG_BOT_L | SEG_CEN_H;
        break;
    case 'A':
    case 'a':
        displayData = SEG_TOP_H | SEG_TOP_R | SEG_BOT_R | SEG_BOT_L | SEG_BOT_L | SEG_CEN_H;
        break;
    case 'B':
    case 'b':
        displayData = SEG_BOT_R | SEG_BOT_H | SEG_BOT_L | SEG_BOT_L | SEG_CEN_H;
        break;
    case 'C':
    case 'c':
        displayData = SEG_TOP_H | SEG_BOT_H | SEG_BOT_L | SEG_BOT_L;
        break;
    case 'D':
    case 'd':
        displayData = SEG_TOP_R | SEG_BOT_R | SEG_BOT_H | SEG_BOT_L | SEG_CEN_H;
        break;
    case 'E':
    case 'e':
        displayData = SEG_TOP_H | SEG_BOT_H | SEG_BOT_L | SEG_BOT_L | SEG_CEN_H;
        break;
    case 'F':
    case 'f':
        displayData = SEG_TOP_H | SEG_BOT_L | SEG_BOT_L | SEG_CEN_H;
        break;
    case 'G':
        displayData = SEG_TOP_H | SEG_BOT_R | SEG_BOT_H | SEG_BOT_L | SEG_BOT_L;
        break;
    case 'g':
        displayData = SEG_TOP_H | SEG_TOP_R | SEG_BOT_R | SEG_BOT_H | SEG_BOT_L | SEG_CEN_H;
        break;
    case '!':
        displayData = SEG_TOP_R | SEG_DEC_P;
        break;
    case 'P':
    case 'p':
        displayData = SEG_TOP_H | SEG_TOP_R | SEG_BOT_L | SEG_BOT_L | SEG_CEN_H;
        break;
    case 'H':
        displayData = SEG_TOP_R | SEG_BOT_R | SEG_BOT_L | SEG_BOT_L | SEG_CEN_H;
        break;
    case 'h':
        displayData = SEG_BOT_R | SEG_BOT_L | SEG_BOT_L | SEG_CEN_H;
        break;
    case 'L':
        displayData = SEG_BOT_H | SEG_BOT_L | SEG_BOT_L;
        break;
    case '#':
        // Used to test all elements
        displayData = SEG_TOP_H | SEG_CEN_H | SEG_BOT_H | SEG_TOP_L | SEG_TOP_R | SEG_BOT_L | SEG_BOT_R | SEG_DEC_P;
        break;
    default:
        displayData = 0B00000000;
        break;
    }
    return displayData;
}



