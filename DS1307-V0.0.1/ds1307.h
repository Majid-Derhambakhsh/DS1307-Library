/*
------------------------------------------------------------------------------
~ File   : ds1307.h
~ Author : Majid Derhambakhsh
~ Version: V0.0.1
~ Created: 07/12/2021 03:00:00 PM
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

#ifndef __DS1307_H_
#define __DS1307_H_

/* ------------------------------------------------ Includes ------------------------------------------------- */

#include <stdint.h> /* Import standard integer lib */
#include "ds1307_conf.h" /* Import config file */

#ifndef __FORM_CONVERTER_H_
#include "FORM_CONVERTER/form_converter.h"
#endif /* __FORM_CONVERTER_H_ */

/* ------------------------------------------------------------------ */

#ifdef __CODEVISIONAVR__  /* Check compiler */

#pragma warn_unref_func- /* Disable 'unused function' warning */

#ifndef __I2C_UNIT_H_
#include "I2C_UNIT/i2c_unit.h" /* Import i2c lib */
#endif /* __I2C_UNIT_H_ */

#include <delay.h>       /* Import delay library */

/* ------------------------------------------------------------------ */

#elif defined(__GNUC__) && !defined(USE_HAL_DRIVER)  /* Check compiler */

#pragma GCC diagnostic ignored "-Wunused-function" /* Disable 'unused function' warning */

#ifndef __I2C_UNIT_H_
#include "I2C_UNIT/i2c_unit.h" /* Import i2c lib */
#endif /* __I2C_UNIT_H_ */

#include <util/delay.h>  /* Import delay library */

/* ------------------------------------------------------------------ */

#elif defined(USE_HAL_DRIVER)  /* Check driver */

	/* ------------------------------------------------------- */

	#if defined ( __ICCARM__ ) /* ICCARM Compiler */

		#pragma diag_suppress=Pe177   /* Disable 'unused function' warning */

	#elif defined   (  __GNUC__  ) /* GNU Compiler */

		#pragma diag_suppress 177     /* Disable 'unused function' warning */

	#endif /* __ICCARM__ */

	/* ------------------------------------------------------- */

#ifndef __STM32_I2C_H_
#include "STM32_I2C/stm32_i2c.h" /* Import i2c lib */
#endif /* __STM32_I2C_H_ */

/* ------------------------------------------------------------------ */

#else                     /* Compiler not found */

#error Chip or I2C Library not supported  /* Send error */

#endif /* __CODEVISIONAVR__ */

/* ------------------------------------------------------------------ */

/* ------------------------------------------------- Defines ------------------------------------------------- */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ DS1307 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define _DS1307_NACCESSTIME 1U

/* Register informations */
#define _DS1307_DEV_ADD 0xD0

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~ Error & Warning ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define _DS1307_RAM_SIZE_ERROR 3U

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Public ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define _DS1307_TRIALS  10U /* Number of test */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ By compiler ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#ifdef __CODEVISIONAVR__  /* Check compiler */

#ifndef _ERROR_VAL
#define _ERROR_VAL             _STAT_ERROR             /* OK status value */
#endif

#ifndef _OK_VAL
#define _OK_VAL                _STAT_OK                /* OK status value */
#endif

#define I2C_MEMADD_SIZE_8BIT   _I2C_MEMADD_SIZE_8BIT   /* Memory Address Size */

#define _I2C_MEM_READY(da,tr,tim)            I2C_IsDeviceReady((da),(tr),(tim)) /* Change function */
#define _I2C_MEM_WRITE(da,ma,mas,md,qu,tim)  I2C_Mem_Write((da),(ma),(mas),(md),(qu),(tim)) /* Change function */
#define _I2C_MEM_READ(da,ma,mas,md,qu,tim)   I2C_Mem_Read((da),(ma),(mas),(md),(qu),(tim)) /* Change function */

#ifndef _DELAY_MS
	#define _DELAY_MS(t)                     delay_ms((t)) /* Change function */
#endif /* _DELAY_MS */

/* ------------------------------------------------------------------ */

#elif defined(__GNUC__) && !defined(USE_HAL_DRIVER)  /* Check compiler */

#ifndef _ERROR_VAL
#define _ERROR_VAL             _STAT_ERROR             /* OK status value */
#endif

#ifndef _OK_VAL
#define _OK_VAL                _STAT_OK                /* OK status value */
#endif

#define I2C_MEMADD_SIZE_8BIT   _I2C_MEMADD_SIZE_8BIT   /* Memory Address Size */

#define _I2C_MEM_READY(da,tr,tim)            I2C_IsDeviceReady((da),(tr),(tim)) /* Change function */
#define _I2C_MEM_WRITE(da,ma,mas,md,qu,tim)  I2C_Mem_Write((da),(ma),(mas),(md),(qu),(tim)) /* Change function */
#define _I2C_MEM_READ(da,ma,mas,md,qu,tim)   I2C_Mem_Read((da),(ma),(mas),(md),(qu),(tim)) /* Change function */

#ifndef _DELAY_MS
	#define _DELAY_MS(t)                     _delay_ms((t)) /* Change function */
#endif /* _DELAY_MS */

/* ------------------------------------------------------------------ */

#elif defined(USE_HAL_DRIVER)  /* Check driver */

#ifndef _ERROR_VAL
#define _ERROR_VAL    HAL_ERROR             /* OK status value */
#endif

#ifndef _OK_VAL
#define _OK_VAL       HAL_OK                /* OK status value */
#endif

#define _I2C_MEM_READY(da,tr,tim)            HAL_I2C_IsDeviceReady(&_CONNECTED_I2C,(da),(tr),(tim)) /* Change function */
#define _I2C_MEM_WRITE(da,ma,mas,md,qu,tim)  HAL_I2C_Mem_Write2(&_CONNECTED_I2C,(da),(ma),(mas),(md),(qu),(tim)) /* Change function */
#define _I2C_MEM_READ(da,ma,mas,md,qu,tim)   HAL_I2C_Mem_Read2(&_CONNECTED_I2C,(da),(ma),(mas),(md),(qu),(tim)) /* Change function */

#ifndef _DELAY_MS
	#define _DELAY_MS(t)                     HAL_Delay((t)) /* Change function */
#endif /* _DELAY_MS */

/* ------------------------------------------------------------------ */

#else 
#endif /* __CODEVISIONAVR__ */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* -------------------------------------------------- Enum --------------------------------------------------- */

typedef enum /* Oscillator Modes */
{
	
	_DS1307_OSCILLATOR_ENABLE  = 0,
	_DS1307_OSCILLATOR_DISABLE = 1
	
}DS1307_OscillatorConfigTypeDef;

typedef enum /* AM/PM */
{
	
	_DS1307_AM = 0,
	_DS1307_PM = 1
	
}DS1307_MeridiemTypeDef;

typedef enum /* Clock Modes */
{
	
	_DS1307_CLOCK_24H = 0,
	_DS1307_CLOCK_12H = 1
	
}DS1307_ClockModeTypeDef;

typedef enum /* Square Wave Modes */
{
	
	_DS1307_SQW_DISABLE = 0,
	_DS1307_SQW_ENABLE  = 1
	
}DS1307_SQWConfigTypeDef;

typedef enum /* Square Ware Rate */
{
	
	_DS1307_SQW_1HZ   = 0,
	_DS1307_SQW_4KHZ  = 1,
	_DS1307_SQW_8KHZ  = 2,
	_DS1307_SQW_32KHZ = 3
	
}DS1307_SQWRateTypeDef;

typedef enum /* Output pin states */
{
	
	_DS1307_OUT_PIN_LOW  = 0,
	_DS1307_OUT_PIN_HIGH = 1
	
}DS1307_OutputControlTypeDef;

typedef struct /* structure that contains the configuration information for the specified chip properties. */
{
	
	DS1307_OscillatorConfigTypeDef OscillatorConfig : 1;
	DS1307_ClockModeTypeDef        ClockMode        : 1;
	DS1307_SQWConfigTypeDef        SquareWaveConfig : 1;
	DS1307_SQWRateTypeDef          SquareWaveRate   : 2;
	DS1307_OutputControlTypeDef    OutputControl    : 1;
	
}DS1307_ConfigTypeDef;

/* ------------------------------------------------- Struct -------------------------------------------------- */

/* ............ By HAL DRIVER ............ */

#ifdef USE_HAL_DRIVER

extern I2C_HandleTypeDef _CONNECTED_I2C;

#endif /* USE_HAL_DRIVER */

/* ------------------------------------------------ Prototype ------------------------------------------------ */


uint8_t DS1307_DeviceIsReady(uint16_t _time_out);
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

uint8_t DS1307_SetTime(uint8_t _hour, uint8_t _minute, uint8_t _second, DS1307_MeridiemTypeDef _meridiem, uint16_t _time_out);
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
									* _STAT_OK / _STAT_ERROR
			
	Example :
			uint8_t result;
			
			result = DS1307_SetTime(12, 23, 47, _DS1307_PM, 100);
			
			result is _STAT_OK/_STAT_ERROR
			
*/

uint8_t DS1307_GetTime(uint8_t *_hour, uint8_t *_minute, uint8_t *_second, DS1307_MeridiemTypeDef *_meridiem, uint16_t _time_out);
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
									* _STAT_OK / _STAT_ERROR
			
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
			
			result is _STAT_OK/_STAT_ERROR
			
*/

uint8_t DS1307_SetDate(uint8_t _year, uint8_t _month, uint8_t _day, uint8_t _weekday, uint16_t _time_out);
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
									* _STAT_OK / _STAT_ERROR
			
	Example :
			uint8_t result;
			
			result = DS1307_SetDate(20, 1, 17, 0, 100);
			
			result is _STAT_OK/_STAT_ERROR
			
*/

uint8_t DS1307_GetDate(uint8_t *_year, uint8_t *_month, uint8_t *_day, uint8_t *_weekday, uint16_t _time_out);
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
									* _STAT_OK / _STAT_ERROR
			
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
			
			result is _STAT_OK/_STAT_ERROR
			
*/

uint8_t DS1307_SaveInRam(uint32_t _ram_address, uint8_t *_ram_data , uint8_t _size , uint16_t _time_out);
/*
	Guide   :
			Function description	This function is used to write data in RAM of RTC chip.
			
			Parameters
									* _ram_address : Address of ram for write data.
									* _ram_data    : Pointer to data.
									* _size        : Amount of data to be write.
									* _time_out    : Timeout duration.
									
			Return Values
									* _STAT_OK / _STAT_ERROR / _DS1307_RAM_SIZE_ERROR
			
	Example :
			uint8_t result;
			
			uint8_t my_data[27] = "Hello I Am Microcontroller";
			
			result = DS1307_SaveInRam(5, my_data, 26, 100);
			
			result is _STAT_OK/_STAT_ERROR/_DS1307_RAM_SIZE_ERROR
			
*/

uint8_t DS1307_ReadFromRam(uint32_t _ram_address, uint8_t *_ram_data , uint8_t _size , uint16_t _time_out);
/*
	Guide   :
			Function description	This function is used to read data from RAM of RTC chip.
			
			Parameters
									* _ram_address : Address of ram for read data.
									* _ram_data    : Pointer for save data.
									* _size        : Amount of data to be read.
									* _time_out    : Timeout duration.
									
			Return Values
									* _STAT_OK / _STAT_ERROR / _DS1307_RAM_SIZE_ERROR
			
	Example :
			uint8_t result;
			
			uint8_t my_data[56];
			
			result = DS1307_ReadFromRam(0, my_data, 20, 100);
			
			result is _STAT_OK/_STAT_ERROR/_DS1307_RAM_SIZE_ERROR
			
*/

uint8_t DS1307_Config(DS1307_ConfigTypeDef *_rtc_conf, uint16_t _time_out);
/*
	Guide   :
			Function description	This function is used to config RTC chip.
			
			Parameters
									* _rtc_conf : Pointer to a DS1307_ConfigTypeDef structure that contains
												  the configuration information for the specified chip properties.
												
									* _time_out : Timeout duration.
									
			Return Values
									* _STAT_OK / _STAT_ERROR
			
	Example :
			uint8_t result;
			
			DS1307_ConfigTypeDef rtc_cfg;
			
			rtc_cfg.ClockMode        = _DS1307_CLOCK_12H;
			rtc_cfg.OscillatorConfig = _DS1307_OSCILLATOR_ENABLE;
			rtc_cfg.OutputControl    = _DS1307_OUT_PIN_HIGH;
			rtc_cfg.SquareWaveConfig = _DS1307_SQW_DISABLE;
			rtc_cfg.SquareWaveRate   = _DS1307_SQW_8KHZ;
			
			result = DS1307_Config(&rtc_cfg, 1000);
			
			result is _STAT_OK/_STAT_ERROR
			
*/

uint8_t DS1307_GetConfig(DS1307_ConfigTypeDef *_rtc_conf, uint16_t _time_out);
/*
	Guide   :
			Function description	This function is used to get config of RTC chip.
			
			Parameters
									* _rtc_conf : Pointer to a DS1307_ConfigTypeDef structure that contains
												  the configuration information for the specified chip properties.
												
									* _time_out : Timeout duration.
									
			Return Values
									* _STAT_OK / _STAT_ERROR
			
	Example :
			uint8_t result;
			
			DS1307_ConfigTypeDef rtc_cfg;
			
			result = DS1307_Config(&rtc_cfg, 1000);
			
			result is _STAT_OK/_STAT_ERROR
			
*/


#endif /* __DS1307_H_ */
