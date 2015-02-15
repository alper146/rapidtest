
#include <Adafruit_GFX.h>    // Core graphics library
#include <SWTFT.h> // Hardware-specific library
#include <SWTouch.h>
#include <SWTFT_Buttons.h>

SWTFT tft;
SWTouch touch(&tft);
SWTFT_Buttons buttons(&tft, &touch);
int but1, but2, but3, but4;

#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define GRAY    0x7BEF
#define WHITE   0xFFFF

void setup()
{
  Serial.begin(9600);
  Serial.println(F("TFT LCD test"));
  tft.reset();
  uint16_t identifier = tft.readID();
  Serial.print(F("LCD driver chip: "));
  Serial.println(identifier, HEX);  
  tft.begin(identifier);
  tft.setRotation(0);
  tft.fillScreen(BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(GREEN);
  tft.setTextSize(5);
  tft.println("Ready.");  

  tft.setTextSize(1);  
  but1 = buttons.addButton( 50, 50, 80,  30, "B1");
  but2 = buttons.addButton( 50,  90, 80,  30, "Button 2");
  but3 = buttons.addButton( 50, 130, 80,  30, "Button 3");  
  but4 = buttons.addButton( 50, 170, 80,  30, "Button 4", BUTTON_DISABLED);
  buttons.drawButtons();
  
}

void loop()
{
  int pressed_button = buttons.checkButtons();
  if ( pressed_button > -1 )
  {
      tft.setCursor(0, 0);
      tft.fillRect(0, 0, 240, 40, BLACK);
      tft.print("button ");
      tft.print(pressed_button);
      tft.println(" pressed.");        
  }
  
}
