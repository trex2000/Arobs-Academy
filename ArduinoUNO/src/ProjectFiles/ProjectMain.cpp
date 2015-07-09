/*
 * ProjectMain.cpp
 *
 * Created: 5/26/2015 2:22:43 PM
 *  Author: barna.peto
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
 * Function Implementation
 * Task function scheduled to run every 20ms
 */
void task20ms(void) {
	static uint8_t flag = 0;
	flag = 1 - flag;
	digitalWrite(13, flag);
	
	};

/** 
 * Function Implementation
 * Task function scheduled to run every 40ms
 */
void task40ms(void) {
	static uint8_t flag = 0;
	flag = 1 - flag;
	digitalWrite(12, flag);
	
	};
	
/** 
 * Function Implementation
 * Task function scheduled to run every 60ms
 */
void task60ms(void) {
	static uint8_t flag = 0;
	flag = 1 - flag;
	digitalWrite(11, flag);
	};
	
/** 
 * Function Implementation
 * Task function scheduled to run every 100ms
 */
void task100ms(void) {
	static uint8_t flag = 0;
	flag = 1 - flag;
	digitalWrite(10, flag);
	};
	
/** 
 * Function Implementation
 * Task function scheduled to run every 1000ms
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


static TaskType_stType tasks_st[] = {
	{ T_INTERVAL_20MS,	task20ms, 13 },
	{ T_INTERVAL_40MS,	task40ms, 12 },
	{ T_INTERVAL_60MS,	task60ms, 11 },
	{ T_INTERVAL_100MS,	task100ms, 10 },
	{ T_INTERVAL_1000MS,task1000ms, 9 },
};

/** 
 * Function Implementation
 * Return a pointer to tasks configuration table 
 */	
TaskType_stType *taskGetConfigPtr(void) {
	return tasks_st;
}

/** 
 * Function Implementation
 * Return the number of current tasks scheduled to run 
 */	
uint8_t getNrTasks(void) {
	return sizeof(tasks_st) / sizeof(*tasks_st);
}

/** 
 * Function Implementation
 * Initialize the timer 
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

uint16_t stui_tick;

uint8_t stui_TaskIndex;
volatile uint8_t taskTimeCounterFlag_u8;
volatile uint8_t taskTimeCounter_u8;
const uint8_t cui_numberOfTasks = getNrTasks();

static TaskType_stType *taskPtr;


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
	/*This is the setup function. It will be called once
	pinMode(13,OUTPUT);
	Serial.begin(9600);
	Serial.print("Hello World!");

	//PWM setup
	DDRD |= (1 << DDD6);
	// PD6 is now an output

	OCR2A = 128;
	// set PWM for 50% duty cycle

	
	
	TCCR2A |= (1 << COM2A1);
	// set none-inverting mode

	TCCR2A |= (1 << WGM21) | (1 << WGM20);
	// set fast PWM Mode

	TCCR2B |= (1 << CS21);
	// set prescaler to 8 and starts PWM*/
	
	
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
