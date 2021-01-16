#include "EPD4IN_Device.h"
//
//
//
uint8_t EPD4IN_Device:: IIC_Device_Dected(uint8_t *device_id)
{
  Serial.println ("I2C scanner. Scanning ...");
  uint8_t count = 0;
  Wire.begin();
  for (uint8_t i = 8; i < 120; i++) {
    Wire.beginTransmission (i);
    if (Wire.endTransmission () == 0) {
      Serial.print ("Found address: ");
      device_id[count] = i;
      Serial.print (i, DEC);
      Serial.print (" (0x");
      Serial.print (i, HEX);
      Serial.println (")");
      count++;
      delay (1); // maybe unneeded?
    } // end of good response
  } // end of for loop


  return count;
}
