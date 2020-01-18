/*
------------------------------------------------------------------------------
~ File   : ds1307.c
~ Author : Majid Derhambakhsh
~ Version: V0.0.0
~ Created: 01/17/2020 07:05:00 AM
~ Brief  :
~ Support: 
           E-Mail : Majid.Derhambakhsh@gmail.com (subject: Embedded Library Support)
		   
           Github : https://github.com/Majid-Derhambakhsh
------------------------------------------------------------------------------
~ Description:    Support DS1307 RTC Series Products With the I2C peripheral.
				  Support AVR - ARM (STM32) Microcontroller Series.

~ Attention  :    This module required [stm32_i2c - I2C_UNIT - form_converter] Driver Module. 

~ Changes    :
------------------------------------------------------------------------------
*/

#include "ds1307.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Enum ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

enum /* Array Bit vectors enum */
{
	
	_DS1307_ARR_SECONDS_VECT = 0,
	_DS1307_ARR_MINUTES_VECT = 1,
	_DS1307_ARR_HOURS_VECT   = 2
	
}DS1307_TimeArrayBitVect;

enum /* Array Bit vectors enum */
{
	
	_DS1307_ARR_DAY_VECT   = 0,
	_DS1307_ARR_DATE_VECT  = 1,
	_DS1307_ARR_MONTH_VECT = 2,
	_DS1307_ARR_YEAR_VECT  = 3
	
}DS1307_DateArrayBitVect;

enum /* Bit set enum */
{
	
	_DS1307_3_BIT_SET = 0x07,
	_DS1307_5_BIT_SET = 0x1F,
	_DS1307_6_BIT_SET = 0x3F,
	_DS1307_7_BIT_SET = 0x7F
	
}DS1307_DataBitSet;

enum /* Bit vectors enum */
{
	
	_DS1307_CH_BIT_VECT         = 7,
	_DS1307_PM_AM_BIT_VECT      = 5,
	_DS1307_CLOCK_MODE_BIT_VECT = 6,
	_DS1307_RS0_BIT_VECT        = 0,
	_DS1307_RS1_BIT_VECT        = 1,
	_DS1307_SQWE_BIT_VECT       = 4,
	_DS1307_OUT_BIT_VECT        = 7
	
}DS1307_ConfBitVect;

enum /* Registers address enum */
{
	
	_DS1307_SECONDS_REG_ADD = 0x00,
	_DS1307_MINUTES_REG_ADD = 0x01,
	_DS1307_HOURS_REG_ADD   = 0x02,
	_DS1307_DAY_REG_ADD     = 0x03,
	_DS1307_DATE_REG_ADD    = 0x04,
	_DS1307_MONTH_REG_ADD   = 0x05,
	_DS1307_YEAR_REG_ADD    = 0x06,
	_DS1307_CONTROL_REG_ADD = 0x07,
	_DS1307_RAM_REG_ADD     = 0x08,
	
}DS1307_RegisterAddress;

enum /* Register informations enum */
{
	
	_DS1307_NMB_OF_ALL_REG        = 8,
	_DS1307_NMB_OF_TIME_REGISTERS = 3,
	_DS1307_NMB_OF_DATE_REGISTERS = 4,
	_DS1307_NMB_OF_RAM_REGISTERS  = 56
	
}DS1307_RegisterInformation;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

uint8_t DS1307_DeviceIsReady(uint16_t _time_out)
{
	return _I2C_MEM_READY(_DS1307_DEV_ADD,_DS1307_TRIALS,_time_out); /* Check device */
}
/*
	Guide   :
			Function description	This function is used to check chip connectivity.
			
			Parameters
									* _time_out : Timeout duration.
									
			Return Values
									* _TRUE / _FALSE
			
	Example :
			uint8_t result;
			
			result = DS1307_DeviceIsReady(100);
			
			result is _TRUE/_FALSE
			
*/

uint8_t DS1307_SetTime(uint8_t _hour, uint8_t _minute, uint8_t _second, DS1307_MeridiemTypeDef _meridiem, uint16_t _time_out)
{
	/* ------------ Variable ------------- */
	uint8_t ds1307_com_status = _ERROR_VAL; /* Variable for take status */
	
	uint8_t ds1307_t[_DS1307_NMB_OF_TIME_REGISTERS];
	
	DS1307_ConfigTypeDef ds1307_cfg;
	
	/* ................................... */
	ds1307_com_status = DS1307_GetConfig(&ds1307_cfg,_time_out);
	
	/* ............ Copy data ............ */
	ds1307_t[_DS1307_ARR_SECONDS_VECT] = (FormConvert_DecimalToHexad(_second) & _DS1307_7_BIT_SET) | ((uint8_t)ds1307_cfg.OscillatorConfig << _DS1307_CH_BIT_VECT);
	ds1307_t[_DS1307_ARR_MINUTES_VECT] = (FormConvert_DecimalToHexad(_minute) & _DS1307_7_BIT_SET);
	
	if (ds1307_cfg.ClockMode == _DS1307_CLOCK_12H)
	{
		ds1307_t[_DS1307_ARR_HOURS_VECT] = ((uint8_t)ds1307_cfg.ClockMode << _DS1307_CLOCK_MODE_BIT_VECT) | ((uint8_t)_meridiem << _DS1307_PM_AM_BIT_VECT) | (FormConvert_DecimalToHexad(_hour) & _DS1307_5_BIT_SET);
	}
	else if (ds1307_cfg.ClockMode == _DS1307_CLOCK_24H)
	{
		ds1307_t[_DS1307_ARR_HOURS_VECT] = FormConvert_DecimalToHexad(_hour) & _DS1307_6_BIT_SET;
	}
	else{}
	
	/* ............ Copy data ............ */
	ds1307_com_status = _I2C_MEM_WRITE(_DS1307_DEV_ADD,_DS1307_SECONDS_REG_ADD,I2C_MEMADD_SIZE_8BIT,ds1307_t,_DS1307_NMB_OF_TIME_REGISTERS,_time_out); /* Write data */
	
	_DELAY_MS(_DS1307_NACCESSTIME); /* Delay for next access */
	
	return ds1307_com_status;
	
	/* Function End */
}
/*
	Guide   :
			Function description	This function is used to set time in RTC chip.
			
			Parameters
									* _hour     : Hour.
									* _minute   : Minute.
									* _second   : Second.
									* _meridiem : AM/PM.
									* _time_out : Timeout duration.
									
			Return Values
									* _OK_VAL / _ERROR_VAL
			
	Example :
			uint8_t result;
			
			result = DS1307_SetTime(12, 23, 47, _DS1307_PM, 100);
			
			result is _OK_VAL/_ERROR_VAL
			
*/

uint8_t DS1307_GetTime(uint8_t *_hour, uint8_t *_minute, uint8_t *_second, DS1307_MeridiemTypeDef *_meridiem, uint16_t _time_out)
{
	/* ------------ Variable ------------- */
	uint8_t ds1307_com_status = _ERROR_VAL; /* Variable for take status */
	
	uint8_t ds1307_t[_DS1307_NMB_OF_TIME_REGISTERS];
	
	DS1307_ConfigTypeDef ds1307_cfg;
	
	/* ................................... */
	ds1307_com_status = DS1307_GetConfig(&ds1307_cfg,_time_out);
	
	/* ............ Copy data ............ */
	ds1307_com_status = _I2C_MEM_READ(_DS1307_DEV_ADD,_DS1307_SECONDS_REG_ADD,I2C_MEMADD_SIZE_8BIT,ds1307_t,_DS1307_NMB_OF_TIME_REGISTERS,_time_out); /* Write data */
	
	*_second   = FormConvert_HexadToDecimal( (ds1307_t[_DS1307_ARR_SECONDS_VECT] & _DS1307_7_BIT_SET) );
	*_minute   = FormConvert_HexadToDecimal( (ds1307_t[_DS1307_ARR_MINUTES_VECT] & _DS1307_7_BIT_SET) );
	*_meridiem = (DS1307_MeridiemTypeDef)((ds1307_t[_DS1307_ARR_HOURS_VECT] >> _DS1307_PM_AM_BIT_VECT) & 1U);
	
	if (ds1307_cfg.ClockMode == _DS1307_CLOCK_12H)
	{
		*_hour = FormConvert_HexadToDecimal( (ds1307_t[_DS1307_ARR_HOURS_VECT] & _DS1307_5_BIT_SET) );
	}
	else if (ds1307_cfg.ClockMode == _DS1307_CLOCK_24H)
	{
		*_hour = FormConvert_HexadToDecimal( (ds1307_t[_DS1307_ARR_HOURS_VECT] & _DS1307_6_BIT_SET) );
	}
	else{}
	
	_DELAY_MS(_DS1307_NACCESSTIME); /* Delay for next access */
	
	return ds1307_com_status;
	
	/* Function End */
}
/*
	Guide   :
			Function description	This function is used to get time from RTC chip.
			
			Parameters
									* _hour     : Hour.
									* _minute   : Minute.
									* _second   : Second.
									* _meridiem : AM/PM.
									* _time_out : Timeout duration.
									
			Return Values
									* _OK_VAL / _ERROR_VAL
			
	Example :
			uint8_t result;
			
			uint8_t                clock_hour;
			uint8_t                clock_minute;
			uint8_t                clock_second;
			DS1307_MeridiemTypeDef clock_meridiem;
			
			result = DS1307_GetTime(&clock_hour, &clock_minute, &clock_second, &clock_meridiem, 100);
			
			clock_hour     value is 0~23 in 24 hour mode & 1~12 in 12 hour mode
			clock_minute   value is 0 to 59
			clock_second   value is 0 to 59
			clock_meridiem value is _DS1307_AM/_DS1307_PM
			
			result is _OK_VAL/_ERROR_VAL
			
*/

uint8_t DS1307_SetDate(uint8_t _year, uint8_t _month, uint8_t _day, uint8_t _weekday, uint16_t _time_out)
{
	/* ------------ Variable ------------- */
	uint8_t ds1307_com_status = _ERROR_VAL; /* Variable for take status */
	
	uint8_t ds1307_d[_DS1307_NMB_OF_DATE_REGISTERS];
	
	/* ................................... */
	ds1307_d[_DS1307_ARR_DAY_VECT]   = FormConvert_DecimalToHexad( (_weekday & _DS1307_3_BIT_SET) );
	ds1307_d[_DS1307_ARR_DATE_VECT]  = FormConvert_DecimalToHexad( (_day & _DS1307_6_BIT_SET) );
	ds1307_d[_DS1307_ARR_MONTH_VECT] = FormConvert_DecimalToHexad( (_month & _DS1307_5_BIT_SET) );
	ds1307_d[_DS1307_ARR_YEAR_VECT]  = FormConvert_DecimalToHexad(_year);
	
	/* ............ Copy data ............ */
	ds1307_com_status = _I2C_MEM_WRITE(_DS1307_DEV_ADD, _DS1307_DAY_REG_ADD, I2C_MEMADD_SIZE_8BIT, ds1307_d, _DS1307_NMB_OF_DATE_REGISTERS, _time_out); /* Write data */
	
	_DELAY_MS(_DS1307_NACCESSTIME); /* Delay for next access */
	
	return ds1307_com_status;
	
	/* Function End */
}
/*
	Guide   :
			Function description	This function is used to set date in RTC chip.
			
			Parameters
									* _year     : Year.
									* _month    : Month.
									* _day      : Day.
									* _weekday  : Weekday.
									* _time_out : Timeout duration.
									
			Return Values
									* _OK_VAL / _ERROR_VAL
			
	Example :
			uint8_t result;
			
			result = DS1307_SetDate(20, 1, 17, 0, 100);
			
			result is _OK_VAL/_ERROR_VAL
			
*/

uint8_t DS1307_GetDate(uint8_t *_year, uint8_t *_month, uint8_t *_day, uint8_t *_weekday, uint16_t _time_out)
{
	/* ------------ Variable ------------- */
	uint8_t ds1307_com_status = _ERROR_VAL; /* Variable for take status */
	
	uint8_t ds1307_d[_DS1307_NMB_OF_DATE_REGISTERS];
	
	/* ............ Read data ............ */
	ds1307_com_status = _I2C_MEM_READ(_DS1307_DEV_ADD, _DS1307_DAY_REG_ADD, I2C_MEMADD_SIZE_8BIT, ds1307_d, _DS1307_NMB_OF_DATE_REGISTERS, _time_out); /* Write data */
	
	/* ............ Copy data ............ */
	*_weekday   = FormConvert_HexadToDecimal(ds1307_d[_DS1307_ARR_DAY_VECT]);
	*_day  = FormConvert_HexadToDecimal(ds1307_d[_DS1307_ARR_DATE_VECT]);
	*_month = FormConvert_HexadToDecimal(ds1307_d[_DS1307_ARR_MONTH_VECT]);
	*_year  = FormConvert_HexadToDecimal(ds1307_d[_DS1307_ARR_YEAR_VECT]);
	
	_DELAY_MS(_DS1307_NACCESSTIME); /* Delay for next access */
	
	return ds1307_com_status;
	
	/* Function End */
}
/*
	Guide   :
			Function description	This function is used to get date from RTC chip.
			
			Parameters
									* _year     : Year.
									* _month    : Month.
									* _day      : Day.
									* _weekday  : Weekday.
									* _time_out : Timeout duration.
									
			Return Values
									* _OK_VAL / _ERROR_VAL
			
	Example :
			uint8_t result;
			
			uint8_t date_year;
			uint8_t date_month;
			uint8_t date_day;
			uint8_t date_weekday;
			
			result = DS1307_GetDate(&date_year, &date_month, &date_day, &date_weekday, 100);
			
			date_year    value is 0 to 99
			date_month   value is 1 to 12
			date_day     value is 1 to 31
			date_weekday value is 1 to 7
			
			result is _OK_VAL/_ERROR_VAL
			
*/

uint8_t DS1307_SaveInRam(uint32_t _ram_address, uint8_t *_ram_data , uint8_t _size , uint16_t _time_out)
{
	/* ------------ Variable ------------- */
	uint8_t ds1307_com_status = _ERROR_VAL; /* Variable for take status */
	
	/* ----------------------------------- */
	if ( _size > (_DS1307_NMB_OF_RAM_REGISTERS - _ram_address) )
	{
		ds1307_com_status = _DS1307_RAM_SIZE_ERROR;
	}
	{
		
		/* ............ Copy data ............ */
		ds1307_com_status = _I2C_MEM_WRITE(_DS1307_DEV_ADD, (_ram_address + _DS1307_RAM_REG_ADD), I2C_MEMADD_SIZE_8BIT, _ram_data, _size, _time_out); /* Write data */
		
		_DELAY_MS(_DS1307_NACCESSTIME); /* Delay for next access */
		
	}
	
	return ds1307_com_status;
	
	/* Function End */
}
/*
	Guide   :
			Function description	This function is used to write data in RAM of RTC chip.
			
			Parameters
									* _ram_address : Address of ram for write data.
									* _ram_data    : Pointer to data.
									* _size        : Amount of data to be write.
									* _time_out    : Timeout duration.
									
			Return Values
									* _OK_VAL / _ERROR_VAL / _DS1307_RAM_SIZE_ERROR
			
	Example :
			uint8_t result;
			
			uint8_t my_data[27] = "Hello I Am Microcontroller";
			
			result = DS1307_SaveInRam(5, my_data, 26, 100);
			
			result is _OK_VAL/_ERROR_VAL/_DS1307_RAM_SIZE_ERROR
			
*/

uint8_t DS1307_ReadFromRam(uint32_t _ram_address, uint8_t *_ram_data , uint8_t _size , uint16_t _time_out)
{
	/* ------------ Variable ------------- */
	uint8_t ds1307_com_status = _ERROR_VAL; /* Variable for take status */
	
	/* ----------------------------------- */
	if ( _size > (_DS1307_NMB_OF_RAM_REGISTERS - _ram_address) )
	{
		ds1307_com_status = _DS1307_RAM_SIZE_ERROR;
	}
	{
		
		/* ............ Copy data ............ */
		ds1307_com_status = _I2C_MEM_READ(_DS1307_DEV_ADD, (_ram_address + _DS1307_RAM_REG_ADD), I2C_MEMADD_SIZE_8BIT, _ram_data, _size, _time_out); /* Read data */
		
		_DELAY_MS(_DS1307_NACCESSTIME); /* Delay for next access */
		
	}
	
	return ds1307_com_status;
	
	/* Function End */
}
/*
	Guide   :
			Function description	This function is used to read data from RAM of RTC chip.
			
			Parameters
									* _ram_address : Address of ram for read data.
									* _ram_data    : Pointer for save data.
									* _size        : Amount of data to be read.
									* _time_out    : Timeout duration.
									
			Return Values
									* _OK_VAL / _ERROR_VAL / _DS1307_RAM_SIZE_ERROR
			
	Example :
			uint8_t result;
			
			uint8_t my_data[56];
			
			result = DS1307_ReadFromRam(0, my_data, 20, 100);
			
			result is _OK_VAL/_ERROR_VAL/_DS1307_RAM_SIZE_ERROR
			
*/

uint8_t DS1307_Config(DS1307_ConfigTypeDef *_rtc_conf, uint16_t _time_out)
{
	/* ------------ Variable ------------- */
	uint8_t ds1307_com_status = _ERROR_VAL; /* Variable for take status */
	
	/* Date variable */
	uint8_t ds1307_year  = 0;
	uint8_t ds1307_month = 0;
	uint8_t ds1307_date  = 0;
	uint8_t ds1307_day   = 0;
	
	/* ------------- */
	uint8_t ds1307_reg_values[_DS1307_NMB_OF_ALL_REG] = {0};
	
	/* ................................... */
	ds1307_com_status = DS1307_GetDate(&ds1307_year, &ds1307_month, &ds1307_date, &ds1307_day, 1000);
	
	/* ............ Copy data ............ */
	ds1307_reg_values[_DS1307_SECONDS_REG_ADD] = ((uint8_t)_rtc_conf->OscillatorConfig << _DS1307_CH_BIT_VECT);
	ds1307_reg_values[_DS1307_MINUTES_REG_ADD] = 0U;
	ds1307_reg_values[_DS1307_HOURS_REG_ADD]   = ((uint8_t)_rtc_conf->ClockMode << _DS1307_CLOCK_MODE_BIT_VECT);
	ds1307_reg_values[_DS1307_DAY_REG_ADD]     = FormConvert_DecimalToHexad(ds1307_day);
	ds1307_reg_values[_DS1307_DATE_REG_ADD]    = FormConvert_DecimalToHexad(ds1307_date);
	ds1307_reg_values[_DS1307_MONTH_REG_ADD]   = FormConvert_DecimalToHexad(ds1307_month);
	ds1307_reg_values[_DS1307_YEAR_REG_ADD]    = FormConvert_DecimalToHexad(ds1307_year);
	ds1307_reg_values[_DS1307_CONTROL_REG_ADD] = ((uint8_t)_rtc_conf->OutputControl << _DS1307_OUT_BIT_VECT) | ((uint8_t)_rtc_conf->SquareWaveConfig << _DS1307_SQWE_BIT_VECT) | (uint8_t)_rtc_conf->SquareWaveRate;
	
	ds1307_com_status = _I2C_MEM_WRITE(_DS1307_DEV_ADD, _DS1307_SECONDS_REG_ADD, I2C_MEMADD_SIZE_8BIT, ds1307_reg_values, _DS1307_NMB_OF_ALL_REG, _time_out); /* Write data */
	
	_DELAY_MS(_DS1307_NACCESSTIME); /* Delay for next access */
	
	return ds1307_com_status;
	
	/* Function End */
}
/*
	Guide   :
			Function description	This function is used to config RTC chip.
			
			Parameters
									* _rtc_conf : Pointer to a DS1307_ConfigTypeDef structure that contains
												  the configuration information for the specified chip properties.
												
									* _time_out : Timeout duration.
									
			Return Values
									* _OK_VAL / _ERROR_VAL
			
	Example :
			uint8_t result;
			
			DS1307_ConfigTypeDef rtc_cfg;
			
			rtc_cfg.ClockMode        = _DS1307_CLOCK_12H;
			rtc_cfg.OscillatorConfig = _DS1307_OSCILLATOR_ENABLE;
			rtc_cfg.OutputControl    = _DS1307_OUT_PIN_HIGH;
			rtc_cfg.SquareWaveConfig = _DS1307_SQW_DISABLE;
			rtc_cfg.SquareWaveRate   = _DS1307_SQW_8KHZ;
			
			result = DS1307_Config(&rtc_cfg, 1000);
			
			result is _OK_VAL/_ERROR_VAL
			
*/

uint8_t DS1307_GetConfig(DS1307_ConfigTypeDef *_rtc_conf, uint16_t _time_out)
{
	/* ------------ Variable ------------- */
	uint8_t ds1307_second  = 0;
	uint8_t ds1307_hour    = 0;
	uint8_t ds1307_control = 0;
	uint8_t ds1307_com_status  = _ERROR_VAL; /* Variable for take status */
	
	/* ............ Read data ............ */
	ds1307_com_status = _I2C_MEM_READ(_DS1307_DEV_ADD, _DS1307_SECONDS_REG_ADD, I2C_MEMADD_SIZE_8BIT, &ds1307_second, 1U, _time_out); /* Read data */
	ds1307_com_status = _I2C_MEM_READ(_DS1307_DEV_ADD, _DS1307_HOURS_REG_ADD, I2C_MEMADD_SIZE_8BIT, &ds1307_hour, 1U, _time_out); /* Read data */
	ds1307_com_status = _I2C_MEM_READ(_DS1307_DEV_ADD, _DS1307_CONTROL_REG_ADD, I2C_MEMADD_SIZE_8BIT, &ds1307_control, 1U, _time_out); /* Read data */
	
	/* ............ Copy data ............ */
	_rtc_conf->OscillatorConfig = (ds1307_second >> _DS1307_CH_BIT_VECT) & 1U;
	_rtc_conf->ClockMode        = (ds1307_hour >> _DS1307_CLOCK_MODE_BIT_VECT) & 1U;
	_rtc_conf->SquareWaveRate   = (ds1307_control & _DS1307_SQW_32KHZ);
	_rtc_conf->SquareWaveConfig = (ds1307_control >> _DS1307_SQWE_BIT_VECT) & 1U;
	_rtc_conf->OutputControl    = (ds1307_control >> _DS1307_OUT_BIT_VECT) & 1U;
	
	return ds1307_com_status;
	
	/* Function End */
}
/*
	Guide   :
			Function description	This function is used to get config of RTC chip.
			
			Parameters
									* _rtc_conf : Pointer to a DS1307_ConfigTypeDef structure that contains
												  the configuration information for the specified chip properties.
												
									* _time_out : Timeout duration.
									
			Return Values
									* _OK_VAL / _ERROR_VAL
			
	Example :
			uint8_t result;
			
			DS1307_ConfigTypeDef rtc_cfg;
			
			result = DS1307_Config(&rtc_cfg, 1000);
			
			result is _OK_VAL/_ERROR_VAL
			
*/

