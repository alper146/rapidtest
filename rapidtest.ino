#include <avr/interrupt.h>
#include <Keypad.h>
#include <avr/io.h>
#include <Wire.h>
#include "Adafruit_FRAM_I2C.h"
Adafruit_FRAM_I2C fram     = Adafruit_FRAM_I2C();
uint16_t          framAddr = 0;
int i;
int c=1;

unsigned char ab;

#define F_CPU 16000000UL
#define L_ARRAY 128
#define L_ARRAY_1 129
//global vars
uint16_t CLKcycleCounter = 0; 
//uint16_t pixels[256] = {0}; 
volatile uint16_t data=0;
 uint16_t prepix[256] ;//= {901,906,906,913,898,904,904,910,910,913,914,909,909,922,921,933,926,930,928,921,922,927,918,929,927,915,915,925,925,926,923,932,932,940,932,929,936,933,937,920,914,917,918,924,924,920,926,928,925,928,921,927,924,935,924,929,932,921,924,921,899,891,882,863,851,837,818,814,785,773,751,739,730,727,720,724,730,744,749,760,773,797,818,827,841,862,879,899,904,907,912,922,920,925,918,930,931,934,933,939,937,935,940,935,940,927,931,934,932,939,919,927,917,926,923,929,918,928,916,931,916,909,912,912,893,908,895,864,901,906,906,913,898,904,904,910,910,913,914,909,909,922,921,933,926,930,928,921,922,927,918,929,927,915,915,925,925,926,923,932,932,940,932,929,936,933,937,920,914,917,918,924,924,920,926,928,925,928,921,927,924,935,924,929,932,921,924,921,899,891,882,863,851,837,818,814,785,773,751,739,730,727,720,724,730,744,749,760,773,797,818,827,841,862,879,899,904,907,912,922,920,925,918,930,931,934,933,939,937,935,940,935,940,927,931,934,932,939,919,927,917,926,923,929,918,928,916,931,916,909,912,912,893,908,895,864};
int asd=0;
//uint16_t aa[256];
//uint8_t gain[256];
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
 byte rowPins[4] = {9,8,7,6}; //Rows 0 to 3
byte colPins[4]= {5,4,3,2}; //Columns 0 to 3
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},  
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

 ISR(ADC_vect) {
  
  if((CLKcycleCounter < L_ARRAY)) 
  {
  
    
      __asm__("nop\n\t"); 
        __asm__("nop\n\t"); 
          __asm__("nop\n\t"); 
    __asm__("nop\n\t"); 
     __asm__("nop\n\t"); 
    __asm__("nop\n\t"); 
    PORTB |= (1 << PINB2); 
   
    __asm__("nop\n\t"); 
    __asm__("nop\n\t"); 
     __asm__("nop\n\t"); 
       __asm__("nop\n\t"); 
    __asm__("nop\n\t"); 
      __asm__("nop\n\t"); 
  PORTB &= ~(1 << PINB2);
  if(c==0){
    data =analogRead(A1);
   
 prepix[CLKcycleCounter]=data;
   }
if(c==1){
    data =analogRead(A0);
   
  prepix[CLKcycleCounter+128]=data;
  }
     //int b=analogRead(A0);

    
    CLKcycleCounter++; 
  } 
  else if(CLKcycleCounter == L_ARRAY ) 
  { 
 
  __asm__("nop\n\t"); 
      __asm__("nop\n\t"); 
   PORTB |= (1 << PINB2); 
   
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
if(c==1){c=0;
ADMUX&=~(1<<MUX0);}
else if(c==0){c=1; ADMUX|=(1<<MUX0);
}
  }
  ADCSRA |= (1 << ADSC); 
}
void setup() {
 c=0;
  Serial.begin(9600);
  DDRB |= (1 << PINB2) | (1 << PINB3);
  PORTB &= ~(1 << PINB2); 
  PORTB &= ~(1 << PINB3); 
 
 fram.begin();
  
  ADCSRA = 0; 
  ADCSRA |= (1 << ADEN); 
  ADCSRA |= (1 << ADPS2)|(1<<ADPS1)|(1<<ADPS0); 
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
 //for(i=0;i<256;i++){gain[i]=2;}
}
void loop(){
char customKey = customKeypad.getKey();
 
if (customKey){
    Serial.print(customKey);
  }
   if(Serial.available()){
 ab=Serial.read();
  if(ab==10)
  {
   
   fram_write();
   fram_read();
   send_values();  
}
else if(ab==11){
    fram_write();
   fram_read();
  determine_gain();
 send_values();
  
}

else if(ab=12){
 uint16_t s;
   for(i=0;i<256;i++){
    s=fram.read8(2*i+1024);
    s=(s<<8)+fram.read8(2*i+1025);

 //Serial.println(s); 
Serial.write((s>>8) );
delay(10);
Serial.write(s&0xFF);
delay(10);
}
 
}
 
   }
  
 /*
   for(i=0;i<256;i++){
   Serial.println(prepix[i]);}*/
}
   void  fram_write(void){
  int b;
  uint16_t a;
  a=0;
     while(a<512){
 for(i=0;i<256;i++){
   b=prepix[i];
fram.write8(2*a, (b>>8));
  fram.write8(2*a+1, (b& 0xFF));
 a++;
 }
 
 }
 
  }
  
void fram_read(void){
   uint16_t a;
int x,d;
 a=0;
  asd=0;
  for(i=0;i<256;i++){
  a=i;
  while(a<512){
  d=fram.read8(2*a);
 x=d<<8;
  d=fram.read8(2*a+1);
  x=x+(d& 0xFF);
  a=a+256;
  asd=x+asd;
 
}
asd=asd/2;
fram.write8((2*i+1024), (asd>>8));
  fram.write8(2*i+1025, (asd& 0xFF));
 asd=0;
}

}
void inline send_values(void){
 uint16_t s;
 union Data
{
   float asd;
   byte  s2[4];
} data;  
 
  for(i=0;i<256;i++){
    s=fram.read8(2*i+1024);
    s=(s<<8)+fram.read8(2*i+1025);
  data.s2[3]=fram.read8(2*i+2050);
 data.s2[2]= fram.read8(2*i+2051);
 data.s2[1]= fram.read8(2*i+2052);
  data.s2[0]=fram.read8(2*i+2053);
s=(data.asd)*s;
 //Serial.println(s); 
Serial.write((s>>8) );
delay(10);
Serial.write(s&0xFF);
delay(10);
}
 
}
void  determine_gain(void){
  uint16_t s;
 union Data
{
   float asd;
   byte  s2[4];
} data;  
for(i=0;i<256;i++){
   s=fram.read8(2*i+1024);
    s=(s<<8)+fram.read8(2*i+1025);
  data.asd=(float)1023.00/s;
  
  fram.write8(2*i+2050,data.s2[3]);
  fram.write8(2*i+2051,data.s2[2]);
  fram.write8(2*i+2052,data.s2[1]);
  fram.write8(2*i+2053,data.s2[0]);
}
}
