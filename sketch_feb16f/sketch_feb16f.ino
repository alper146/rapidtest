#include <avr/io.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include "SWTFT.h" // Hardware-specific library
#define F_CPU 16000000UL

 int a,i;
int b=0,d=0;
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
SWTFT tft;
uint16_t aa[256]={0};
uint16_t bb[128]={0};
uint16_t pix[128]={0};
int c=0;
void setup(void){
Serial.begin(9600);
  uint16_t identifier = tft.readID();
  tft.begin(identifier);
 tft.fillScreen(BLUE );

}
void loop(void){
  
while (Serial.available()<62) {} 
for(int n=0; n<62; n++){
  aa[n] = Serial.read();
}
while (Serial.available()<62) {} 
for(int n=0; n<62; n++){
  aa[n+62] = Serial.read();
}
while (Serial.available()<62) {} 
for(int n=0; n<62; n++){
  aa[n+124] = Serial.read();
}
while (Serial.available()<62) {} 
for(int n=0; n<62; n++){
  aa[n+186] = Serial.read();
}
while (Serial.available()<8) {} 
for(int n=0; n<8; n++){
  aa[n+248] = Serial.read();
}
for(int n=0; n<128; n=n+1){
  
 bb[n]=(aa[2*n]<<8)+(aa[2*n+1]&0xFF);

}


  for(i=0;i<128;i++){
         

         tft.drawFastHLine(20, (2*i)+1,pix[i]/5, RED);
        tft.drawFastHLine(20, (2*i)+1,bb[i]/5, BLACK);
   
    }
    for(i=0;i<128;i++){
pix[i]=bb[i];
c=0;}


}
