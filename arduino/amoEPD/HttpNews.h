#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>

#define USE_SERIAL Serial

DynamicJsonDocument  docbuffer(2048);   //分配2k字节存储空间



int GetNews(const char **news_str)
{
  int i;
  HTTPClient http;
  String  errjson = "err_code";
  USE_SERIAL.print("[HTTP] begin...\n");
  http.begin("http://free-api.ledcfg.com/base/info/searchnews?sn=amobbs&mode=0"); //HTTP
  USE_SERIAL.print("[HTTP] GET...\n");
  // start connection and send HTTP header
  int httpCode = http.GET();
  // httpCode will be negative on error
  if (httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);
    // file found at server
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      USE_SERIAL.println(payload);
      DeserializationError error = deserializeJson(docbuffer, payload);   //反序列化json
      JsonObject root = docbuffer.as<JsonObject>();
      USE_SERIAL.printf("deserial ok \r\n");
      if (root != NULL)
      {
        USE_SERIAL.printf("root is ok \r\n");
        int error_code = root[errjson];
        USE_SERIAL.printf("root get err code is %d\r\n", error_code);
        if (error_code == 0)   //无错误 输出
        {
          i = root["result"].size();
          USE_SERIAL.printf("result size is%d\r\n", i);

          for (int j = 0; j < i; j++)
          {
            news_str[j] = root["result"][j];
            USE_SERIAL.printf("%s\r\n", news_str[j]);
          }
        }
      }
    }
  } else {
    USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());

  }

  http.end();

  return i;
}
