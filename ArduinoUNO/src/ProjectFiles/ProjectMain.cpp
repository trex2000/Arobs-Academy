/*
 * ProjectMain.cpp
 *
 * Created: 5/26/2015 2:22:43 PM
 *  Author: barna.peto
 */ 

/*Include Header files*/
#include <ProjectMain.h>
#include <schedulerConfig.h>


/*FOR PWM*/
#include <avr/io.h>
#include <avr/interrupt.h>

/*
* Main code called on reset is in  Arduino.h
*/

void task20ms(void) {};
void task40ms(void) {};
void task60ms(void) {};
void task100ms(void) {};
void task1000ms(void) {};

static TaskType_stType tasks_st[] = {
	{ T_INTERVAL_20MS,	task20ms },
	{ T_INTERVAL_40MS,	task40ms },
	{ T_INTERVAL_60MS,	task60ms },
	{ T_INTERVAL_100MS,	task100ms },
	{ T_INTERVAL_1000MS,task1000ms },
};

TaskType_stType *taskGetConfigPtr(void) {
	return tasks_st;
}

uint8_t getNrTasks(void) {
	return sizeof(tasks_st) / sizeof(*tasks_st);
}


void timer1_init() {
	// set the timer with a prescaler = 1024;
	TCCR1B |= (1<<CS02)|(1<<CS00); 
	
	// initialize counter
	TCNT1 = T_TIMER_START;	
	
	// enable overflow interrupt
	TIMSK1 |= (1<<TOIE1);
	
	//enable global intterupts
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

void setup()
{
	taskTimeCounterFlag_u8 = 0;
	taskTimeCounter_u8 = 0;
	
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
				} else {
					// do nothing
				}
				
			}
		
		}
		taskTimeCounterFlag_u8 = 0;
	}
	
	
	
	
	
}

