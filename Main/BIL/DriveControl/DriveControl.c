/*
 * DriveControl.c
 *
 * Created: 28-10-2021 13:31:26
 *  Author: thoma
 */ 
#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "DriveControl.h"
#include "../FrontLight/FrontLight.h"
#include "../MotorDriver/Motor.h"
#include "../MP3/MP3.h"
#include "../RearLight/RearLight.h"
#include "../Underglow/Underglow.h"
#include "../Drivers/switch.h"
#include <avr/interrupt.h>


extern counter;

void initSystem()
{
	InitUART(9600, 8);
 	initFrontLight();
 	initRearLight();
// 	initUnderglow();
	initMotor();
	initSwitchPort();
	EIMSK=0b00000100;
	EICRA=0b00110000;
	
}

void stopRoutine()
{
		_delay_ms(100);
		turnOnReverse();
		turnOnFront();
		turnOnRearLightDrive();
		_delay_ms(100);
		turnOffReverse();
		turnOffFront();
		turnOffRear();
		_delay_ms(100);
		turnOnReverse();
		turnOnFront();
		turnOnRearLightDrive();
		_delay_ms(100);
		turnOffReverse();
		turnOffFront();
		turnOffRear();
}

void driveControl()
{
	counter = 0;

	if ((EIFR && 0b00000100) != 0)
	{
		EIFR |= 0b00000100;
	}
	sei();
	PORTB |= 0b00000100;
	PORTB &= 0b11111011;
	int nedAfBakke = 0;
	_delay_ms(500);
	turnOnFront();
	turnOnRearLightDrive();
	_delay_ms(100);
	playStart();
	_delay_ms(4000);
	//
	do{
		switch (counter)
		{
		case 0:
			carDrive(50,1500);
			break;
		
		case 1: //Brik 1
			carDrive(60, 2500); //Neds�t hastigheden lidt (Bakke snart)
			break;
			
		case 2: //Brik 2
			carDrive(90, 3000); //Bakke start - hastighed ydeligere ned
			break;
			
		case 3: //Brik 3
			if (nedAfBakke < 850)
			{
				carDrive(-80, 0); //Hastighed ned inden bakken k�rer ned
				nedAfBakke++;
				
			}else{
				carDrive(30, 4500);
			}
			
			break;
		
			
		case 4: //Brik 4
			carDrive(70, 1500); //HAstigheden op - bunden af bakken
			break;
			
		case 5: //Brik 5
			carDrive(40, 6000); //hastigheden lidt ned - g�r klar til snart at stoppe
			break;
			
		case 6: //Brik 6
			carDrive(-60, 100); //K�r tilbage til refleksbrik 5
			break;
			
		case 7: //Brik 6
			carDrive(-60, 1500); //Refelksbrik 6 igen
			break;
			
		case 8: //Brik 5
			carDrive(70, 200); //K�r frem igen
			break;
			
		case 9: //Brik 5
			carDrive(70, 1000); //K�r frem igen
			break;
			
		case 10: //Brik 6
			carDrive(50, 6000); //K�r frem igen	
			break;
			
			
			
		}

	}while (counter < 11); //G�r ud af do-while n�r refliksbrik 7 er n�et
	
	carStop();
	_delay_ms(550);
	turnOffFront();
	turnOffRear();
	_delay_ms(1000);
	
	playStop();
	
	stopRoutine();

	
	cli();
}