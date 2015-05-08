#include <Adafruit_GFX.h>    // Core graphics library
#include "SWTFT.h" // Hardware-specific library
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define BOXSIZE 70

uint8_t aa[512]={0};
int freeRam () 
{
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}
uint16_t inline make(uint16_t k){
return ((aa[2*k]<<8)+(aa[2*k+1]&0xFF));
}

void esitlik(uint16_t k,uint16_t sayi){
aa[2*k]=sayi>>8;
aa[2*k+1]=sayi&0xFF;
}
SWTFT tft;

int komut;
int d=0;


//uint16_t prepix[256]={0};
/*int piksel=0;
 unsigned char flag2=0;*/
//unsigned char flag=0;
//int komut=0;

int komut2=0;
void returnmenu(void);
void processing_data(void){
int a,i;
  while (Serial.available()<62) {
  } 
  for(i=0; i<62; i++){
    aa[i] = Serial.read();
  }
  while (Serial.available()<62) {
  } 
  for(i=0; i<62; i++){
    aa[i+62] = Serial.read();
  }
  while (Serial.available()<62) {
  } 
  for(i=0; i<62; i++){
    aa[i+124] = Serial.read();
  }
  while (Serial.available()<62) {
  } 
  for( i=0; i<62; i++){
    aa[i+186] = Serial.read();
  }
  /*********************************/  ///////////

  while (Serial.available()<62) {
  } 
  for(i=0; i<62; i++){
    aa[i+248] = Serial.read();
  }
  while (Serial.available()<62) {
  } 
  for(i=0; i<62; i++){
    aa[i+310] = Serial.read();
  }
  while (Serial.available()<62) {
  } 
  for(i=0; i<62; i++){
    aa[i+372] = Serial.read();
  }
  while (Serial.available()<62) {
  } 
  for( i=0; i<62; i++){
    aa[i+434] = Serial.read();
  }
  /*********************************/  ///////////
  while (Serial.available()<16) {
  } 
  for(i=0; i<16; i++){
    aa[i+496] = Serial.read();
  }
for(i=0;i<256;i++){
   tft.drawFastHLine(20, (i)+1,1023/5, RED);
   tft.drawFastHLine(20, (i)+1,(make(i))/5, BLACK);
   }
  
   for( i=1;i<256;i++){
   esitlik(i,0.90*(make(i))+0.10*(make(i-1)));
   }
  uint16_t piksel;
   uint16_t b=1023;
   esitlik(255,1023);
   for(i=0;i<256;i++){
   if(make(i)<b){b=(make(i));  piksel=i; }
   }
   uint16_t flagRight=0;
   i=0;
   while(flagRight==0){
if(((make(piksel+i)-2)<((make(piksel+i+1)+make(piksel+i+2)+make(piksel+i+3)+make(piksel+i+4)+make(piksel+i+5)+make(piksel+i+6)+make(piksel+i+7)+make(piksel+i+8))/8))){}
else{flagRight=i;}
  
   i++;
   }
   i=0;
   uint16_t flagLeft=0;
   while(flagLeft==0){
if(((make(piksel-i)-2)<((make(piksel-i-1)+make(piksel-i-2)+make(piksel-i-3)+make(piksel-i-4)+make(piksel-i-5)+make(piksel-i-6)+make(piksel-i-7)+make(piksel-i-8))/8))){}
else{flagLeft=i;}
 
   i++;
   }
   /////////////////////2.part
   uint16_t flag2Right=0;
   uint16_t flag2Left=0;
   uint16_t b2=1023;
   uint16_t piksel2;
    for(i=0;i<(piksel-flagLeft);i++){
   if(make(i)<b2){b2=(make(i));  piksel2=i; }
   }
   for(i=(piksel+flagRight);i<256;i++){
   if(make(i)<b2){b2=(make(i));  piksel2=i; }
   }
   
   i=0;
   while(flag2Right==0){
if(((make(piksel2+i)-2)<((make(piksel2+i+1)+make(piksel2+i+2)+make(piksel2+i+3)+make(piksel2+i+4)+make(piksel2+i+5)+make(piksel2+i+6)+make(piksel2+i+7)+make(piksel2+i+8))/8))){}
else{flag2Right=i;}
  
   i++;
   }
   i=0;
  
   while(flag2Left==0){
     i++;
if(((make(piksel2-i)-2)<((make(piksel2-i-1)+make(piksel2-i-2)+make(piksel2-i-3)+make(piksel2-i-4)+make(piksel2-i-5)+make(piksel2-i-6)+make(piksel2+i+7)+make(piksel2+i+8))/8))){}
else{flag2Left=i;}
 
   }
   ///////////////////////////////////2.partend
   d=0;
   for(i=(piksel-flagLeft);i<piksel;i++)
{
    tft.drawLine(20+make(i)/5,i+1,20+(make(i+1))/5,i+2, GREEN);
   d=d+(1023-make(i)-make(piksel-flagLeft));
 }
  
   for(i=(piksel);i<(piksel+flagRight);i++)
 { d=d+1023-make(i)-make(piksel+flagRight);
    tft.drawLine(20+make(i)/5,i+1,20+(make(i+1))/5,i+2, GREEN);}
   /////////////////////////2.part
   int d2=0;
   for(i=(piksel2-flag2Left);i<piksel2;i++)
   {
   tft.drawLine(20+make(i)/5,i+1,20+(make(i+1))/5,i+2, WHITE);
   d2=d2+1023-make(i)-make(piksel2-flag2Left);}
   
   for(i=(piksel2);i<(piksel2+flag2Right);i++)
 {
   d2=d2+1023-make(i)-make(piksel2+flag2Right);
   tft.drawLine(20+(make(i))/5,i+1,20+(make(i+1))/5,i+2, WHITE); }
   
   tft.drawLine(20+(make(piksel+flagRight))/5,piksel+flagRight,20+(make(piksel-flagLeft))/5,piksel-flagLeft, GREEN);  
   tft.drawLine(20+(make(piksel2+flag2Right))/5,piksel2+flag2Right,20+(make(piksel2-flag2Left))/5,piksel2-flag2Left, WHITE);
   /////////////////////////2.part end
   if(flagLeft<flag2Left){b=1;}
   else{b=2;}
   /*if(b==1){
   for(i=0;i<(piksel-flagLeft);i++){esitlik(i,1023);tft.drawFastHLine(20, (i)+1,1023/5, RED);
   tft.drawFastHLine(20, (i)+1,(make(i))/5, WHITE);}
   for(i=piksel+flagRight;i<flag2Left;i++){esitlik(i,1023);tft.drawFastHLine(20, (i)+1,1023/5, RED);
   tft.drawFastHLine(20, (i)+1,(make(i))/5, WHITE);}
   for(i=piksel2+flag2Right;i<256;i++){esitlik(i,1023);tft.drawFastHLine(20, (i)+1,1023/5, RED);
   tft.drawFastHLine(20, (i)+1,(make(i))/5, WHITE);}
   }
   else if(b==2){
    for(i=0;i<(piksel2-flag2Left);i++){esitlik(i,1023);tft.drawFastHLine(20, (i)+1,1023/5, RED);
   tft.drawFastHLine(20, (i)+1,(make(i))/5, BLACK);}
   for(i=piksel2+flag2Right;i<(piksel-flagLeft);i++){esitlik(i,1023);tft.drawFastHLine(20, (i)+1,1023/5, RED);
   tft.drawFastHLine(20, (i)+1,(make(i))/5, BLACK);}
 for(i=piksel+flagRight;i<256;i++){esitlik(i,1023);tft.drawFastHLine(20, (i)+1,1023/5, RED);
   tft.drawFastHLine(20, (i)+1,(make(i))/5, BLACK);}
 
   }*/
   
  // d=(((flagLeft+flagRight)*1023)-d);
   tft.fillRect(10,300,130,130,BLUE);
   tft.setCursor(10,270);
   tft.setTextSize(1);
  /* tft.print((freeRam()));
   tft.print(" ");*/
   tft.print(F("White:"));tft.print(d2);tft.print(F(" "));tft.print(F("Green:"));tft.println(d);
   tft.println(F(""));
   tft.print(F("Peak_white:"));tft.print(piksel2);tft.print(F(" ")); tft.print(F("Peak_green:"));tft.println(piksel);
   tft.println(F(""));
    tft.print(F("Max.white:"));tft.print(1023-make(piksel2)-make(piksel2-flag2Left));tft.print(F(" ")); tft.print(F("Max.green:"));tft.print(1023-make(piksel)-make(piksel-flagLeft));tft.print(F(" "));
/*  tft.print((piksel)); tft.print(" ");
    tft.print((piksel2)); tft.print(" ");
    tft.print((flagRight)); tft.print(" ");
    tft.print((flagLeft)); 
   
    /*
  for(i=0;i<256;i++){
   tft.drawFastHLine(20, (i)+1,1023/5, RED);
   tft.drawFastHLine(20, (i)+1,(make(i))/5, BLACK);
   }*/
  /*
   tft.drawFastHLine(20,piksel-flagLeft,1023/5,RED);
    tft.drawFastHLine(20,piksel+flagRight,1023/5,BLUE);
    tft.drawFastHLine(20,piksel2-flag2Left,1023/5,YELLOW);
     tft.drawFastHLine(20,piksel2+flag2Right,1023/5,WHITE);
  
    
  /*  tft.setCursor(10,30);
   tft.println(piksel);
   tft.println(flag);
   tft.println(flag2);*/
  //tft.println(prepix[piksel]);
}
void processing_data2(void){
int a,i;
  while (Serial.available()<62) {
  } 
  for(i=0; i<62; i++){
    aa[i] = Serial.read();
  }
  while (Serial.available()<62) {
  } 
  for(i=0; i<62; i++){
    aa[i+62] = Serial.read();
  }
  while (Serial.available()<62) {
  } 
  for(i=0; i<62; i++){
    aa[i+124] = Serial.read();
  }
  while (Serial.available()<62) {
  } 
  for( i=0; i<62; i++){
    aa[i+186] = Serial.read();
  }
  /*********************************/  ///////////

  while (Serial.available()<62) {
  } 
  for(i=0; i<62; i++){
    aa[i+248] = Serial.read();
  }
  while (Serial.available()<62) {
  } 
  for(i=0; i<62; i++){
    aa[i+310] = Serial.read();
  }
  while (Serial.available()<62) {
  } 
  for(i=0; i<62; i++){
    aa[i+372] = Serial.read();
  }
  while (Serial.available()<62) {
  } 
  for( i=0; i<62; i++){
    aa[i+434] = Serial.read();
  }
  /*********************************/  ///////////
  while (Serial.available()<16) {
  } 
  for(i=0; i<16; i++){
    aa[i+496] = Serial.read();
  }

    /*for( i=1;i<256;i++){
   esitlik(i,0.25*(make(i))+0.75*(make(i-1)));
   }*/
  for(i=0;i<256;i++){
   tft.drawFastHLine(20, (i)+1,1023/5, RED);
   tft.drawFastHLine(20, (i)+1,(make(i))/5, BLACK);
   }
    
  /*  tft.setCursor(10,30);
   tft.println(piksel);
   tft.println(flag);
   tft.println(flag2);*/
  //tft.println(prepix[piksel]);
}
void menu1(void){
  komut=10;
  tft.setCursor(10,10);
  tft.fillScreen(BLACK);
  tft.println(F("choose an algorithm:"));

  while(!Serial.available()){
  }
  komut2=Serial.parseInt();

  if(komut2==0){
    returnmenu();
    return;
  }
  else if(komut2==3){
    returnmenu();
    return;
  }
  else{
    tft.println(F("you have entered invalid argument. please type again."));
    menu1();
    return;  
  }

}
void menu2(void){
  komut=10;
  tft.fillScreen(BLUE);
  tft.setCursor(10,300);
  tft.setTextSize(2);
  tft.println(F("LOADING.."));
  Serial.write(10);
  processing_data();
  while(!Serial.available()){
  }
  komut=Serial.parseInt();
  if(komut==0){
    returnmenu();
  }

}
void menu3(void){

  komut=10;
  tft.fillScreen(BLUE);
  tft.setCursor(10,300);
  tft.setTextSize(2);
  tft.println(F("calibrating"));
  Serial.write(11);
  processing_data2();
  while(!Serial.available()){
  }
  komut=Serial.parseInt();
  if(komut==0){
    returnmenu();
  }
}
void menu4(void){
    komut=10;
  tft.fillScreen(BLUE);
  tft.setCursor(10,300);
  tft.setTextSize(2);
  tft.println(F("calibrating"));
  Serial.write(13);
  processing_data2();
  while(!Serial.available()){
  }
  komut=Serial.parseInt();
  if(komut==0){
    returnmenu();
  }

}
void menu5(void){
 komut=10;
  tft.fillScreen(BLUE);
  tft.setCursor(10,300);
  tft.setTextSize(2);
  tft.println(F("LOADING.."));
  Serial.write(12);
processing_data2();
 while(!Serial.available()){
  }
  komut=Serial.parseInt();
  if(komut==0){
    returnmenu();
  }
}
void komut_al(void){
  while(!Serial.available()){
  }
  komut= Serial.parseInt();


  //komut=character;

  tft.setCursor(10,290);
  tft.fillRect(0,270,40,40,BLACK);
  tft.setTextSize(2);
  tft.println(komut); 
}
void menu_sec(void){
  switch(komut){
  case 1:
    menu1();
    break;
  case 2:
    menu2();
    break;
  case 3:
    menu3();
    break;
  case 4:
    menu4();

    break;
  case 5:
    menu5();
  case 10:

    break;
  }

}
void setup(void) {
  Serial.begin(9600);
  tft.reset();
  uint16_t identifier = tft.readID();


  tft.begin(identifier);
  returnmenu();

}

void loop(void){
  komut_al();
  menu_sec();


}

void returnmenu(void){
  tft.fillScreen(BLACK);
  tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
  tft.setCursor(10,10);
  tft.setTextSize(1);
  tft.print(F("algorithms"));
  tft.setCursor(10,40);
  tft.setTextSize(2);
  tft.print(F("1"));
  tft.fillRect(80, 0, BOXSIZE, BOXSIZE, RED);
  tft.setCursor(80,10);
  tft.setTextSize(1);
  tft.print(F("Run Test"));
  tft.setCursor(80,40);
  tft.setTextSize(2);
  tft.print(F("2"));
  tft.fillRect(160,0, BOXSIZE, BOXSIZE, RED);
  tft.setCursor(160,10);
  tft.setTextSize(1);
  tft.print(F("Calibration"));
  tft.setCursor(160,40);
  tft.setTextSize(2);
  tft.print(F("3"));
  //   SATIR 2
  tft.fillRect(0, 80, BOXSIZE, BOXSIZE, RED);
  tft.setCursor(10,90);
  tft.setTextSize(1);
  tft.println(F("set para-"));
  tft.println(F("  meters"));
  tft.setCursor(10,120);
  tft.setTextSize(2);
  tft.print(F("4"));
  tft.fillRect(80, 80, BOXSIZE, BOXSIZE, RED);
  tft.setCursor(80,80);
  tft.setTextSize(1);
  tft.print(F("Show Data"));
  tft.setCursor(80,120);
  tft.setTextSize(2);
  tft.print(F("5"));
  tft.fillRect(160,80, BOXSIZE, BOXSIZE, RED);
  tft.setCursor(160,90);
  tft.setTextSize(1);
  tft.println(F("Return Menu"));
  tft.setCursor(160,120);
  tft.setTextSize(2);
  tft.print(F("0"));
  tft.setCursor(0,250);
  tft.setTextSize(3);
  tft.print(F("Enter number:"));
   tft.setCursor(10,300);
   tft.setTextSize(2);
   tft.print(freeRam()); 
}
