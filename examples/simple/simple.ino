#include <PCF8563.h>

PCF8563 pcf;

void setup() {
  Serial.begin(9600);
  pcf.init();//initialize the clock

  pcf.stopClock();//stop the clock

  //set time to to 31/3/2018 17:33:0

  pcf.setYear(18);//set year
  pcf.setMonth(3);//set month
  pcf.setDay(31);//set dat
  pcf.setHour(17);//set hour
  pcf.setMinut(33);//set minut
  pcf.setSecond(0);//set second

  pcf.startClock();//start the clock
}

void loop() {
  Time nowTime = pcf.getTime();//get current time

  //print current time
  Serial.print(nowTime.day);
  Serial.print("/");
  Serial.print(nowTime.month);
  Serial.print("/");
  Serial.print(nowTime.year);
  Serial.print(" ");
  Serial.print(nowTime.hour);
  Serial.print(":");
  Serial.print(nowTime.minute);
  Serial.print(":");
  Serial.println(nowTime.second);
  delay(1000);
}
