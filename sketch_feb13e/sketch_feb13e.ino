#include <Adafruit_GFX.h>    // Core graphics library
#include "SWTFT.h" // Hardware-specific library
#include <avr/io.h>
//#include <avr/interrupt.h>
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
unsigned char ab[5]={0};
unsigned char b[5]={1};
 long a=0;
 SWTFT tft;

//global vars
uint8_t CLKcycleCounter = 0; // counts the number of clock cycles expired
volatile uint16_t pixels[L_ARRAY] = {0}; // pixel buffer - holds data from ADC
 uint16_t prepix[L_ARRAY] = {0}; //
 uint16_t aa[L_ARRAY] = {0};
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
    PORTB |= (1 << PINB2); // CLK = 5V
    __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
    __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
    __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
  PORTB &= ~(1 << PINB2); // CLK = 0V
    pixels[CLKcycleCounter] =analogRead(A5); // high byte of ADC data
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
   PORTB |= (1 << PINB2); // CLK = 5V
    __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
    __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
    __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
  PORTB &= ~(1 << PINB2); // CLK = 0V
    CLKcycleCounter++; // iterate clock cycle counter
  } 
  else 
  { // start next frame by sending a pulse on SI
  PORTB |= (1 << PINB3); // SI = 5V
    __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
    __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
  PORTB |= (1 << PINB2); // CLK = 5V
    __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
    __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
   PORTB &= ~(1 << PINB3); // SI = 0V, must go low before next clock rise!!!
    __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
    __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
   PORTB &= ~(1 << PINB2); // CLK = 0V
    CLKcycleCounter = 0; // reset clock cycle counter to zero  
  }
  ADCSRA |= (1 << ADSC); // start next conversion
}

// this function executes once to set everything up
void setup() {
  // use serial library for communication with MATLAB
  Serial.begin(9600);
 Serial.println(F("TFT LCD test"));
tft.reset();
   uint16_t identifier = tft.readID();
  tft.begin(identifier);
 
  // set up digital output pins on port B; CLK = B3 (pin 11) and SI = B0 (pin 8)
 //8IDDRB = 0; // zero the register
//PORTB = 0; // zero the register
 DDRB |= (1 << PINB2) | (1 << PINB3); // CLK(B3) and SI(B0)
  PORTB &= ~(1 << PINB2); // CLK = 0V
  PORTB &= ~(1 << PINB3); // SI = 0V
 
  // ADC set-up; ADC will read the analog output (AO) voltage from the sensor
  sei(); // enable global interrupts
  ADCSRA = 0; // zero the register
  ADCSRA |= (1 << ADEN); // turn on ADC
  ADCSRA |= (1 << ADPS2); // set clock to F_CPU/16 = 1Mhz
  ADCSRA |= (1 << ADIE); // enable ADC interrupt
  ADMUX |= (1 << ADLAR) | (1 << REFS0) | (1 << MUX2) | (1 << MUX0); // ADC is on pin 5;
    
  // start first frame
  PORTB |= (1 << PINB3); // SI = 5V
  __asm__("nop\n\t"); // delay one CPU clock cycle = 62 tft.begin();.5 nanosec
  __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
  PORTB |= (1 << PINB2); // CLK = 5V
  __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
  __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
  PORTB &= ~(1 << PINB3); // SI = 0V, must go low before next clock rise!!!
  __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
  __asm__("nop\n\t"); // delay one CPU clock cycle = 62.5 nanosec
 PORTB &= ~(1 << PINB2); // CLK = 0V

tft.fillScreen(BLUE );/*
    tft.setRotation(0);
    tft.setTextSize(2);
   tft.setCursor(15, 270);
  tft.println("WHITE AREA:");
   tft.setCursor(120, 290);
   tft.setTextSize(1);
  tft.println("of  131072");
    tft.setCursor(0, 0);
    tft.setRotation(1);
     tft.setCursor(200,200);
    */
      tft.setTextSize(2);/*
  tft.setCursor(15, 300);
  tft.println(0);
    tft.setCursor(30, 300);
  tft.println(0);
    tft.setCursor(45, 300);
  tft.println(0);
    tft.setCursor(60, 300);
  tft.println(0);
    tft.setCursor(75, 300);
  tft.println(0);
    tft.setCursor(90, 300);
  tft.println(0);
  
 */
  // first conversion
  ADCSRA |= (1 << ADSC);
}

void loop() {

a=0;

tft.setRotation(0);
      
      for(i=0;i<128;i++){
       aa[i] =pixels[i];
        if(prepix[i]!=aa[i]){
        tft.drawPixel(prepix[i]/5, (2*i), BLUE);
         tft.drawPixel(prepix[i]/5, (2*i)+1, BLUE);
        tft.drawPixel(aa[i]/5, 2*i, BLACK);
        tft.drawPixel(aa[i]/5, (2*i)+1, BLACK);
   tft.drawPixel(80/5, (2*i), RED);
    }
     prepix[i]=aa[i];
/*
    if(pixels[i]<prepix[i])  {
     tft.setRotation(0);
    tft.drawFastHLine(10,2*i, pixels[i]/5, ILI9340_WHITE);
    }
    else if(pixels[i]>prepix[i]) {
    
    tft.drawFastHLine(9+(pixels[i]/5),2*i, ((1024-pixels[i])/5), ILI9340_BLACK);
    
    //tft.drawFastHLine(10,2*i+1, pixels[i]/5, ILI9340_BLACK);
    //tft.drawFastHLine(9+(pixels[i]/5),2*i+1, ((1024-pixels[i])/5), ILI9340_WHITE);
    prepix[i]=pixels[i]; 
    }                
 
 
  
   
   else{
      tft.setRotation(2);
    
    tft.drawFastHLine(26,(320-(2*i))-3, (1023-pixels[i])/5
    , ILI9340_BLACK);
    
    prepix[i]=pixels[i];
    a=a+pixels[i];
   }*/
} 
     
 
  ab[0]=a%10;
ab[1]=(a/10)%10;
ab[2]=(a/100)/10;
ab[3]=(a/1000)%10;  
ab[4]=(a/10000)%10;
ab[5]=(a/100000)%10;
/*
if(ab[5]!=b[5]){
    tft.fillRect(15, 300, 15, 15,
             ILI9340_RED);
   tft.setCursor(15, 300);
  tft.println(ab[5]);
 
}
if(ab[4]!=b[4]){
  tft.fillRect(30, 300, 15, 15,
             ILI9340_RED);
             tft.setCursor(30, 300);
   tft.println(ab[4]);
}
if(ab[3]!=b[3]){
  tft.fillRect(45, 300, 15, 15,
             ILI9340_RED);
  tft.setCursor(45, 300);
   tft.println(ab[3]);
}
if(ab[2]!=b[2]){
  tft.fillRect(60, 300, 15, 15,
             ILI9340_RED);
  tft.setCursor(60, 300);
   tft.println(ab[2]);
}
if(ab[1]!=b[1]){
  tft.fillRect(75, 300, 15, 15,
             ILI9340_RED);
  tft.setCursor(75, 300);
   tft.println(ab[1]);
}
if(ab[0]!=b[0]){
  tft.fillRect(90, 300, 15, 15,
             ILI9340_RED);
             
  tft.setCursor(90, 300);
   tft.println(ab[0]);
}//  tft.setRotation(0);
for(c=0;c<6;c++){
b[c]=ab[c];
}*/
  }

