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
volatile unsigned char counter = 0;

// Left right detection
unsigned char detection = 0;


//Initialiser interrupt counter - husk playReflex();
ISR(INT2_vect) //refleks registreret
{
	counter++;
	//if (detection == 0)
	//{
		//counter++;
		////playReflex();
		//detection = 1;
		//TCNT1 = 62411;
		//TCCR1B |= 0b00000101;

	//}else
	//{
		
	//}
}

<<<<<<< HEAD
=======
ISR(TIMER4_OVF_vect)
{
	turnOnRearLightDrive();
	TCCR4B = 0b00000000;
}

>>>>>>> 5f48685bc2778b02f9207224087c28e27ebfb478
//ISR(TIMER1_OVF_vect){
	//detection = 0;
	//TCCR1B &= 0b11111000;
//}



int main(void)
{
	sei();
	EIMSK=0b00000100;
	EICRA=0b00110000;
	
	//timer
	//TCCR1A = 0b00000000;
	//TCCR1B = 0b00000000;
	//TIMSK1 = 0b00000001;
	
	
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