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
float uint16_t aa[L_ARRAY] = {0};
 float gain[L_ARRAY] = {1};
 
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
int calibState = 0; 
const int calibPin = 3;
void fram_write(void);
void fram_read(void);
void determine_gains(void);
void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(3, INPUT);
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
  while( !((digitalRead(buttonPin) == HIGH)||(digitalRead(3)==HIGH))){}
  if(digitalRead(buttonPin)){
  Serial.write(11 );
  delay(100);
  a=0;
  fram_write();   
 fram_read();
 send_values();
  }
  if(digitalRead(calibPin)){
   Serial.write(11 );
  delay(100);
  a=0;
  fram_write();   
 fram_read();
 determine_gains();
 send_values();
  }
    }
    
 void inline fram_write(void){
   while(a<4096){
 for(i=0;i<128;i++){
   c=prepix[i];
fram.write8(2*a, (c>>8));
  fram.write8(2*a+1, (c& 0xFF));
 a++;
 }
 
 }
 
  }
void inline fram_read(void){

 a=0;
  asd=0;
  for(i=0;i<128;i++){
  a=i;
  while(a<4096){
  c=fram.read8(2*a);
  b=c<<8;
  c=fram.read8(2*a+1);
  b=b+(c & 0xFF);
  a=a+128;
  asd=b+asd;
}
aa[i]=asd/32;
 
 asd=0;
}
}
void inline send_values(void){
  for(i=0;i<128;i++){
  c=aa[i]*gain[i];
Serial.write((c>>8) );
delay(10);
Serial.write(c&0xFF);
delay(10);
}

}
void inline determine_gains(void){
for(i=0;i<128;i++){
  gain[i]=1023/aa[i];
}

}

 
