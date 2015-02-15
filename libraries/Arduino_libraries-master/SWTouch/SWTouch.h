// Touch screen library with X Y and Z (pressure) readings as well
// as oversampling to avoid 'bouncing'
// (c) ladyada / adafruit
// Code under MIT License

#ifndef SWTOUCH_H_
#define SWTOUCH_H_
#include <stdint.h>
#include <SWTFT.h>

#define YP A1  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 6   // can be a digital pin

#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

class SWPoint {
 public:
  SWPoint();
  SWPoint(int16_t x, int16_t y, int16_t z);
  
  bool operator==(SWPoint);
  bool operator!=(SWPoint);

  int16_t x, y, z;
};

class SWTouch {
 public:
  SWTouch(SWTFT * _ptrSWTFT);
  SWTouch(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym);
  SWTouch(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym, uint16_t rx);

  SWPoint getPoint();
  int16_t pressureThreshhold;
  boolean touchAvailable();
  int16_t getX();
  int16_t getY();
private:
  uint8_t _yp, _ym, _xm, _xp;
  uint16_t _rxplate;
  SWPoint _point;
  SWTFT * _swtft;
};

#endif
