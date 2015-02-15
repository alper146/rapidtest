#include <SoftI2CMaster.h>

const byte sdaPin = 7;  // digital pin 7 wired to 'd' on BlinkM
const byte sclPin = 6;  // digital pin 6 wired to 'c' on BlinkM

#define disk1 0x50
SoftI2CMaster i2c = SoftI2CMaster( sdaPin,sclPin );

asdasd

//
void setup()
{
  Serial.begin( 9600);
 
writeEEPROM(disk1,300,5);

  
}

void loop()
{ 
 
 

  char a;
   a=readEEPROM(disk1, 0);
   Serial.println(a);
  
  
}
void writeEEPROM(int deviceaddress,  int eeaddress, byte data ) 
{
  i2c.beginTransmission(deviceaddress);
  i2c.send((int)(eeaddress >> 8));   // MSB
  i2c.send((int)(eeaddress & 0xFF)); // LSB
  i2c.send(data);
  i2c.endTransmission();
 
  
}
 
byte readEEPROM(int deviceaddress,  int eeaddress ) 
{
  byte rdata = 0xFF;
 
  i2c.beginTransmission(deviceaddress);
  i2c.send((int)(eeaddress >> 8));   // MSB
  i2c.send((int)(eeaddress & 0xFF)); // LSB
  i2c.endTransmission();
 
  i2c.requestFrom(deviceaddress);
  rdata=i2c.receive();
 return rdata;
 
}
