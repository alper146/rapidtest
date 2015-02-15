#include <Adafruit_GFX.h>    // Core graphics library
#include "SWTFT.h" // Hardware-specific library
#include <avr/io.h>
#include <Wire.h>
#include "Adafruit_FRAM_I2C.h"


Adafruit_FRAM_I2C fram     = Adafruit_FRAM_I2C();
uint16_t          framAddr = 0;

#include <avr/interrupt.h>

int i;
unsigned char c;
#define F_CPU 16000000UL
#define L_ARRAY 128
#define L_ARRAY_1 129
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
int asd;
 int a=0;
 int b;
 SWTFT tft;

//global vars
uint8_t CLKcycleCounter = 0; 
uint16_t pixels[L_ARRAY] = {0}; 
volatile uint16_t data=0;
 uint16_t prepix[L_ARRAY] = {0}; 
 uint16_t aa[L_ARRAY] = {0};
 
// D7=CLK
// D6=SI
//AO=A5

ISR(ADC_vect) {
  
  if(CLKcycleCounter < L_ARRAY) 
  {
  
    __asm__("nop\n\t"); 
    __asm__("nop\n\t"); 
    __asm__("nop\n\t"); 
    PORTB |= (1 << PINB2); 
    __asm__("nop\n\t"); 
    __asm__("nop\n\t"); 
    __asm__("nop\n\t"); 
  PORTB &= ~(1 << PINB2); 
    data =analogRead(A0); 
    prepix[CLKcycleCounter]=data;
    CLKcycleCounter++; 
  } 
  else if(CLKcycleCounter == L_ARRAY ) 
  { 
    __asm__("nop\n\t"); 
    __asm__("nop\n\t"); 
    __asm__("nop\n\t"); 
   PORTB |= (1 << PINB2); 
    __asm__("nop\n\t"); 
    __asm__("nop\n\t"); 
    __asm__("nop\n\t"); 
  PORTB &= ~(1 << PINB2); 
    CLKcycleCounter++; 
  } 
  else 
  { 
  PORTB |= (1 << PINB3);
    __asm__("nop\n\t"); 
    __asm__("nop\n\t"); 
  PORTB |= (1 << PINB2);
    __asm__("nop\n\t"); 
    __asm__("nop\n\t"); 
   PORTB &= ~(1 << PINB3); 
    __asm__("nop\n\t"); 
    __asm__("nop\n\t");
   PORTB &= ~(1 << PINB2);
    CLKcycleCounter = 0;   
  }
  ADCSRA |= (1 << ADSC); 
}


void setup() {
 
  Serial.begin(9600);
 Serial.println(F("TFT LCD test"));
tft.reset();
   uint16_t identifier = tft.readID();
  tft.begin(identifier);
 
 
 DDRB |= (1 << PINB2) | (1 << PINB3);
  PORTB &= ~(1 << PINB2); 
  PORTB &= ~(1 << PINB3); 
 
  
  ADCSRA = 0; 
  ADCSRA |= (1 << ADEN); 
  ADCSRA |= (1 << ADPS2); 
  ADCSRA |= (1 << ADIE); 
  ADMUX |= (1 << ADLAR) | (1 << REFS0) | (1 << MUX2) | (1 << MUX0); 
    pinMode(10, OUTPUT); 
      pinMode(11, OUTPUT); 
 
  PORTB |= (1 << PINB3); 
  __asm__("nop\n\t"); 
  __asm__("nop\n\t"); 
  PORTB |= (1 << PINB2); 
  __asm__("nop\n\t"); 
  __asm__("nop\n\t"); 
  PORTB &= ~(1 << PINB3); 
  __asm__("nop\n\t"); 
  __asm__("nop\n\t"); 
 PORTB &= ~(1 << PINB2); 

tft.fillScreen(BLUE );
  ADCSRA |= (1 << ADSC);
}

void loop() {



tft.setRotation(0);
for(a=0;a<4095;a++){
 for(i=0;i<128;i++){
fram.write8(a, (prepix[i]>>8));
  fram.write8(a+1, (prepix[i]& 0xFF));
   c=fram.read8( a);
    b=c<<8;
    c=fram.read8(a+1);
    b=b+(c & 0xFF);
    Serial.println(b);
  a++;
 
 }
    }  

for(i=0;i<128;i++){
      aa[i] =pixels[i];
}
for(i=0;i<128;i++){
 for(a=0;a<=4095;a++){
    c=fram.read8(a);
    b=c<<8;
    c=fram.read8(a+1);
    b=b+(c & 0xFF);
  asd=asd+b;
  a=a+128;
  Serial.println(asd);
 }
    pixels[i]=asd/32;
  
asd=0;

}  
for(i=0;i<128;i++){
      
        if(pixels[i]!=aa[i]){
        tft.drawPixel(aa[i]/5, (2*i), BLUE);
         tft.drawPixel(aa[i]/5, (2*i)+1, BLUE);
        tft.drawPixel(pixels[i]/5, 2*i, BLACK);
        tft.drawPixel(pixels[i]/5, (2*i)+1, BLACK);
   tft.drawPixel(80/5, (2*i), RED);
    }
    

} 
      }
  

 

