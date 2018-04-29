#ifndef PCF8563_H
#define PCF8563_H

#include <Arduino.h>
#include <Wire.h>

//now time structure
struct Time
{
  uint8_t year;
  uint8_t month;
  uint8_t day;
  uint8_t weekday;
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
};

//output frequency
enum output_frequency
{
  CLKOUT_32768_Hz,
  CLKOUT_1024_Hz,
  CLKOUT_32_Hz,
  CLKOUT_1_Hz,
};

class PCF8563
{
public:

  //general control
  void init();//initialize the chip
  void stopClock();//stop the clock
  void startClock();//start the clock

  //time settings functions
  void setYear(uint8_t year);//set year
  void setMonth(uint8_t month);//set month
  void setDay(uint8_t day);//set day
  void setHour(uint8_t hour);//set hour
  void setMinut(uint8_t minut);//set minut
  void setSecond(uint8_t second);//set second

  //clkout output
  void enableClkOutput();//enable CLK output
  void disableClkOutput();//disable CLK output
  void setClkOutputFrequency(output_frequency frequency);//set CLK output frequency

  //time reading functions
  Time getTime();//get time
  bool checkClockIntegrity();//check clock integrity

private:
  uint8_t read(uint8_t address);//read one byte from selected register
  void write(uint8_t address, uint8_t data);//write one byte of data to the register
  void write_OR(uint8_t address, uint8_t data);//write data to the register using OR operations
  void write_AND(uint8_t address, uint8_t data);//write data to the register using AND operation
  unsigned char bcd_to_number(uint8_t first, uint8_t second);//convert two digits to one number
  uint8_t get_first_number(unsigned short number);//get ten’s place digit of the number
  uint8_t get_second_number(unsigned short number);//get unit place digit of the number

  //registers map
  enum registers
  {
    PCF8563_address  = 0x51,
    Control_status_1 = 0x00,
    Control_status_2 = 0x01,
    VL_seconds       = 0x02,
    Minutes          = 0x03,
    Hours            = 0x04,
    Days             = 0x05,
    Weekdays         = 0x06,
    Century_months   = 0x07,
    Years            = 0x08,
    Minute_alarm     = 0x09,
    Hour_alarm       = 0x0A,
    Day_alarm        = 0x0B,
    Weekday_alarm    = 0x0C,
    CLKOUT_control   = 0x0D,
    Timer_control    = 0x0E,
    Timer            = 0x0F,
  };
};
#endif
