

#include "EPD4INCH.H"
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("\nSystem Start up");
}

void loop() {
  // put your main code here, to run repeatedly:
   Serial.println("Init Port");
  Epd_Port_init(0);
  Serial.println("Epd Power Up");
  Epd_Power_up();
  delay(100);
  s1d135xx_soft_reset();
  delay(100);
 
  
  Epd_Power_up();
  delay(1000);
 
 
  Serial.println("Epd init");   
  epson_epdc_init();
      delay(100);
  s1d135xx_set_epd_power(1);
    delay(100);
  s1d13541_pattern_check(20);
    delay(100);
  pl_epdc_single_update(1, UPDATE_FULL, NULL); 
  while(1){
     
  delay(1000);    
    }

}
