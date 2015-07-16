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


//#include <avr/io.h>
//#include <Arduino.h>
#include "lights.h"
#include "IO_extern.h"


void test_lights(void){
	
	
	
	setOutputPin(EN_SODPWM_ENABLE_MOTOR1,70);
	setOutputPin(EN_SODPWM_ENABLE_MOTOR2,70);
	
	if(GetInputPin (EN_SID_WIFI_CONTROL_UP))
	{
		static uint8_t flag=0;
		flag=1-flag;
		digitalWrite(6,flag);
		
		setOutputPin (EN_SOD_MOTOR12_0, 1);
		setOutputPin (EN_SOD_MOTOR12_1, 0);
		setOutputPin (EN_SOD_MOTOR12_2, 1);
		setOutputPin (EN_SOD_MOTOR12_3, 0);
		
	}
	else{
		
		setOutputPin (EN_SOD_MOTOR12_0, 0);
		setOutputPin (EN_SOD_MOTOR12_1, 0);
		setOutputPin (EN_SOD_MOTOR12_2, 0);
		setOutputPin (EN_SOD_MOTOR12_3, 0);
	}
	


}

