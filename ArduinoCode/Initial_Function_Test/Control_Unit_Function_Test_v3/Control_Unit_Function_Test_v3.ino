/*
  DigitalReadSerial
 Reads a digital input on pin 2, prints the result to the serial monitor

 This example code is in the public domain.
 */
#include <SoftwareSerial.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif



// Remooe control push buttons:
#define pushRemA 10
#define pushRemB 11


// PWM stuff (all obn PWM pins)
#define PWM1 6
#define PWM2 7
#define PWM3 8
#define PWM4 9

// Neopixel Stuff:
#define LED1 14
#define LED2 15
#define LED3 16
#define LED4 17


//SoftwareSerial extSerial(18, 19); // RX, TX

// digital pin 2 has a pushbutton attached to it. Give it a name:
#define pushButtonA 20
#define pushButtonB 21

// This is for the serial shifted output data
#define sLatch 22   //Pin connected to ST_CP of 74HC595
#define sData 24    //Pin connected to DS of 74HC595
#define sClk 27   //Pin connected to SH_CP of 74HC595
#define outEnable 25  // Pin for the ~OE

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(60, LED1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(60, LED2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(60, LED3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(60, LED4, NEO_GRB + NEO_KHZ800);




long int number1 = 0;  // This will be the displayed data
long int number2 = 0;  // This will be the displayed data
long int number3 = 0;  // This will be the displayed data

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  Serial1.begin(115200);
  // make the pushbutton's pin an input:
  pinMode(pushRemA, INPUT);
  pinMode(pushRemB, INPUT);
  pinMode(pushButtonA, INPUT_PULLUP);
  pinMode(pushButtonB, INPUT_PULLUP);

  //set pins to output so you can control the shift register
  pinMode(sLatch, OUTPUT);
  pinMode(sClk, OUTPUT);
  pinMode(sData, OUTPUT); 
  pinMode(outEnable, OUTPUT); 

  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(PWM3, OUTPUT);
  pinMode(PWM4, OUTPUT);

    
  // Neopixel LED stuff:
  strip1.begin();
  strip1.show(); // Initialize all pixels to 'off'
  
}

// the loop routine runs over and over again forever:
void loop() {
  // Output data to the Timer:
    for(int i=0;i<999;i++)
  {
    if(i<10)
    {
      number1 = int7segment(i);
      number2 = B00000000;
      number3 = B00000000;
    }
    else if(i<100)
    {
      number1 = int7segment(i%10);
      number2 = int7segment(i/10);
      number3 = B00000000;
    }
    else if(i<1000)
    {
      number1 = int7segment(i-(i/10)*10);
      number2 = int7segment((i/10)%10);
      number3 = int7segment(i/100);
    }   
    
    // take the latchPin low so the LEDs don't change while you're sending in bits:
    digitalWrite(sLatch, LOW);
    // shift out the bits:
    // Send data via 3 shift registers: 
    // Put Decimal Point here:
    number1 = number1 | B10000000; 
    shiftOut(sData, sClk, MSBFIRST, number1);  // Puts out data onto all three digits 
    // Put Decimal Point here:
    number2 = number2 | B10000000;
    shiftOut(sData, sClk, MSBFIRST, number2); 
     // Put Decimal Point here:
    number3 = number3 | B10000000;
    shiftOut(sData, sClk, MSBFIRST, number3); 
    //take the latch pin high so the LEDs will light up:
    digitalWrite(sLatch, HIGH);
    
    // Put info out onto serial port for testing
//    Serial.println(i);
//    Serial.println(number1);
    //Serial.println(number2);
    //Serial.println(number3);
    
    //delay(100);   // Delay for a second

    // Check the buttons:
    
    // read the input pin:
    int buttonState = 0; // = digitalRead(pushRemA)||(~digitalRead(pushButtonA));

    if(digitalRead(pushRemA)==HIGH||digitalRead(pushButtonA)==LOW)
    {
      Serial1.println("A PRESSED!");
      buttonState = 1;
    }
    // print out the state of the button:
    Serial.print(buttonState);
    Serial.print("&");
    //buttonState = digitalRead(pushRemB)||(~digitalRead(pushButtonB));
    buttonState = 0;
    if(digitalRead(pushRemB)==HIGH||digitalRead(pushButtonB)==LOW)
    {
      Serial1.println("B PRESSED!");
      buttonState = 1;
    }
    // print out the state of the button:
    Serial.println(buttonState);
    //delay(100);        // delay in between reads for stability
    Serial1.println("ALIVE");
  
  
    // Test the LED strands ( all 4 of them):
  
    // Some example procedures showing how to display to the pixels:
    colorWipe(strip1.Color(0, 255, 0), 2); // Red
    colorWipe(strip1.Color(255, 0, 0), 2); // Green
    colorWipe(strip1.Color(0, 0, 255), 2); // Blue
  
    // Test the PWM functions

  
  }
}

// This function returns the correct binary value to display the integer
int int7segment (int segmentData)
{
  int displayData;
  
  switch (segmentData)
  {
    // This is the new table for Matt Venns LED display unit.
    case 0:
      displayData = B00111111;  // The number 0 in binary   
    break;
    case 1:
      displayData = B00000110;  // The number 1 in binary   
    break;
    case 2:
      displayData = B01011011;  // The number 2 in binary   
    break;
    case 3:
      displayData = B01001111;  // The number 3 in binary   
    break;
    case 4:
      displayData = B01100110;  // The number 4 in binary   
    break;
    case 5:
      displayData = B01101101;  // The number 5 in binary   
    break;
    case 6:
      displayData = B01111101;  // The number 6 in binary   
    break;
    case 7:
      displayData = B00000111;  // The number 7 in binary   
    break;
    case 8:
      displayData = B01111111;  // The number 8 in binary   
    break;
    case 9:
      displayData = B01101111;  // The number 9 in binary   
    break;
      
  }
  return displayData;
}


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip1.numPixels(); i++) {
    strip1.setPixelColor(i, c);
    i++;
    strip1.setPixelColor(i, c);   
    strip1.show();
    delay(wait);
  }
  for(uint16_t i=0; i<strip1.numPixels(); i++) {
    strip1.setPixelColor((strip1.numPixels()-i+1), strip1.Color(0, 0, 0));
    i++;
    strip1.setPixelColor((strip1.numPixels()-i+1), strip1.Color(0, 0, 0));   
    strip1.show();
    delay(wait);
  }
}

