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