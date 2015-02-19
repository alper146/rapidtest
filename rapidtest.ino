#include <avr/io.h>
#include <Wire.h>
#include "Adafruit_FRAM_I2C.h"


Adafruit_FRAM_I2C fram     = Adafruit_FRAM_I2C();
uint16_t          framAddr = 0;

#include <avr/interrupt.h>

int i;
int c;
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
unsigned long asd;
 int a=0;
 int b;


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
const int buttonPin = 2; 
int buttonState = 0; 
void setup() {
 
  Serial.begin(9600);

  pinMode(buttonPin, INPUT);   


 fram.begin();
 
 DDRB |= (1 << PINB2) | (1 << PINB3);
  PORTB &= ~(1 << PINB2); 
  PORTB &= ~(1 << PINB3); 
 
  
  ADCSRA = 0; 
  ADCSRA |= (1 << ADEN); 
  ADCSRA |= (1 << ADPS2); 
  ADCSRA |= (1 << ADIE); 
  ADMUX |= ((1 << ADLAR) | (1 << REFS0)); 
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


  ADCSRA |= (1 << ADSC);
}

void loop() {

 

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  while( !(digitalRead(buttonPin) == HIGH)){}

a=0;
while(a<2048){
 for(i=0;i<128;i++){
   c=prepix[i];
fram.write8(2*a, (c>>8));
  fram.write8(2*a+1, (c& 0xFF));
 a++;
 }
 
 }
    

a=0;
asd=0;
for(i=0;i<128;i++){
  a=i;
while(a<2049){
c=fram.read8(2*a);
    b=c<<8;
    c=fram.read8(2*a+1);
    b=b+(c & 0xFF);
    a=a+128;
   asd=b+asd;
}
aa[i]=asd/14;
 
 asd=0;
}
for(i=0;i<128;i++){
  c=aa[i];
Serial.write((c>>8) );
delay(10);
Serial.write(c&0xFF);
delay(10);
}
/*
 for(a=0;a<2048;a++){
    c=fram.read8(2*a);
    b=c<<8;
    c=fram.read8(2*a+1);
    b=b+(c & 0xFF);
   asd=asd+b;
//  Serial.println(asd);
 }
 asd=asd/2048;
 Serial.println(asd);
   
  */


 /*
for(i=0;i<128;i++){
      
        if(pixels[i]!=aa[i]){
        tft.drawPixel(aa[i]/5, (2*i), BLUE);
         tft.drawPixel(aa[i]/5, (2*i)+1, BLUE);
        tft.drawPixel(pixels[i]/5, 2*i, BLACK);
        tft.drawPixel(pixels[i]/5, (2*i)+1, BLACK);
   tft.drawPixel(80/5, (2*i), RED);
    }}
    */


      }
  

 
