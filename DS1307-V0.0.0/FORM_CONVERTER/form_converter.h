/*
------------------------------------------------------------------------------
~ File   : form_converter.h
~ Author : Majid Derhambakhsh
~ Version: V0.0.0
~ Created: 01/13/2020 03:15:00 AM
~ Brief  :
~ Support:
           E-Mail : Majid.Derhambakhsh@gmail.com (subject : Embedded Library Support)
           
           Github : https://github.com/Majid-Derhambakhsh
------------------------------------------------------------------------------
~ Description:    Library for convert data format.

~ Attention  :    

~ Changes    :    
------------------------------------------------------------------------------
*/

#ifndef __FORM_CONVERTER_H_
#define __FORM_CONVERTER_H_

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Include ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#include <stdint.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* ---------------------------- Public ---------------------------- */

#ifndef _ASCII_ZERO
	#define _ASCII_ZERO '0' /* ASCII Code */
#endif

#ifndef _LAST_BIT
	#define _LAST_BIT 7 /* Value for select last bit of byte data */
#endif

#ifndef _NIBBLE_SHIFT
	#define _NIBBLE_SHIFT 4 /* Value for nibble shift */
#endif

#ifndef _HIGH_BYTE_SEL
	#define _HIGH_BYTE_SEL 0xF0 /* Value for select high byte */
#endif

#ifndef _LOW_BYTE_SEL
	#define _LOW_BYTE_SEL 0xF /* Value for select low byte */
#endif

#ifndef _NMB_OF_HEXAD_BITS
	#define _NMB_OF_HEXAD_BITS 16 /* Number of bits */
#endif

#ifndef _UNITY_DIVIDER
	#define _UNITY_DIVIDER 10 /* Value for divide */
#endif

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Enum ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Prototype ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

uint8_t FormConvert_DecimalToHexad(uint8_t _decimal); /* Up to two digit */
/*
	Guide   :
			Function description	This function is used to convert decimal to hexadecimal format.
			
			Parameters
									* _decimal : Data for convert.
			Return Values
									* Converted data
			
	Example :
			uint8_t my_data;
			
			my_data = FormConvert_DecimalToHexad(66);
			
			my_data value is 0x66
			
*/

uint8_t FormConvert_HexadToDecimal(uint8_t _hexad); /* Up to two digit */
/*
	Guide   :
			Function description	This function is used to convert hexadecimal to decimal format.
			
			Parameters
									* _hexad : Data for convert.
			Return Values
									* Converted data
			
	Example :
			uint8_t my_data;
			
			my_data = FormConvert_HexadToDecimal(0x12);
			
			my_data value is 12
			
*/

void FormConvert_NumberToBinaryString(uint8_t _nmb, char *_str); /* Up to 8 bit */
/*
	Guide   :
			Function description	This function is used to convert number to binary code in string format.
			
			Parameters
									* _nmb : Data for convert.
									* _str : Pointer to string.
									
			Return Values
									-
			
	Example :
			char my_binary_data[8];
			
			FormConvert_NumberToBinaryString(10,my_binary_data);
			
			my_binary_data value is "00001010"
			
*/

uint8_t FormConvert_BinaryStringToNumber(char *_str); /* Up to 8 bit */
/*
	Guide   :
			Function description	This function is used to convert binary code to number format.
			
			Parameters
									* _str : Pointer to string.
									
			Return Values
									* Converted data
			
	Example :
			uint8_t my_number;
			
			my_number = FormConvert_BinaryStringToNumber("00011010");
			
			my_number value is 26
			
*/

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ End of the program ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#endif
