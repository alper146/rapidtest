// Touch screen library with X Y and Z (pressure) readings as well
// as oversampling to avoid 'bouncing'
// (c) ladyada / adafruit
// Code under MIT License

#include "pins_arduino.h"
#include "wiring_private.h"
#include <avr/pgmspace.h>
#include "SWTouch.h"

// increase or decrease the touchscreen oversampling. This is a little different than you make think:
// 1 is no oversampling, whatever data we get is immediately returned
// 2 is double-sampling and we only return valid data if both points are the same
// 3+ uses insert sort to get the median value.
// We found 2 is precise yet not too slow so we suggest sticking with it!

#define NUMSAMPLES 2

SWPoint::SWPoint(void) {
  x = y = 0;
}

SWPoint::SWPoint(int16_t x0, int16_t y0, int16_t z0) {
  x = x0;
  y = y0;
  z = z0;
}

bool SWPoint::operator==(SWPoint p1) {
  return  ((p1.x == x) && (p1.y == y) && (p1.z == z));
}

bool SWPoint::operator!=(SWPoint p1) {
  return  ((p1.x != x) || (p1.y != y) || (p1.z != z));
}

#if (NUMSAMPLES > 2)
static void insert_sort(int array[], uint8_t size) {
  uint8_t j;
  int save;
  
  for (int i = 1; i < size; i++) {
    save = array[i];
    for (j = i; j >= 1 && save < array[j - 1]; j--)
      array[j] = array[j - 1];
    array[j] = save; 
  }
}
#endif

SWPoint SWTouch::getPoint(void) {
  int x, y, z;
  int samples[NUMSAMPLES];
  uint8_t i, valid;
  

  uint8_t xp_port = digitalPinToPort(_xp);
  uint8_t yp_port = digitalPinToPort(_yp);
  uint8_t xm_port = digitalPinToPort(_xm);
  uint8_t ym_port = digitalPinToPort(_ym);

  uint8_t xp_pin = digitalPinToBitMask(_xp);
  uint8_t yp_pin = digitalPinToBitMask(_yp);
  uint8_t xm_pin = digitalPinToBitMask(_xm);
  uint8_t ym_pin = digitalPinToBitMask(_ym);


  valid = 1;

  pinMode(_yp, INPUT);
  pinMode(_ym, INPUT);
  
  *portOutputRegister(yp_port) &= ~yp_pin;
  *portOutputRegister(ym_port) &= ~ym_pin;
  //digitalWrite(_yp, LOW);
  //digitalWrite(_ym, LOW);
   
  pinMode(_xp, OUTPUT);
  pinMode(_xm, OUTPUT);
  //digitalWrite(_xp, HIGH);
  //digitalWrite(_xm, LOW);
  *portOutputRegister(xp_port) |= xp_pin;
  *portOutputRegister(xm_port) &= ~xm_pin;
   
   for (i=0; i<NUMSAMPLES; i++) {
     samples[i] = analogRead(_yp);
   }
#if NUMSAMPLES > 2
   insert_sort(samples, NUMSAMPLES);
#endif
#if NUMSAMPLES == 2
   if (samples[0] != samples[1]) { valid = 0; }
#endif
   x = (1023-samples[NUMSAMPLES/2]);

   pinMode(_xp, INPUT);
   pinMode(_xm, INPUT);
   *portOutputRegister(xp_port) &= ~xp_pin;
   //digitalWrite(_xp, LOW);
   
   pinMode(_yp, OUTPUT);
   *portOutputRegister(yp_port) |= yp_pin;
   //digitalWrite(_yp, HIGH);
   pinMode(_ym, OUTPUT);
  
   for (i=0; i<NUMSAMPLES; i++) {
     samples[i] = analogRead(_xm);
   }

#if NUMSAMPLES > 2
   insert_sort(samples, NUMSAMPLES);
#endif
#if NUMSAMPLES == 2
   if (samples[0] != samples[1]) { valid = 0; }
#endif

   y = (1023-samples[NUMSAMPLES/2]);

   // Set X+ to ground
   pinMode(_xp, OUTPUT);
   *portOutputRegister(xp_port) &= ~xp_pin;
   //digitalWrite(_xp, LOW);
  
   // Set Y- to VCC
   *portOutputRegister(ym_port) |= ym_pin;
   //digitalWrite(_ym, HIGH); 
  
   // Hi-Z X- and Y+
   *portOutputRegister(yp_port) &= ~yp_pin;
   //digitalWrite(_yp, LOW);
   pinMode(_yp, INPUT);
  
   int z1 = analogRead(_xm); 
   int z2 = analogRead(_yp);

   if (_rxplate != 0) {
     // now read the x 
     float rtouch;
     rtouch = z2;
     rtouch /= z1;
     rtouch -= 1;
     rtouch *= x;
     rtouch *= _rxplate;
     rtouch /= 1024;
     
     z = rtouch;
   } else {
     z = (1023-(z2-z1));
   }

   if (! valid) {
     z = 0;
   }

   return SWPoint(x, y, z);
}

SWTouch::SWTouch(SWTFT * _ptrSWTFT) 
{
  _swtft = _ptrSWTFT;
  _yp = YP;
  _xm = XM;
  _ym = YM;
  _xp = XP;
  _rxplate = 220;
  pressureThreshhold = 10;
}


SWTouch::SWTouch(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym) {
  _yp = yp;
  _xm = xm;
  _ym = ym;
  _xp = xp;
  _rxplate = 0;
  pressureThreshhold = 10;
}


SWTouch::SWTouch(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym,
			 uint16_t rxplate) {
  _yp = yp;
  _xm = xm;
  _ym = ym;
  _xp = xp;
  _rxplate = rxplate;

  pressureThreshhold = 10;
}
int16_t SWTouch::getX()
{
  return _point.x;
}

int16_t SWTouch::getY()
{
  return _point.y;
}

//==========================================
#define MINPRESSURE 10
#define MAXPRESSURE 1000
boolean SWTouch::touchAvailable()
{
  SWPoint p = getPoint();
  
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    /*
    Serial.print("X = "); Serial.print(p.x);
    Serial.print("\tY = "); Serial.print(p.y);
    Serial.print("\tPressure = "); Serial.println(p.z);
    */
    
    // scale from 0->1023 to tft.width
    p.x = (map(p.x, TS_MINX, TS_MAXX, 0, _swtft->height()));
    p.y = (map(p.y, TS_MINY, TS_MAXY, 0, _swtft->width()));
    int16_t tmp = p.x;
    p.x = _swtft->width() - p.y;
    p.y = _swtft->height() - tmp;
    /*
    Serial.print("("); Serial.print(p.x);
    Serial.print(", "); Serial.print(p.y);
    Serial.println(")");
    */
    _point = p;
    return true;
  }
  
  return false;
}
