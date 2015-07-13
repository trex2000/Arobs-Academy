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
 * @file ProjectMain.cpp
 * @author Adrian
 * @date 26/05/2015
 * @brief File containing functions for IO External
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 * @see http://www.stack.nl/~dimitri/doxygen/docblocks.html
 * @see http://www.stack.nl/~dimitri/doxygen/commands.html
 */

/*Include Header files*/
#include <ProjectMain.h>
#include <schedulerConfig.h>
#include <PWM.h>

/*FOR PWM*/
#include <avr/io.h>
#include <avr/interrupt.h>

/*Include C Files*/
#include "TaskFunctions.h"

/**
* @brief Implementation of function that handle the 20ms requests
*
* Implementation of function that handle the 20ms requests
* @return void
* @note Void function with no return.
*/
void task20ms(void) {
	processOutputBuffer();
	processDigitalOutputPWM();	
};

/**
* @brief Implementation of function that handle the 40ms requests
*
* Implementation of function that handle the 40ms requests
* @return void
* @note Void function with no return.
*/
void task40ms(void) {
	static uint8_t flag = 0;
	flag = 1 - flag;
	digitalWrite(12, flag);
	
	};
	
/**
* @brief Implementation of function that handle the 60ms requests
*
* Implementation of function that handle the 60ms requests
* @return void
* @note Void function with no return.
*/
void task60ms(void) {
	static uint8_t flag = 0;
	flag = 1 - flag;
	digitalWrite(11, flag);
	};
	
/**
* @brief Implementation of function that handle the 100ms requests
*
* Implementation of function that handle the 100ms requests
* @return void
* @note Void function with no return.
*/
void task100ms(void) {
	static uint8_t flag = 0;
	flag = 1 - flag;
	digitalWrite(10, flag);
	};
	
/**
* @brief Implementation of function that handle the 1000ms requests
*
* Implementation of function that handle the 1000ms requests
* @return void
* @note Void function with no return.
*/
void task1000ms(void) {
	static uint8_t flag = 0;
	flag = 1 - flag;
	digitalWrite(9, flag);	
};

void InitPWM(char pin);
/*
* Main code called on reset is in  Arduino.h
*/

/**
 * @brief Array of tasks and interval of execution
 *
 * Array of tasks and interval of execution
 */
static TaskType_stType tasks_st[] = {
	{ T_INTERVAL_20MS,	task20ms },
	{ T_INTERVAL_40MS,	task40ms },
	{ T_INTERVAL_60MS,	task60ms },
	{ T_INTERVAL_100MS,	task100ms },
	{ T_INTERVAL_1000MS,task1000ms},
};

/**
 * @brief Implementation of the function that returns a pointer to the tasks array
 *
 * @return A pointer to the array of tasks
 * @see tasks_st[];
 */
TaskType_stType *taskGetConfigPtr(void) {
	return tasks_st;
}

/**
 * @brief Implementation of the function that returns the number of current tasks cheduled to run
 *
 * @return number of tasks
 */
uint8_t getNrTasks(void) {
	return sizeof(tasks_st) / sizeof(*tasks_st);
}

/**
 * @brief Implementation of the function that initialize the timer 
 * 
 * Implementation of the function that initialize the timer 1 used in task scheduler
 * @return void
 *  
 */
void timer1_init() {
	pinMode(13, OUTPUT);
	pinMode(12, OUTPUT);
	pinMode(11, OUTPUT);
	pinMode(10, OUTPUT);
	pinMode(9, OUTPUT);
	
	
	// initialize Timer1
	cli();             // disable global interrupts
	TCCR1A = 0;        // set entire TCCR1A register to 0
	TCCR1B = 0;
	
	// initialize counter
	TCNT1 = T_TIMER_START;
	
	// enable Timer1 overflow interrupt:
	TIMSK1 = (1 << TOIE1);
	// set the timer with a prescaller of 256
	TCCR1B |= (1 << CS12);
	// enable global interrupts:
	sei();
}

uint8_t stui_TaskIndex;
volatile uint8_t taskTimeCounterFlag_u8;
volatile uint8_t taskTimeCounter_u8;
const uint8_t cui_numberOfTasks = getNrTasks();

static TaskType_stType *taskPtr;

/**
 * @brief Implementation of the function that thandle timer overflow ISR
 * 
 * Implementation of the function that thandle timer overflow ISR
 * @return void
 *  
 */
ISR(TIMER1_OVF_vect) {
	TCNT1 = T_TIMER_START;
	taskTimeCounterFlag_u8 = 1;
	taskTimeCounter_u8++;
}

void PWM_Init() {
	//PWM setup
	DDRD |= (1 << DDD5) | (1 << DDD6 );
	// PD6 is now an output

	//OCR2A = PWM_DC_Max/(100/PWM_DC);
	//OCR2B = PWM_DC_Max/(100/PWM_DC);
	//functie apelata ciclic cu request-ul respectiv
	// set PWM for 50% duty cycle

	TCCR2A |= (1 << COM2A1);
	// set none-inverting mode

	TCCR2A |= (1 << WGM21) | (1 << WGM20);
	// set fast PWM Mode

	TCCR2B |= (1 << CS20) | (1 << CS21) | (1 << CS22); //????
	// set prescaler to ??? and starts PWM*/
}

void setup()
{
	taskTimeCounterFlag_u8 = 0;
	taskTimeCounter_u8 = 0;
	initIO(); /*Functia de initializare IO*/
	
	timer1_init();		
	stui_TaskIndex = 0;				
	taskPtr = taskGetConfigPtr();	
}



void loop()
{	
	// if 20ms have passed
	if(taskTimeCounterFlag_u8==1) {
		for(stui_TaskIndex=0; stui_TaskIndex < cui_numberOfTasks; stui_TaskIndex++) {
			if((taskTimeCounter_u8 % taskPtr[stui_TaskIndex].interval_u16) == 0 ) {
			
				if((taskPtr[stui_TaskIndex].ptrFunc) != NULL) {
					(*taskPtr[stui_TaskIndex].ptrFunc)();	
				} else {
					// do nothing
				}
				
			}
		
		}
		taskTimeCounterFlag_u8 = 0;
	}
	
	
	
	
	
}
