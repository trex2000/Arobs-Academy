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


#define CHECK_BIT(var,pos) ((var) & (1<<(pos))) //macro care verifica o pozitie din registru daca e pe 1 logic
#define MAX_PWM_VALUE_REG 256


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
 * @brief Returns status of logical Output Pin.
 *
 * Links are generated automatically for webpages (like http://www.google.co.uk)
 * and for structures, like BoxStruct_struct. For typedef-ed types use
 * #BoxStruct.
 * For functions, automatic links are generated when the parenthesis () follow
 * the name of the function, like Box_The_Function_Name().
 * Alternatively, you can use #Box_The_Function_Name.
  * @param pinId_en logical output pin name. range: EN_OUPUT_PINS
 * @return @c state of the pin.
 */
void setOutputPin (EN_OUTPUT_PINS pinId_en, uint8_t value_u8) 
{
	if (pinId_en>=EN_NUMBER_OF_ELEMENTS_OUTPUTS) /**< tests if the pin is out of range */
	{
		return ;
	}
	else if (matchingTableOutputPins_acst[pinId_en].portType_en==EN_PORT_DOPWM)   /**<verificam daca portul e de tip PWM  */
		{
			/**<PWM port  */
			 if (value_u8 > MAX_PWM_VALUE)
			{
				value_u8 = MAX_PWM_VALUE; /**< sets the value to be put in output buffer to the maximum PWM value */
				
			}
			outputBuffer_u8[pinId_en]=value_u8;
		}
		else
		{
			/**<not a PWM port  */
			if (matchingTableOutputPins_acst[pinId_en].portType_en==EN_PORT_DO)
			{
				if(value_u8 > MAX_DIGITAL_VALUE) /**<implementat pentru robustete  */
				{
					value_u8 = MAX_DIGITAL_VALUE;
				}
				outputBuffer_u8[pinId_en] = value_u8;
				/**< functia de Set pini digitali */
			}
			else
			{
				/**<do nothing  */
			}
	}
}	



/**
 * @brief Function implementation for processing output buffer
 *
 * Function implementation for processing output buffer
 * @return void
 */
void processOutputBuffer() {
	EN_OUTPUT_PINS bufferIndex_len;
	for(bufferIndex_len=0; bufferIndex_len<EN_NUMBER_OF_ELEMENTS_OUTPUTS; bufferIndex_len++) {
		switch (matchingTableOutputPins_acst[bufferIndex_len].portType_en)
		{
			case EN_PORT_DO: 
				processDigitalOutput(bufferIndex_len);								
				break; /**<end case EN_PORT_DO  */
				
			case EN_PORT_DOPWM:
				
				break;
				
			default:
				break;	
		} /**< end switch port type  */
	}
}

/**< functia pentru citirea unui pin */
int getValue(uint8_t pin){
	
	uint8_t Register; /**< variabila in care stocam valoarea registrului din care citim */

	/**< cautam registrul aferent piniului selectat, PINx de unde citim starea pinului */
	if ((0 <=pin)||(pin <=7))
	{
		Register = PIND; /**< Registrii PINx sunt Read Only */
	}
	else if((8 >=pin)||(pin <=13))
	{
		Register = PINB;
		/**< pin= pin-7; resetam pinul astfel incat sa putem citi din registrul pinB daca acesta nu e setat in memorie in continuare la PIND */
	}
	else if((14 >=pin)||(pin <=19))
	{
		Register = PINC;
		/**< pin= pin-13; */
	}

	else
	Register=NOT_A_PIN;

	/**< cautam pinul din registrul aferent,de aici putem afla starea pinilor daca sunt Input (1), sau Output (0); */
	if(CHECK_BIT(Register,pin)==1)
	{ return true;}
	else
	{return false;}
	
}

//-------------Cod pentru Setare Output PWM-----------------
int DOPWM_setValue(char pin, int duty)
{
	
	
	char value;

	//formula pentru duty cycle in procente
	value = (duty*256)/100;
	
	//Setam duty cycle pentru fiecare pin cu registrii OCR2A, OCR2B
	OCR2A = value;
	
	return 0;
	

	
}

//functie de initializare pwm
void initIO()
{
	//setam pinul 3 ca output
	DDRD |= (1 << DDD3);
	
	DDRB |= (1 <<DDB3); // DDRB l-am gasit in fisierul iom328p.h ???
	// PB3 is now an output, pin Digital 11
	
	/* SETAM TIMERUL 2 PENTRU Modul PHASE CORRECTED PWM*/
	//setam Timer Counter Control Register A pe None-inverting mode si PWM Phase Corrected Mode
	TCCR2A |= (1 << COM2A1) | (0 << COM2A0) | (1 << COM2B1)| (0 << COM2B0);
	// set none-inverting mode on bytes (7,6,5,4) for timer 2

	TCCR2A |= (0 << WGM21) | (1 << WGM20);
	// set  PWM Phase Corrected Mode using OCR2A TOP value on bytes (1,0)

	// setam Timer Counter Control Register B pe PWM Phase Corrected Mode si cu un prescaler de 64
	TCCR2B |= (1 << CS22) | (1 << WGM22);
	// set prescaler to 64 and starts PWM and sets  PWM Phase Corrected Mode
	
}


/**
 * @brief Function implementation for processing output buffer
 *
 * Function implementation for processing output buffer
 * @return void
 */

void processDigitalOutput(EN_OUTPUT_PINS bufferIndex_len) {
	switch (matchingTableOutputPins_acst[bufferIndex_len].portName_en) {
		case EN_PORT_B:
		if(outputBuffer_u8[bufferIndex_len]) {
			PORTB |= (1<<matchingTableOutputPins_acst[bufferIndex_len].portVal_u8);
			} else {
			PORTB &= ~(1<<matchingTableOutputPins_acst[bufferIndex_len].portVal_u8);
		}
		break;
		
		case EN_PORT_C:
		if(outputBuffer_u8[bufferIndex_len]) {
			PORTC |= (1<<matchingTableOutputPins_acst[bufferIndex_len].portVal_u8);
			} else {
			PORTC &= ~(1<<matchingTableOutputPins_acst[bufferIndex_len].portVal_u8);
		}
		break;
		case EN_PORT_D:
		if(outputBuffer_u8[bufferIndex_len]) {
			PORTD |= (1<<matchingTableOutputPins_acst[bufferIndex_len].portVal_u8);
			} else {
			PORTD &= ~(1<<matchingTableOutputPins_acst[bufferIndex_len].portVal_u8);
		}
		break;
		
		default:
		break;
	}
}

/**
 * @brief Function implementation for processing output buffer
 *
 * Function implementation for processing output buffer
 * @return void
 */
void processDigitalOutputPWM(EN_OUTPUT_PINS bufferIndex_len) {
	uint8_t tempValue_lu8;
	tempValue_lu8 = (outputBuffer_u8[bufferIndex_len] *MAX_PWM_VALUE_REG)/ MAX_PWM_VALUE;
	if(matchingTableOutputPins_acst[bufferIndex_len].portType_en==EN_PORT_DOPWM) {
		switch(bufferIndex_len) {
			// TODO: to be checked if correct
			case EN_SODPWM_ENABLE_MOTOR1:
				OCR2A = tempValue_lu8;
				break;
				
			case EN_SODPWM_ENABLE_MOTOR2:
				OCR2B = tempValue_lu8;
				break;
				
			default:
				break;
		}
	} else {
		//do nothing
	}

}

/**
 * @brief Function implementation for analog input from lightsensor
 *
 * Function implementation for analog input from lightsensor
 * @return void
 */


void setupADC()
{
	ADMUX=(1<<REFS0);/**<Function implementation for analog input from lightsensor*/
	/**<the lightsensor is in ADC0 input*/
	/**<the MUX2:0 pins are 000 for ADC0 input*/
	ADCSRA=(1<<ADEN)|(1<<ADIE)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);
		/**<it is set the ADC enable bit and the ADC interrupt enable bit*/
		/**<it is set the ADC prescaler for 128 cycles*/
	DIDR0=(1<<ADC0D);
	startConversion();		
}

/**
 * @brief Function implementation for starting the ADC conversion
 *
 * Function implementation for starting the ADC conversion
 * @return void
 */

void startConversion()
{
	ADCSRA|=(1<<ADSC);/**< sets the bit to start the conversion */
}

