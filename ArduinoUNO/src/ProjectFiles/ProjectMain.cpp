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
	static uint8_t flag = 0;
	flag = 1 - flag;
	digitalWrite(13, flag);
	
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
	char pin = 12;
	taskTimeCounterFlag_u8 = 0;
	taskTimeCounter_u8 = 0;
	InitPWM(pin); /*Functia de initializare pwm*/
	
	timer1_init();	
	
	stui_tick = 0;						// System tick
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
					digitalWrite(taskPtr[stui_TaskIndex].led, HIGH);
				} else {
					// do nothing
				}
				
			}
		
		}
		taskTimeCounterFlag_u8 = 0;
	}
	
	
	
	
	
}

						//------------------------Cod pentru Citire IMPUTS---------------
#define CHECK_BIT(var,pos) ((var) & (1<<(pos))) //macro care verifica o pozitie din registru daca e pe 1 logic
//functia pentru citirea unui pin
int getValue(uint8_t pin){
	
uint8_t Register; // variabila in care stocam valoarea registrului din care citim

	//cautam registrul aferent piniului selectat, PINx de unde citim starea pinului
	if ((0 <=pin)||(pin <=7))
	{
		Register = PIND; //Registrii PINx sunt Read Only
	}
	else if((8 >=pin)||(pin <=13))
	{
		Register = PINB;
		//pin= pin-7; resetam pinul astfel incat sa putem citi din registrul pinB daca acesta nu e setat in memorie in continuare la PIND
	}
	else if((14 >=pin)||(pin <=19))
	{
		Register = PINC;
		//pin= pin-13;
	}

	else
	Register=NOT_A_PIN;

	//cautam pinul din registrul aferent,de aici putem afla starea pinilor daca sunt Input (1), sau Output (0);
	if(CHECK_BIT(Register,pin)==1)
	{ return true;}
	else
	{return false;}
	
}

//-------------Cod pentru Setare Output PWM-----------------
int DOPWM_setValue(char pin, int duty)
{
		//setam pinii ca si output
	if (pin == 3)
	{
		//setam pinul 3 ca output
		DDRD |= (1 << DDD3);
		// PD3 is now an output, pin Digital 3
	}
	else if (pin == 11)
	{
		DDRB |= (1 <<DDB3); // DDRB l-am gasit in fisierul iom328p.h ???
		// PB3 is now an output, pin Digital 11
	}
	
	char value;

	//formula pentru duty cycle in procente
	value = (duty*256)/100;
	
	//Setam duty cycle pentru fiecare pin cu registrii OCR2A, OCR2B
	OCR2A = value;
	
	return 0;
	

	
}
//functie de initializare pwm
void InitPWM(char pin)
{
	//setam pinii ca si output
	if (pin == 3)
	{
		//setam pinul 3 ca output
		DDRD |= (1 << DDD3);
		// PD3 is now an output, pin Digital 3
	}
	else if (pin == 11)
	{
		DDRB |= (1 <<DDB3); // DDRB l-am gasit in fisierul iom328p.h ???
		// PB3 is now an output, pin Digital 11
	}
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
