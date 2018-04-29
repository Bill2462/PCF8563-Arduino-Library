#include <PCF8563.h>

PCF8563 pcf;

void setup() {
  Serial.begin(9600);
  pcf.init();//initialise PCF8563
  pcf.enableClkOutput();//enable CLKOUT pin
}

void loop() {
    //set output frequency to 32768 Hz
    Serial.println("Outputing 32768Hz");
    pcf.setClkOutputFrequency(CLKOUT_32768_Hz);
    delay(10000);

    //set output frequency to 1024 Hz
    Serial.println("Outputing 1024_Hz");
    pcf.setClkOutputFrequency(CLKOUT_1024_Hz);
    delay(10000);

    //set output frequency to 32Hz
    Serial.println("Outputing 32Hz");
    pcf.setClkOutputFrequency(CLKOUT_32_Hz);
    delay(10000);

    //set output frequency to 1Hz
    Serial.println("Outputing 1Hz");
    pcf.setClkOutputFrequency(CLKOUT_1_Hz);
 
}
