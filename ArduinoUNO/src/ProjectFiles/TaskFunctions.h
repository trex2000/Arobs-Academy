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
 * @file TaskFunctions.h
 * @author Adrian
 * @date 10 Jul 2015
 * @brief File containing functions for Task Scheduler
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 * @see http://www.stack.nl/~dimitri/doxygen/docblocks.html
 * @see http://www.stack.nl/~dimitri/doxygen/commands.html
 */
#ifndef TASKFUNCTIONS_H
#define TASKFUNCTIONS_H

/**
 * @brief Function declaration for tasks which are executed every 20ms
 * Function declaration for tasks which are executed every 20ms.
 * Alternatively, you can use #Box_The_Function_Name.
 * @return void
 */
void task20ms(void);

/**
 * @brief Function declaration for tasks which are executed every40ms
 * Function declaration for tasks which are executed every 40ms
 * Alternatively, you can use #Box_The_Function_Name.
 * @return void
 */
void task40ms(void);

/**
 * @brief Function declaration for tasks which are executed every 60ms
 * Function declaration for tasks which are executed every 60ms.
 * Alternatively, you can use #Box_The_Function_Name.
 * @return void
 */
void task60ms(void);

/**
 * @brief Function declaration for tasks which are executed every 100ms
 * Function declaration for tasks which are executed every 100ms
 * Alternatively, you can use #Box_The_Function_Name.
 * @return void
 */
void task100ms(void);

/**
 * @brief Function declaration for tasks which are executed every 1000ms
 * Function declaration for tasks which are executed every 1000ms
 * Alternatively, you can use #Box_The_Function_Name.
 * @return void
 */
void task1000ms(void);

/**
 * @brief Function definition for timer initialization
 * Function implementation for timer initialization.
 * Alternatively, you can use #Box_The_Function_Name.
 * @return void
 */
void timer1_init();

#endif // end define TASKFUNCTIONS_H