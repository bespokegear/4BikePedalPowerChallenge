#include "SevenSegmentDisplay.h"
#include <Arduino.h>

SevenSegmentDisplay::SevenSegmentDisplay(uint8_t SLatchPin, uint8_t SClkPin, uint8_t SDataPin) :
    _SLatchPin(SLatchPin),
    _SClkPin(SClkPin),
    _SDataPin(SDataPin)
{
#ifdef DEBUG7SEG
    Serial.print(F("SevenSegmentDisplay::SevenSegmentDisplay lat="));
    Serial.print(SLatchPin);
    Serial.print(F(" clk="));
    Serial.print(SClkPin);
    Serial.print(F(" dat="));
    Serial.println(SDataPin);
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
    pinMode(_SLatchPin, OUTPUT);
    pinMode(_SClkPin,   OUTPUT);
    pinMode(_SDataPin,  OUTPUT);
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
    // Converts digits and some alpha values to binary which turns
    // on the various elements of the seven segment display:
    //
    // 0B00000001 . decimal
    // 0B00000010 . centre horizontal
    // 0B00000100 . top left vertical
    // 0B00001000 . bottom left vertical
    // 0B00010000 . bottom horizontal
    // 0B00100000 . bottom right vertical
    // 0B01000000 . top right vertical
    // 0B10000000 . top horizontal

    uint8_t displayData;

    switch (segmentData)
    {
    case 0:
    case '0':
    case 'O':
        displayData = 0B11111100;
        break;
    case 1:
    case '1':
        displayData = 0B01100000;
        break;
    case 2:
    case '2':
        displayData = 0B11011010;
        break;
    case 3:
    case '3':
        displayData = 0B11110010;
        break;
    case 4:
    case '4':
        displayData = 0B01100110;
        break;
    case 5:
    case '5':
        displayData = 0B10110110;
        break;
    case 6:
    case '6':
        displayData = 0B10111110;
        break;
    case 7:
    case '7':
        displayData = 0B11100000;
        break;
    case 8:
    case '8':
        displayData = 0B11111110;
        break;
    case 9:
    case '9':
        displayData = 0B11110110;
        break;
    case 10:
    case '.': 
        // Decimal point ON
        displayData = 0B00000001; 
        break;
    case '_':
        displayData = 0B00010000;  
        break;
    case '-':
        displayData = 0B00000010;  
        break;
    case '=':
        displayData = 0B00010010;  
        break;
    case 'o':
        displayData = 0B00111010;  
        break;
    case 'A':
    case 'a':
        displayData = 0B11101110;  
        break;
    case 'B':
    case 'b':
        displayData = 0B00111110;  
        break;
    case 'C':
    case 'c':
        displayData = 0B10011100;  
        break;
    case 'D':
    case 'd':
        displayData = 0B01111010;  
        break;
    case 'E':
    case 'e':
        displayData = 0B10011110;  
        break;
    case 'F':
    case 'f':
        displayData = 0B10001110;  
        break;
    case 'G':
        displayData = 0B10111100;  
        break;
    case 'g':
        displayData = 0B11110110;  
        break;
    case '!':
        displayData = 0B01000001;  
        break;
    case 'P':
    case 'p':
        displayData = 0B11001110;  
        break;
    case 'H':
        displayData = 0B01101110;  
        break;
    case 'h':
        displayData = 0B00101110;  
        break;
    case 'L':
        displayData = 0B00011100;  
        break;
    default:
        displayData = 0B00000000;
        break;
    }
    return displayData;

    // 0B10000000 . top horizontal
    // 0B01000000 . top right vertical
    // 0B00100000 . bottom right vertical
    // 0B00010000 . bottom horizontal
    // 0B00001000 . bottom left vertical
    // 0B00000100 . top left vertical
    // 0B00000010 . centre horizontal
    // 0B00000001 . decimal
}



