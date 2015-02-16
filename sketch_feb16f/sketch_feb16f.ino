#include <avr/io.h>

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
uint16_t aa[128]={0};
uint16_t pix[128]={0};
int c=0;
void setup(void){
Serial.begin(9600);



}
void loop(void){
while(c<128){
if (Serial.available()) {
a=Serial.read();


if(b==0){
  aa[c]=a<<8;
 
      b=1;  }
              else{
          b=0;
  aa[c]=aa[c]+(a&0xFF);
c++; 
         Serial.println(aa[c]);         }
         
}  }  


  for(i=0;i<128;i++){
         

      //   tft.drawFastHLine(20, (2*i)+1,pix[i], RED);
       // tft.drawFastHLine(20, (2*i)+1,aa[i], BLACK);
   
    }
    for(i=0;i<128;i++){
pix[i]=aa[i];
}


}
