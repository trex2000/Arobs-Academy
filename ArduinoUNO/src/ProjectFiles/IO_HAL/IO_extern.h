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
 * @file IO_extern.h
 * @author Adrian
 * @date 10 Jul 2015
 * @brief File containing functions for IO External
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 * @see http://www.stack.nl/~dimitri/doxygen/docblocks.html
 * @see http://www.stack.nl/~dimitri/doxygen/commands.html
 */


#ifndef _IO_EXTERN_
#define _IO_EXTERN_

/**
 * @brief Section for h files inclusion
 *
 * Section for h files inclusion
 */
#include "IO.h"


/**
 * @brief maximum value for PWM
 *
 * maximum value for PWM
 */
#define MAX_PWM_VALUE  100u

/**
 * @brief maximum value for digital out
 *
 * maximum value for digital out
 */
#define MAX_DIGITAL_VALUE 1u

/**
 * @brief Enumeration of logical inputs
 *
 * Enumeration of logical inputs.
 */
typedef enum en_input_pins {
	EN_SIA_LIGHTSENSOR ,				/**< Lightsensor analogic input */
	EN_SID_WIFI_CONTROL_UP ,			/**< WifiControl Up. */
	EN_SID_WIFI_CONTROL_DOWN ,          /**< WifiControl Down*/
	EN_SID_WIFI_CONTROL_RIGHT ,         /**< WifiControl Right*/
	EN_SID_WIFI_CONTROL_LEFT ,          /**< WifiControl Left */
	EN_NUMBER_OF_ELEMENTS_INPUT ,       /**< Number of input pins*/
} EN_INPUT_PINS;

/**
 * @brief Enumeration of logical outputs
 *
 * Enumeration of logical outputs.
 */
typedef enum en_output_pins {
	EN_SOD_MOTOR12_0,					/**< Motor 12 digital output 1 */
	EN_SOD_MOTOR12_1,				    /**< Motor 12 digital output 2 */
	EN_SOD_MOTOR12_2,				    /**< Motor 12 digital output 3 */
	EN_SOD_MOTOR12_3,					/**< Motor 12 digital output 4 */
	EN_SODPWM_ENABLE_MOTOR1,			/**< Digital out PWM on  Motor1 */
	EN_SODPWM_ENABLE_MOTOR2,			/**< Digital out PWM on  Motor2 */
	EN_SOD_LEFT_FLASHER,				/**< Digital out for Left Flasher */
	EN_SOD_RIGHT_FLASHER,				/**< Digital out for Right Flasher */
	EN_SOD_LOW_BEAM,					/**< Digital out for Low Beam */
	EN_NUMBER_OF_ELEMENTS_OUTPUTS       /**< Number of output pins  */
}EN_OUTPUT_PINS;

/**
 * @brief Enumeration of Ports
 *
 * Enumeration of Ports
 */
typedef enum en_port_enums
{
	EN_PORT_B,			/**< Port B  */
	EN_PORT_C,			/**< Port C  */
	EN_PORT_D			/**< Port D  */
}EN_PORT_ENUMS;

/**
 * @brief A simple stub function to show how links do work.
 *
 * Links are generated automatically for webpages (like http://www.google.co.uk)
 * and for structures, like BoxStruct_struct. For typedef-ed types use
 * #BoxStruct.
 * For functions, automatic links are generated when the parenthesis () follow
 * the name of the function, like Box_The_Function_Name().
 * Alternatively, you can use #Box_The_Function_Name.
 * @return @c NULL is always returned.
 */
extern uint8_t GetInputPin (EN_INPUT_PINS pinId_en);
extern void setOutputPin (EN_OUTPUT_PINS pinId_en, uint8_t value_u8);
#endif