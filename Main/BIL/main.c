/*
 * BIL.c
 *
 * Created: 28-10-2021 13:22:51
 * Author : thoma
 */ 

#include <avr/io.h>
#include "DriveControl/DriveControl.h"
#include "Drivers/switch.h"

int counter = 0;
//Initialiser interrupt counter - husk playReflex();
ISR(Refleks registreret){
	counter++;
	playReflex();
}


int main(void)
{
	initSystem();
	
    while (1) 
    {
		if (switchOn(1) > 0)
		{
			driveControl(); //start driveControl / System
			// nå system færdigt -> afvent nyt tryk 
		}
    }
	
}


