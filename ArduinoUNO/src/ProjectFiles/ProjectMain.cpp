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

 /** \brief Index for task scheduler */
uint8_t stui_TaskIndex;

/** \brief Flag for timer overflow  */
volatile uint8_t taskTimeCounterFlag_u8;

/** \brief Counter used for count how many times the timer has overflow */
volatile uint8_t taskTimeCounter_u8;

/** \brief Variable used to store the current number of tasks scheduled to run */
const uint8_t cui_numberOfTasks = getNrTasks();

/** \brief Pointer type variable which points to the task array */
static TaskType_stType *taskPtr;

/**
* @brief Implementation of setup function 
*
* Implementation of setup function which runs only once at the begining 
* @note This function initialize the counter and the flag for timer overflow event
* @note Here will be initialized the timer also, and is asigned the pointer to the table of tasks 
* @return void
*/
void setup()
{
	taskTimeCounterFlag_u8 = 0;
	taskTimeCounter_u8 = 0;
	initIO(); /*Functia de initializare IO*/
	
	timer1_init();		
	stui_TaskIndex = 0;				
	taskPtr = taskGetConfigPtr();	
}

/**
* @brief Implementation of loop function
*
* Implementation of loop function which runs cyclic afther the setup function was executed
* @note This function contains the request for the diferent functions scheduled to ron on different periods of time
* @return void
*/
void loop()
{	
	// if 20ms have passed
	if(taskTimeCounterFlag_u8==1) {
		for(stui_TaskIndex=0; stui_TaskIndex < cui_numberOfTasks; stui_TaskIndex++) {
			if((taskTimeCounter_u8 % taskPtr[stui_TaskIndex].interval_u16) == 0 ) {
				if((taskPtr[stui_TaskIndex].ptrFunc) != NULL) {
					//execute the task function
					(*taskPtr[stui_TaskIndex].ptrFunc)();	
				} else {
					// do nothing
				}				
			}		
		}
		taskTimeCounterFlag_u8 = 0;
	}	
}


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
void task40ms(void) {};

/**
* @brief Implementation of function that handle the 60ms requests
*
* Implementation of function that handle the 60ms requests
* @return void
* @note Void function with no return.
*/
void task60ms(void) {};

/**
* @brief Implementation of function that handle the 100ms requests
*
* Implementation of function that handle the 100ms requests
* @return void
* @note Void function with no return.
*/
void task100ms(void) {};

/**
* @brief Implementation of function that handle the 1000ms requests
*
* Implementation of function that handle the 1000ms requests
* @return void
* @note Void function with no return.
*/
void task1000ms(void) {};
	
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
	// initialize Timer1
	cli();             // disable global interrupts
	TCCR1A = 0;        // set entire TCCR1A register to 0
	TCCR1B = 0;		   // set entire TCCR1A register to 0
	
	// initialize counter
	TCNT1 = T_TIMER_START;
	
	// enable Timer1 overflow interrupt:
	TIMSK1 = (1 << TOIE1);
	// set the timer with a prescaler of 256
	TCCR1B |= (1 << CS12);
	// enable global interrupts:
	sei();
}

/**
 * @brief Implementation of the function that initialize the PWM 
 * 
 * Implementation of the function that initialize the PWM
 * @return void
 *  
 */
void PWM_Init() {
	//PWM setup
	DDRD |= (1 << DDD5) | (1 << DDD6 );
	// PD6 is now an output

	//OCR2A = PWM_DC_Max/(100/PWM_DC);
	//OCR2B = PWM_DC_Max/(100/PWM_DC);
	//function called cyclic form the request
	// set PWM for 50% duty cycle

	TCCR2A |= (1 << COM2A1);
	// set none-inverting mode

	TCCR2A |= (1 << WGM21) | (1 << WGM20);
	// set fast PWM Mode

	TCCR2B |= (1 << CS20) | (1 << CS21) | (1 << CS22); 
	// set prescaler to ??? and starts PWM*/
}

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
