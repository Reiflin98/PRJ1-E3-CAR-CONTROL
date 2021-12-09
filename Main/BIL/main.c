/*
 * BIL.c
 *
 * Created: 28-10-2021 13:22:51
 * Author : thoma
 */ 

#include <avr/io.h>
#include "DriveControl/DriveControl.h"
#include "Drivers/switch.h"
#include "FrontLight/FrontLight.h"
#include "RearLight/RearLight.h"
#include <avr/interrupt.h>



// global counter til switch cases
volatile unsigned char counter = 0;

// Left right detection
unsigned char detection = 0;


//Initialiser interrupt counter - husk playReflex();
ISR(INT2_vect) //refleks registreret
{
	counter++;
	//if (detection != 0)
	//{
//
	//}else
	//{
		//counter++;
		////playReflex();
		//detection = 1;
		//TCNT1 = 34286;
		//TCCR1B |= 0b00000101;
	//}
}

ISR(TIMER4_OVF_vect) //0,5s delay til bremselys
{
	turnOnRearLightDrive();
	TCCR4B = 0b00000000;
}

//ISR(TIMER1_OVF_vect){
	//detection = 0;
	//TCCR1B &= 0b11111000;
//}



int main(void)
{
	sei();
	EIMSK=0b00000100;
	EICRA=0b00110000;
	
	//Timer til reflex
	//TCCR1A = 0b00000000;
	//TCCR1B = 0b00000000;
	
	initSystem();
	counter = 0;
	
    while (1) 
    {
		if (switchOn(1) != 0)
		{
			driveControl(); //start driveControl / System
			// når system færdigt -> afvent nyt tryk 
		}
    }
	
}