
/*
 * TaskFunctions.h
 *
 * Created: 08.07.2015 14:20:06
 *  Author: Adrian
 */ 

#ifndef TASKFUNCTIONS_H
#define TASKFUNCTIONS_H

/** 
 * Function prototype
 * Task function scheduled to run every 20ms
 */
void task20ms(void);

/** 
 * Function prototype
 * Task function scheduled to run every 40ms
 */
void task40ms(void);

/** 
 * Function prototype
 * Task function scheduled to run every 60ms
 */
void task60ms(void);

/** 
 * Function prototype
 * Task function scheduled to run every 100ms
 */
void task100ms(void);

/** 
 * Function prototype
 * Task function scheduled to run every 1000ms
 */
void task1000ms(void);

/** 
 * Function prototype
 * Initialize the timer 
 */
void timer1_init();


#endif