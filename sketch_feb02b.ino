#include <avr/io.h>
#include <avr/interrupt.h>
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9340.h"


unsigned int i=0;
#define F_CPU 16000000UL
#define L_ARRAY 128
#define L_ARRAY_1 129
#define _sclk 13
#define _miso 12
#define _mosi 11
#define _cs 10
#define _dc 9
#define _rst 8
unsigned char c;
#define F_CPU 16000000UL
#define L_ARRAY 128
#define L_ARRAY_1 129

unsigned char ab[5]={0};
unsigned char b[5]={0};
 long a=0;
Adafruit_ILI9340 tft = Adafruit_ILI9340(_cs, _dc, _rst);
//global vars
uint8_t CLKcycleCounter = 0; // counts the number of clock cycles expired
volatile uint16_t pixels[L_ARRAY] = {0}; // pixel buffer - holds data from ADC
volatile uint16_t prepix[L_ARRAY] = {0}; // 
uint8_t  m, mi = 65, pix; // i is an index for loops, m is the mimimum pixel value
// D7=CLK
// D6=SI
//AO=A5
// ADC interrupt routine - this happens when the ADC is finished taking a sample
ISR(ADC_vect) {
  // if AO is sending pixel data (first 128 clock cycles of each frame)
  // then do an ADC and put it in the pixel buffer
  if(CLKcycleCounter < L_ARRAY) 
  {
    // start next CLK cycle
    __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
    __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
    __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
    PORTD |= (1 << PIND7); // CLK = 5V
    __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
    __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
    __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
    PORTD &= ~(1 << PIND7); // CLK = 0V
    pixels[CLKcycleCounter] =analogRead(A0); // high byte of ADC data
    CLKcycleCounter++; // iterate clock cycle counter
  } 
  else if(CLKcycleCounter == L_ARRAY ) 
  { // there is an extra clock cycle at the end (129) with no data
    // do a second extra clock for charge transfer
    // | CLKcycleCounter == L_ARRAY_1
    // start next CLK cycle
    __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
    __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
    __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
    PORTD |= (1 << PIND7); // CLK = 5V
    __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
    __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
    __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
    PORTD &= ~(1 << PIND7); // CLK = 0V
    CLKcycleCounter++; // iterate clock cycle counter
  } 
  else 
  { // start next frame by sending a pulse on SI
    PORTD |= (1 << PIND6); // SI = 5V
    __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
    __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
    PORTD |= (1 << PIND7); // CLK = 5V
    __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
    __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
    PORTD &= ~(1 << PIND6); // SI = 0V, must go low before next clock rise!!!
    __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
    __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
    PORTD &= ~(1 << PIND7); // CLK = 0V
    CLKcycleCounter = 0; // reset clock cycle counter to zero  
  }
  ADCSRA |= (1 << ADSC); // start next conversion
}

// this function executes once to set everything up
void setup() {
  // use serial library for communication with MATLAB
  Serial.begin(9600);
  tft.begin();

  // set up digital output pins on port B; CLK = B3 (pin 11) and SI = B0 (pin 8)
  DDRD = 0; // zero the register
  PORTD = 0; // zero the register
  DDRD |= (1 << PIND7) | (1 << PIND6); // CLK(B3) and SI(B0)
  PORTD &= ~(1 << PIND6); // CLK = 0V
  PORTD &= ~(1 << PIND7); // SI = 0V
 
  // ADC set-up; ADC will read the analog output (AO) voltage from the sensor
  sei(); // enable global interrupts
  ADCSRA = 0; // zero the register
  ADCSRA |= (1 << ADEN); // turn on ADC
  ADCSRA |= (1 << ADPS2); // set clock to F_CPU/16 = 1Mhz
  ADCSRA |= (1 << ADIE); // enable ADC interrupt
  ADMUX |= (1 << ADLAR) | (1 << REFS0) | (1 << MUX2) | (1 << MUX0); // ADC is on pin 5;
  
  // start first frame
  PORTD |= (1 << PIND6); // SI = 5V
  __asm__("nop\n\t"); // delay one CPU clock cycle = 62 tft.begin();.5 nanosec
  __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
  PORTD |= (1 << PIND7); // CLK = 5V
  __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
  __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
  PORTD &= ~(1 << PIND6); // SI = 0V, must go low before next clock rise!!!
  __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
  __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
  PORTD &= ~(1 << PIND7); // CLK = 0V

 
  // first conversion
  ADCSRA |= (1 << ADSC);
}

void loop() {

for(a=0;a<10;a++)
      {
        for(m<0;m<128;m++){
      i=i+pixels[m];
                           }
       }
      
 
  Serial.println(i);
  i=0;
  m=0;
  }

  

