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
 * @file IO.h
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

#ifndef _IO_
#define _IO_
#include "IO_extern.h"

/**
 * @brief Defines type of physical port
 *
 * Defines type of physical port
 */
typedef enum port_type_enum
{
	EN_PORT_DI,				/**< Digital Input port */
	EN_PORT_DO,				/**< Digital Output port */
	EN_PORT_AI,				/**< Analog Input port */
	EN_PORT_DOPWM,			/**< Digital PWM Output port */
	EN_PORT_LAST_ELEMENT	/**< Number of port types */
} PORT_TYPES_EN;


/**
 * @brief New datatype used in table which connects Logical Input Definitions to Physical Input Def
 *
 * New datatype used in table which connects Logical Input Definitions to Physical Input Def
 */
typedef struct port_types_struct
{
	uint8_t portVal_u8;				/**< Bit position of port */
	EN_PORT_ENUMS  portName_en;		/**< Selection of the port */
	PORT_TYPES_EN portType_en;		/**< Type of the port ( Digital, Analog..) */
} PORT_TYPES_ST;


/**
 * @brief New datatype used in table which connects Logical Outputs Definitions to Physical Outputs Def
 *
 * New datatype used in table which connects Logical Outputs Definitions to Physical Outputs Def
 */
PORT_TYPES_ST const matchingTableOutputPins_acst[EN_NUMBER_OF_ELEMENTS_OUTPUTS] = {
	{PORTD2, EN_PORT_D, EN_PORT_DO},     /**< SOD_Motor12_0 */
	{PORTD3, EN_PORT_D, EN_PORT_DO},	 /**<SOD_Motor12_1 */
	{PORTB6, EN_PORT_B, EN_PORT_DO},     /**<SOD_Motor12_2 */
	{PORTB7, EN_PORT_B, EN_PORT_DO},     /**<SOD_Motor12_3 */
	{PORTD1, EN_PORT_D, EN_PORT_DOPWM},  /**<SODPWM_EnableMotor1 */
	{PORTD5, EN_PORT_D, EN_PORT_DOPWM},  /**<ODPWM_EnableMotor2 */
	{PORTC2, EN_PORT_C, EN_PORT_DO},     /**<SOD_LeftFlasher */
	{PORTC1, EN_PORT_C, EN_PORT_DO},     /**<SOD_RightFlasher */
	{PORTD4, EN_PORT_D, EN_PORT_DO}      /**<SOD_LowBeam */
};
/**
 * @brief New datatype used in table which connects Logical Input Definitions to Physical Input Def
 *
 * New datatype used in table which connects Logical Input Definitions to Physical Input Def
 */
PORT_TYPES_ST const matchingTableInputPins_acst[EN_NUMBER_OF_ELEMENTS_INPUT] = {
	{PORTC0, EN_PORT_C, EN_PORT_AI},     /**< EN_SIA_LIGHTSENSOR */
	{PORTD7, EN_PORT_D, EN_PORT_DI}, 	 /**< EN_SID_WIFI_CONTROL_UP */
	{PORTB0, EN_PORT_B, EN_PORT_DI},	 /**< EN_SID_WIFI_CONTROL_DOWN */
	{PORTB5, EN_PORT_B, EN_PORT_DI},	 /**< EN_SID_WIFI_CONTROL_RIGHT */
	{PORTB4, EN_PORT_B, EN_PORT_DI}	     /**< EN_SID_WIFI_CONTROL_LEFT */
};

/**
 * @brief Function definition for processing input buffer
 *
 * Function implementation for processing input buffer.
 * For functions, automatic links are generated when the parenthesis () follow
 * the name of the function, like Box_The_Function_Name().
 * Alternatively, you can use #Box_The_Function_Name.
 * @return void
 */
void processInputBuffer();


/**
 * @brief Function definition for processing output buffer
 *
 * Function implementation for processing output buffer.
 * For functions, automatic links are generated when the parenthesis () follow
 * the name of the function, like Box_The_Function_Name().
 * Alternatively, you can use #Box_The_Function_Name.
 * @return void
 */
void processOutputBuffer();

/**
 * @brief Function definition for get value
 *
 * Function definition for set output pin
 * For functions, automatic links are generated when the parenthesis () follow
 * the name of the function, like Box_The_Function_Name().
 * Alternatively, you can use #Box_The_Function_Name.
 * @return void
 */
void int getValue(uint8_t pin);


/**
 * @brief Function definition for processing Digital output
 *
 * Function definition for set output pin
 * For functions, automatic links are generated when the parenthesis () follow
 * the name of the function, like Box_The_Function_Name().
 * Alternatively, you can use #Box_The_Function_Name.
 * @return void
 */
void processDigitalOutput(EN_OUTPUT_PINS bufferIndex_len);

/**
 * @brief Function definition for processDigitalOutputPWM
 *
 * Function definition for set output pin
 * For functions, automatic links are generated when the parenthesis () follow
 * the name of the function, like Box_The_Function_Name().
 * Alternatively, you can use #Box_The_Function_Name.
 * @return void
 */
void processDigitalOutputPWM(EN_OUTPUT_PINS bufferIndex_len);


#endif
