/*
 * BIL.c
 *
 * Created: 28-10-2021 13:22:51
 * Author : thoma
 */ 

#include <avr/io.h>
#include "DriveControl.h"

int counter = 0;
void buttonIsPressed(void);

// erkl�r *** knap til funktion


int main(void)
{
    buttonIsPressed = false;
	
	initSystem()
	
    while (1) 
    {
		if (buttonIsPressed(void)==true)
		{
			driveControl(); //start driveControl / System
			// n� system f�rdigt -> afvent nyt tryk 
		}
    }
	//Thomas er sku faktisk lidt grim v3.0
	
}


