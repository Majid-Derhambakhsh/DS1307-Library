/*
------------------------------------------------------------------------------
~ File   : form_converter.c
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

#include "form_converter.h"

/* ------------- Functions ------------- */

uint8_t FormConvert_DecimalToHexad(uint8_t _decimal) /* Up to two digit */
{
	return (((_decimal / _UNITY_DIVIDER) << _NIBBLE_SHIFT)|(_decimal % _UNITY_DIVIDER));
}
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

uint8_t FormConvert_HexadToDecimal(uint8_t _hexad) /* Up to two digit */
{
	return (((((_hexad & _HIGH_BYTE_SEL) / _NMB_OF_HEXAD_BITS) % _UNITY_DIVIDER) * _UNITY_DIVIDER) + ((_hexad & _LOW_BYTE_SEL) % _UNITY_DIVIDER));
}
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

void FormConvert_NumberToBinaryString(uint8_t _nmb, char *_str) /* Up to 8 bit */
{
	
	int8_t bit_counter = _LAST_BIT;
	
	/* ......................... */
	
	for (; bit_counter >= 0; bit_counter--)
	{
		*_str = ((_nmb >> bit_counter) & 1) + _ASCII_ZERO;
		_str++;
	}
	
	*_str = '\0';
	
}
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

uint8_t FormConvert_BinaryStringToNumber(char *_str) /* Up to 8 bit */
{
	
	uint8_t nmb = 0;
	int8_t  bit_counter = _LAST_BIT;
	
	/* ......................... */
	
	for (; bit_counter >= 0; bit_counter--)
	{
		nmb |= ((*_str - _ASCII_ZERO) << bit_counter);
		_str++;
	}
	
	return nmb;
}
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

