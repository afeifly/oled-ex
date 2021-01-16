#include <I2C_BM8563.h>
#include <SPIFFS.h>
#include "EPD4IN_Device.h"
#include "PIC.H"
#include "HttpNews.h"
#include <WiFi.h>
#include <WiFiMulti.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include "SHTSensor.h"
#include "SPIFFS.h"
#include "EPD4IN_driver.h"


EPD4INC epd_drv;
uint8_t deviceid[8];
uint8_t devicenum;
I2C_BM8563 rtc(I2C_BM8563_DEFAULT_ADDRESS, Wire1);
SHTSensor sht;
WiFiMulti wifiMulti;
const char *news_data[50]; //50个新闻最大
struct pl_area;
struct pl_area user_area;
void setup() {
  Wire.begin();
  SPIFFS.begin();
  rtc.begin();


  // Set RTC Date
  I2C_BM8563_DateTypeDef dateStruct;
  dateStruct.weekDay = 3;
  dateStruct.month = 3;
  dateStruct.date = 22;
  dateStruct.year = 2019;
  rtc.setDate(&dateStruct);

  // Set RTC Time
  I2C_BM8563_TimeTypeDef timeStruct;
  timeStruct.hours   = 18;
  timeStruct.minutes = 56;
  timeStruct.seconds = 10;
  rtc.setTime(&timeStruct);


  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("\nSystem Start up");
  delay(1000);
  if (sht.init()) {
    Serial.print("init(): success\n");
  } else {
    Serial.print("init(): failed\n");
  }
  sht.setAccuracy(SHTSensor::SHT_ACCURACY_MEDIUM); // only supported by SHT3x


  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }
  wifiMulti.addAP("TP-LINK_CE96", "abcd12345bb");

  if ((wifiMulti.run() == WL_CONNECTED)) {
  }
  delay(1000);

}

char buff[128];
int i = 0, j;
char testout[100];
unsigned long testreturn;
void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Init Port");
  epd_drv.EPD4INC_Port_init();
  epd_drv.EPD_CLK_EX();
  Serial.println("Epd Power Up");
  epd_drv.EPD4INC_Power_up();
  delay(100);
  epd_drv.s1d135xx_soft_reset();
  delay(100);


  epd_drv.EPD4INC_Power_up();
  delay(1000);


  Serial.println("Epd init");
  epd_drv.epson_epdc_init();
  delay(100);
  epd_drv.s1d135xx_set_epd_power(1);
  delay(100);

  epd_drv.Buf_Clear();
  epd_drv.Buf_DrawLine(0, 0, 120, 200);
  epd_drv.Buf_DrawLine(120, 200, 0, 399);

  epd_drv.Buf_Buf_DrawXline(20, 40, 100);
  epd_drv.Buf_UpdateFull(1);
  epd_drv.Buf_Buf_DrawYline(20, 40, 100);
  epd_drv.Buf_UpdateFull(1);
  epd_drv.Buf_Clear();
  epd_drv.Buf_DrawBox(30, 30, 15, 80);
  epd_drv.Buf_DrawEmptyBox(80, 80, 20, 60);
  epd_drv.Buf_DrawCircle(200, 120, 15, 1);
  for (i = 0; i < 39; i++)
  {
    epd_drv.Buf_InverseArea(i * 10, (i + 1) * 10, 200, 210);

    epd_drv.Buf_UpdateFull(2);
  }


  epd_drv.Buf_UpdateFull(1);
  delay(5000);


  //刷新背景
  epd_drv.EPD_Update_Full(12000, S1D13541_LD_IMG_1BPP, rt_news_background);
  epd_drv.EPD_UpdateUser(1, UPDATE_FULL, NULL);
  delay(2000);
  epd_drv.EPD4INC_Power_Sleep();
  delay(5000);
  epd_drv.EPD4INC_Power_wakeup();
  delay(20);

  user_area.top = 00;
  user_area.left = 0;
  user_area.width = 400;
  user_area.height = 240;


  epd_drv.EPD_Fill_White(&user_area, 1);

  sprintf(buff, "Checked I2C device is %d ", devicenum);
  epd_drv.EPD_SetFount(FONT12);
  epd_drv.DrawUTF( 80 , 80, buff, 1);

  epd_drv.EPD_UpdateUser(1, UPDATE_FULL, NULL);
  delay(2000);

  user_area.top = 80;
  user_area.left = 80;
  user_area.width = 32 * 5;
  user_area.height = 64;


  for (i = 0; i < 10; i++)
  {
    I2C_BM8563_DateTypeDef dateStruct;
    I2C_BM8563_TimeTypeDef timeStruct;

    // Get RTC
    rtc.getDate(&dateStruct);
    rtc.getTime(&timeStruct);


    epd_drv.DrawTime(80, 80, timeStruct.hours, timeStruct.seconds, FONT64_NUM, 1);
    epd_drv.EPD_UpdateUser(2, UPDATE_PARTIAL_AREA, &user_area);
    delay(10);
  }



  if (sht.readSample()) {
    Serial.print("SHT:\n");
    Serial.print("  RH: ");
    Serial.print(sht.getHumidity(), 2);
    Serial.print("\n");
    Serial.print("  T:  ");
    Serial.print(sht.getTemperature(), 2);
    Serial.print("\n");
    sprintf(buff, "湿度%.2fRH,温度=%.2f度", sht.getHumidity(), sht.getTemperature());
    user_area.top = 0;
    user_area.left = 0;

    user_area.height = 16;
    epd_drv.EPD_SetFount(FONT12);
    epd_drv.DrawUTF( user_area.left , user_area.top, buff, 1);

    Serial.printf("字符数量 %d width %d", i, user_area.width);

    epd_drv.pl_epdc_single_update(2, UPDATE_PARTIAL_AREA, &user_area);
  }

  user_area.top = 80;
  user_area.left = 80;
  user_area.width = 16;
  user_area.height = 16;
  epd_drv.EPD_SetFount(FONT16);
  j = 0;
  while (1) {
    j++;



    if ((wifiMulti.run() == WL_CONNECTED)) {
      int newstimes = GetNews(news_data);
      if (newstimes > 12)
      {
        epd_drv.EPD_SetFount(FONT12);
        if (sht.readSample()) {

          sprintf(buff, "湿度%.2fRH,温度=%.2f度", sht.getHumidity(), sht.getTemperature());
          user_area.top = 0;
          user_area.left = 0;
          user_area.height = 16;
          epd_drv.DrawUTF(0, 0, buff, 1);

          epd_drv.pl_epdc_single_update(1, UPDATE_PARTIAL_AREA, &user_area);
          delay(500);
        }
        epd_drv.EPD_SetFount(FONT16);
        user_area.top = 00;
        user_area.left = 0;
        user_area.width = 400;
        user_area.height = 240;
        epd_drv.EPD_Fill_White(&user_area, 1);

        user_area.top = 40;
        user_area.left = 0;
        user_area.width = 400;
        user_area.height = 200;


        epd_drv.EPD_Fill_White(&user_area, 1);
        for (int newst = 0; newst < 12; newst++)
        {
          Serial.println(news_data[newst]);
          epd_drv.DrawUTF(5, 40 + newst * 16, news_data[newst], 1);

        }

        epd_drv.EPD_UpdateUser(2, UPDATE_PARTIAL_AREA, &user_area);
        delay(1000);
        epd_drv.EPD_Fill_White(&user_area, 1);
        epd_drv.EPD_SetFount(FONT12);
        for (int newst = 0; newst < 12; newst++)
        {

          Serial.println(news_data[newst + 12]);

          epd_drv.DrawUTF(5, 40 + newst * 16, news_data[newst + 12], 1);


        }
        epd_drv.EPD_UpdateUser(2, UPDATE_PARTIAL_AREA, &user_area);

        delay(1000);
        if (j == 5) {

          j = 0;
          epd_drv.EPD_Fill_White(&user_area, 1);
          epd_drv.EPD_UpdateUser(1, UPDATE_PARTIAL_AREA, &user_area);
          delay(1000);

        }


      }

    }

  }

  Serial.println("test over i= ");

  Serial.println(i);

  while (1) {


  }

}
