/*
 * BIL.c
 *
 * Created: 28-10-2021 13:22:51
 * Author : thoma
 */ 

#include <avr/io.h>
#include "DriveControl/DriveControl.h"
#include "Drivers/switch.h"
#include <avr/interrupt.h>


// global counter til switch cases
volatile unsigned counter = 0;

// Left right detection
unsigned char detection =0;


//Initialiser interrupt counter - husk playReflex();
ISR(INT0_vect) //refleks registreret
{
	if (detection!=1)
	{
		detection++;
		counter++;
		playReflex();
	}
	else
	{
		detection=0;
	}
}



int main(void)
{
	sei();
	EIMSK=0b00000001;
	EICRA=0b00000011;
	
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


