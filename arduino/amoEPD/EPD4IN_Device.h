#ifndef _EPD4IN_DEVICE_H_
#define _EPD4IN_DEVICE_H_

#include <string.h>
#include <Wire.h>
#include <Arduino.h>

#include <SPI.h>
//
//
//uint8_t IIC_Device_Dected(uint8_t *device_id);
//

class EPD4IN_Device {


  public :
    uint8_t IIC_Device_Dected(uint8_t *device_id);      //读取设备的I2C总线设备



};

#endif;
