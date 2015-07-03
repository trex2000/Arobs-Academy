/*
 * ProjectMain.cpp
 *
 * Created: 5/26/2015 2:22:43 PM
 *  Author: barna.peto
 */ 

/*Include Header files*/
#include <ProjectMain.h>



/*FOR PWM*/
//#include <avr/io.h>


/*
* Main code called on reset is in  Arduino.h
*/



void setup()
{
	/*This is the setup function. It will be called once*/
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
	// set prescaler to 8 and starts PWM	
}



void loop()
{
	/*This is the main loop function. Simple LED toggling example*/
	digitalWrite(13,LOW);
	delay(100);
	digitalWrite(13,HIGH);
	delay(100);
}

