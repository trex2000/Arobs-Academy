/****************************************************************************
 * Copyright (C) 2015														*
 *                                                                          *
 * This file is part of RC CAR                                              *
 *                                                                          *
 *   Box is free software: you can redistribute it and/or modify it         *
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation, either version 3 of the License, or   *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   Box is distributed in the hope that it will be useful,                 *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with Box.  If not, see <http://www.gnu.org/licenses/>.   *
 ****************************************************************************/

/**
 * @file IO.c
 * @author Alex
 * @date 10 Jul 2015
 * @brief File containing functions for IO 
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 * @see http://www.stack.nl/~dimitri/doxygen/docblocks.html
 * @see http://www.stack.nl/~dimitri/doxygen/commands.html
 */

#include <avr/io.h>
#include "IO.h"
#include "IO_extern.h"

/**
 * @brief buffer holds the value of the inputs.
 *
 * Detailed buffer holds the value of the inputs.
 */
uint8_t inputBuffer_u8[EN_NUMBER_OF_ELEMENTS_INPUT];

/**
 * @brief buffer holds the value of the outputs.
 *
 * Detailed buffer holds the value of the outputs.
 */
uint8_t outputBuffer_u8[EN_NUMBER_OF_ELEMENTS_OUTPUTS];


/**
 * @brief Returns status of logical Input Pin.
 *
 * Links are generated automatically for webpages (like http://www.google.co.uk)
 * and for structures, like BoxStruct_struct. For typedef-ed types use
 * #BoxStruct.
 * For functions, automatic links are generated when the parenthesis () follow
 * the name of the function, like Box_The_Function_Name().
 * Alternatively, you can use #Box_The_Function_Name.
  * @param pinId_en logical input pin name. range: EN_INPUT_PINS
 * @return @c state of the pin.
 */


uint8_t GetInputPin (EN_INPUT_PINS pinId_en)
{	
	if (pinId_en>=EN_NUMBER_OF_ELEMENTS_INPUT)
{	
		return 0;
}	
	else
	{
		if ((matchingTableInputPins_acst[pinId_en].portType_en==EN_PORT_AI)||(matchingTableInputPins_acst[pinId_en].portType_en==EN_PORT_DI))
		{	
				return inputBuffer_u8[pinId_en];
		}	
		else
		{	
			return 0;
		}	
	}
	
	
}

/**
 * @brief Sets the specified value to the output pin and holds the value in output buffer
 *
 * @param pinId_en logical output pin name. range: EN_OUTPUT_PINS
 * @param value_u8 is an 8-bit value to be set to the digital out PWM and in the output buffer 
 * @return ??? nothing???
 */

void setOutputPin (EN_OUTPUT_PINS pinId_en, uint8_t value_u8)
{
	/*if (pinId_en>=EN_NUMBER_OF_ELEMENTS_OUTPUTS)
	{
		return 0; //function does NOT return a value
	}
	else
	{*/
		if ( getPortTypePWM(pinId_en))
		{
			//avem port cu pwm
			if (value_u8 <= MAX_PWM_VALUE)
			{
				outputBuffer_u8[pinId_en] = value_u8;
				DOPWM_setValue(EN_OUTPUT_PINS pinId_en, uint8_t value_u8); //setam ciclul PWM ????
			}
			else
			{
				//do nothing
			}
		}
		else
		{
			//nu este port cu pwm
			if (value_u8<=MAX_DIGITAL_VALUE)
			{
				outputBuffer_u8[pinId_en] = value_u8;
				//functia de Set pini digitali
			}
			else
			{
				//nu facem nimic
			}
		}
		
	//}
}

/**
 * @brief Returns the type of logical Output Pin.
 *
 * @param pinId_en logical input pin name. range: EN_OUTPUT_PINS
 * @return @c true if the pin is a digital out PWM
 */

 unsigned int getPortTypePWM(EN_OUTPUT_PINS pinId_en)
{
	if (matchingTableInputPins_acst[pinId_en].portType_en==EN_PORT_DOPWM)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
