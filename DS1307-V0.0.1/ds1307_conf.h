/*
------------------------------------------------------------------------------
~ File   : ds1307_conf.h
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

#ifndef __DS1307_CONF_H_
#define __DS1307_CONF_H_

/* ~~~~~~~~~~~~~~~~~~ Options ~~~~~~~~~~~~~~~~~~ */

/* ~~~~~~~~~~~~~~~ Include files ~~~~~~~~~~~~~~~ */

#include "FORM_CONVERTER/form_converter.h"
//#include "I2C_UNIT/i2c_unit.h"
//#include "STM32_I2C/stm32_i2c.h"

/* 
	Uncomment this library for AVR microcontroller
	
		#include "I2C_UNIT/i2c_unit.h"
	
	Uncomment this library for ARM microcontroller
		#include "STM32_I2C/stm32_i2c.h"
	
*/

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#endif /* __DS1307_CONF_H_ */
