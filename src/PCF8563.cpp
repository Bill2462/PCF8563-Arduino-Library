#include "PCF8563.h"
#include "Arduino.h"

//initialize PCF8563
//Parameters: none
//Returns: none
void PCF8563::init()
{
  Wire.begin();//initialize the I2C interface
  write_AND(Control_status_1,~(1<<3));//clear TESTC bit
  write_AND(CLKOUT_control,~(1<<7));//clear CLKOUT enable bit
}

//Start the clock
//Parameters: None
//Returns:    None
void PCF8563::startClock()
{
  write_AND(Control_status_1,~(1<<5));
}

//Start the clock
//Parameters: None
//Returns:    None
void PCF8563::stopClock()
{
  write_OR(Control_status_1,1<<5);
}

//Set the year
//Parameters:
// * uint8_t year -> selected year (you can set values 0-99)
//Returns: None
void PCF8563::setYear(uint8_t year)
{
  const uint8_t data = ((get_second_number(year))<<4)|(get_first_number(year));
  write(Years,data);
}

//Set the month
//Parameters:
// * uint8_t month -> selected month (you can set values 1-12)
//Returns: None
void PCF8563::setMonth(uint8_t month)
{
  const uint8_t data = ((get_second_number(month))<<4)|(get_first_number(month));
  write(Century_months,data);
}

//Set the day
//Parameters:
// * uint8_t day -> selected day (you can set values 1-31)
//Returns: None
void PCF8563::setDay(uint8_t day)
{
  const uint8_t data = ((get_second_number(day))<<4)|(get_first_number(day));
  write(Days,data);
}

//Set the hour
//Parameters:
// *uint8_t hour -> selected day (you can set values 0-24)
//Returns: None
void PCF8563::setHour(uint8_t hour)
{
  const uint8_t data = ((get_second_number(hour))<<4)|(get_first_number(hour));
  write(Hours,data);
}

//Set the minut
//Parameters:
// *uint8_t minut -> selected day (you can set values 0-59)
//Returns:    None
void PCF8563::setMinut(uint8_t minut)
{
  const uint8_t data = ((get_second_number(minut))<<4)|(get_first_number(minut));
  write(Minutes,data);
}

//Set the second
//Parameters:
// * uint8_t second -> selected day (you can set values 0-59)
//Returns: None
void PCF8563::setSecond(uint8_t second)
{
  const uint8_t data = ((get_second_number(second))<<4)|(get_first_number(second));
  write(VL_seconds,data);
}

//Get current time
//Parameters: None
//Returns: Time (current code encoded into the Time structure)
Time PCF8563::getTime()
{
  Time output;

  //read data registers contents
  const uint8_t YEAR    = read(Years);
  const uint8_t MONTH   = read(Century_months);
  const uint8_t DAY     = read(Days);
  const uint8_t WEEKDAY = read(Weekdays);
  const uint8_t HOUR    = read(Hours);
  const uint8_t MINUTE  = read(Minutes);
  const uint8_t SECONDS = read(VL_seconds);

  //convert readed data to numbers using bcd_to_number function).
  output.year    = bcd_to_number((YEAR&0b11110000)>>4,YEAR&0b00001111);
  output.month   = bcd_to_number((MONTH&0b00010000)>>4,MONTH&0b00001111);
  output.day     = bcd_to_number((DAY&0b00110000)>>4,DAY&0b00001111);
  output.weekday = bcd_to_number(0,WEEKDAY&0b00000111);
  output.hour    = bcd_to_number((HOUR&0b00110000)>>4,HOUR&0b00001111);
  output.minute  = bcd_to_number((MINUTE&0b01110000)>>4,MINUTE&0b00001111);
  output.second  = bcd_to_number((SECONDS&0b01110000)>>4,SECONDS&0b00001111);

  return output;
}

//Check clock integrity
//Parameters: None
//Returns: clock status (bool)
bool PCF8563::checkClockIntegrity()
{
    const uint8_t data = read(VL_seconds);//read the data

    if(data & (1<<7))
    {
      return 0;//if clock integrity is not guaranteed return 0
    }

    else
    {
      return 1;//otherwise return 1
    }
}

//Enable CLK OUTPUT
//Parameters: None
//Returns: None
void PCF8563::enableClkOutput()
{
  write_OR(CLKOUT_control,1<<7);//set FE bit in CLKOUT_control register
}

//Disable CLK OUTPUT
//Parameters: None
//Returns: None
void PCF8563::disableClkOutput()
{
  write_AND(CLKOUT_control,~(1<<7));//clear FE bit in CLKOUT_control register
}

//Set CLK OUTPUT frequency
//Parameters:
// * output_frequency frequency -> Selected frequency
//Returns: None
void PCF8563::setClkOutputFrequency(output_frequency frequency)
{
  switch(frequency)
  {
    case CLKOUT_32768_Hz:
      write_AND(CLKOUT_control,~((1<<0)|(1<<1)));
      break;

    case CLKOUT_1024_Hz:
      write_AND(CLKOUT_control,~(1<<1));
      write_OR(CLKOUT_control,1<<0);
      break;

    case CLKOUT_32_Hz:
      write_AND(CLKOUT_control,~(1<<0));
      write_OR(CLKOUT_control,1<<1);
      break;

    case CLKOUT_1_Hz:
      write_OR(CLKOUT_control,(1<<0)|(1<<1));
      break;
  }
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

//Convert BCD format to number
//Parameters:
// * uint8_t first -> first digit
// * uint8_t second -> second digit
//Returns: the result of the conversion (unsigned char)
unsigned char PCF8563::bcd_to_number(uint8_t first, uint8_t second)
{
  unsigned char output;
  output = first*10;
  output = output + second;
  return output;
}

//Get first digit of the number
//Parameters:
// * unsigned short ->
//Returns: digit (uint8_t)
uint8_t PCF8563::get_first_number(unsigned short number)
{
  uint8_t output = number%10;
  return output;
}

//Get second digit of the number
//Parameters:
// * unsigned short ->
//Returns: digit (uint8_t)
uint8_t  PCF8563::get_second_number(unsigned short number)
{
  uint8_t output = number/10;
  return output;
}

//Write one byte of data
//Parameters:
// * uint8_t address  - register read_address
// * uint8_t data     - byte of data that we want to write to the register
//Returns: none
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
//Returns: none
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
//Returns: none
void PCF8563::write_AND(uint8_t address, uint8_t data)
{
  uint8_t c = read(address);
  c = c & data;
  write(address,c);
}
