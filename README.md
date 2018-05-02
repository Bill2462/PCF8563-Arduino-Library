# PCF8563-Arduino-Library
[![Build Status](https://travis-ci.org/Bill2462/PCF8563-Arduino-Library.svg?branch=master)](https://travis-ci.org/Bill2462/PCF8563-Arduino-Library)
[![GitHub release](https://img.shields.io/github/release/Bill2462/PCF8563-Arduino-Library.svg?maxAge=3600)](https://github.com/Bill2462/PCF8563-Arduino-Library/releases/latest)
[![License](https://img.shields.io/github/license/Bill2462/PCF8563-Arduino-Library.svg?maxAge=3600)](LICENSE)

Arduino Library for PCF8563 real time clock.

## API
PCF8563 class members : 

#### void init()
Initialise PCF8563. 

#### void stopClock()
Stop the clock. 

#### void startClock()
Start the clock. 

#### void setYear(uint8_t year)
Sets year.

Parameters: 
- uint8_t year - year (00 to 99) 

#### void setMonth(uint8_t month)
Sets month.

Parameters: 
- uint8_t year - year (00 to 99) 

#### void setDay(uint8_t day)
Sets day. 

Parameters: 
- uint8_t year - year (00 to 99) 

#### void setHour(uint8_t hour)
Sets hour. 

Parameters: 
- uint8_t year - year (00 to 99) 

#### void setMinut(uint8_t minut)
Sets minut.

Parameters: 
- uint8_t year - year (00 to 99) 

#### void setSecond(uint8_t second)
Sets second. 

Parameters: 
- uint8_t year - year (00 to 99) 

#### void enableClkOutput()
Enables square signal output pin. 

#### void disableClkOutput()
Disables square signal output pin. 

#### void setClkOutputFrequency(output_frequency frequency)
Sets output signal frequency. 

Parameters:
- output_frequency frequency - selected frequency 

Valid values :
 - `CLKOUT_32768_Hz` - 32768Hz
 - `CLKOUT_1024_Hz`  - 1024Hz
 - `CLKOUT_32_Hz`    - 32Hz
 - `CLKOUT_1_Hz`     - 1Hz

#### Time getTime()
Reads current time and returns it as a structure. 

Returns: Current time encoded inside Time structure. 

Time structure :

```
struct Time
{
  uint8_t year;     //year
  uint8_t month;    //month
  uint8_t day;      //day
  uint8_t weekday;  //weekday (1-7)
  uint8_t hour;     //hour
  uint8_t minute;   //minute
  uint8_t second;   //second
};
```

#### bool checkClockIntegrity()
Check clock integrity. 

Returns: true if clock is valid. If not returns false. 

