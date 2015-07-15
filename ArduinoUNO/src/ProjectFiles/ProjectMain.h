/*
 * ProjectMain.h
 *
 * Created: 5/26/2015 2:21:47 PM
 *  Author: barna.peto
 */ 


#ifndef PROJECTMAIN_H_
#define PROJECTMAIN_H_

/*Include Arduino headers*/
#include <Arduino.h>

#define ARDUINO_MAIN

// Disable some warnings for the Arduino files
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wattributes"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wuninitialized"


/*
* Libraries
*/
// Standard Arduino source files for serial:
//#include <HardwareSerial.h>
// Restore original warnings configuration
// Standard Arduino source files for serial:
#include <HardwareSerial.h>

// Unused source files:
//#include <WInterrupts.c>
//#include <wiring_pulse.c>
//#include <wiring_shift.c>
//#include <IPAddress.cpp>
//#include <Tone.cpp>
#pragma GCC diagnostic pop

/**
 * @brief Function definition for PWM initialization
 *
 * Function definition for PWM initialization
 * For functions, automatic links are generated when the parenthesis () follow
 * the name of the function, like Box_The_Function_Name().
 * Alternatively, you can use #Box_The_Function_Name.
 * @return void
 */
void PWM_Init();


void InitPWM(char pin);
void timer0_init();

#endif /* PROJECTMAIN_H_ */