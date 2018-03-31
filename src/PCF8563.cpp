#include "PCF8563.h"
#include "Arduino.h"

//initialize PCF8563
void PCF8563::init()
{
  Wire.begin();//initialize the I2C interface
  write_AND(Control_status_1,~(1<<3));//clear TESTC bit
  write_AND(CLKOUT_control,~(1<<7));//clear CLKOUT enable bit
}

void PCF8563::startClock()
{
  write_AND(Control_status_1,~(1<<5));
}

void PCF8563::stopClock()
{
  write_OR(Control_status_1,1<<5);
}

void PCF8563::setYear(uint8_t year)
{
  const uint8_t data = ((get_second_number(year))<<4)|(get_first_number(year));
  write(Years,data);
}

void PCF8563::setMonth(uint8_t month)
{
  const uint8_t data = ((get_second_number(month))<<4)|(get_first_number(month));
  write(Century_months,data);
}
void PCF8563::setDay(uint8_t day)
{
  const uint8_t data = ((get_second_number(day))<<4)|(get_first_number(day));
  write(Days,data);
}

void PCF8563::setHour(uint8_t hour)
{
  const uint8_t data = ((get_second_number(hour))<<4)|(get_first_number(hour));
  write(Hours,data);
}

void PCF8563::setMinut(uint8_t minut)
{
  const uint8_t data = ((get_second_number(minut))<<4)|(get_first_number(minut));
  write(Minutes,data);
}

void PCF8563::setSecond(uint8_t second)
{
  const uint8_t data = ((get_second_number(second))<<4)|(get_first_number(second));
  write(VL_seconds,data);
}

Time PCF8563::getTime()
{
  Time output;

  const uint8_t YEAR    = read(Years);
  const uint8_t MONTH   = read(Century_months);
  const uint8_t DAY     = read(Days);
  const uint8_t WEEKDAY = read(Weekdays);
  const uint8_t HOUR    = read(Hours);
  const uint8_t MINUTE  = read(Minutes);
  const uint8_t SECONDS = read(VL_seconds);

  output.year    = bcd_to_number((YEAR&0b11110000)>>4,YEAR&0b00001111);
  output.month   = bcd_to_number((MONTH&0b00010000)>>4,MONTH&0b00001111);
  output.day     = bcd_to_number((DAY&0b00110000)>>4,DAY&0b00001111);
  output.weekday = bcd_to_number(0,WEEKDAY&0b00000111);
  output.hour    = bcd_to_number((HOUR&0b00110000)>>4,HOUR&0b00001111);
  output.minute  = bcd_to_number((MINUTE&0b01110000)>>4,MINUTE&0b00001111);
  output.second  = bcd_to_number((SECONDS&0b01110000)>>4,SECONDS&0b00001111);

  return output;
}

//Read one byte of data
//Parameters:
// * uint8_t address  - register read_address
//Returns: readed byte of data (uint8_t)
uint8_t PCF8563::read(uint8_t address)
{
  Wire.beginTransmission(PCF8563_address);//begin transmission
  Wire.write(address);//inform chip what register we want to read
  Wire.endTransmission();
  Wire.requestFrom(PCF8563_address,1);//request one byte from the chip
  uint8_t data = Wire.read();//read the data
  return data;
}

unsigned char PCF8563::bcd_to_number(uint8_t first, uint8_t second)
{
  unsigned char output;
  output = first*10;
  output = output + second;
  return output;
}

uint8_t PCF8563::get_first_number(unsigned short number)
{
  uint8_t output = number%10;
  return output;
}

uint8_t  PCF8563::get_second_number(unsigned short number)
{
  uint8_t output = number/10;
  return output;
}

//Write one byte of data
//Parameters:
// * uint8_t address  - register read_address
// * uint8_t data     - byte of data that we want to write to the register
void PCF8563::write(uint8_t address, uint8_t data)
{
  Wire.beginTransmission(PCF8563_address);
  Wire.write(address);
  Wire.write(data);
  Wire.endTransmission();
}

//Change state of the register using OR operation
//Parameters:
// * uint8_t address    - register address
// * uint8_t data       - one byte of data that we want to put in the register
void PCF8563::write_OR(uint8_t address, uint8_t data)
{
  uint8_t c = read(address);
  c = c | data;
  write(address,c);
}

//Change state of the register using AND operation
//Parameters:
// * uint8_t address    - register address
// * uint8_t data       - one byte of data that we want to put in the register
void PCF8563::write_AND(uint8_t address, uint8_t data)
{
  uint8_t c = read(address);
  c = c & data;
  write(address,c);
}
