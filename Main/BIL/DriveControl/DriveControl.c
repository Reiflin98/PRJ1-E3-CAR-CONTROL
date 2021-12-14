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


extern counter;

void initSystem()
{
	InitUART(9600, 8);
 	initFrontLight();
 	initRearLight();
// 	initUnderglow();
	initMotor();
	initSwitchPort();
	
}

void driveControl()
{
	
	PORTB |= 0b00000100;
	PORTB &= 0b11111011;
	int ned_af_bakke = 0;
	//turnOnUnder();
	_delay_ms(500);
	playStart();
	_delay_ms(4000);
	turnOnFront();
	initRearLight();
	turnOnRearLightDrive();
	//
	do{
		switch (counter)
		{
		case 0:
			carDrive(50,1500);
			break;
		
		case 1: //Brik 1
			carDrive(60, 2500); //Nedsæt hastigheden lidt (Bakke snart)
			break;
			
		case 2: //Brik 2
			carDrive(90, 3000); //Bakke start - hastighed ydeligere ned
			break;
			
		case 3: //Brik 3
			if (ned_af_bakke < 850)
			{
				carDrive(-80, 0); //Hastighed ned inden bakken kører ned
				ned_af_bakke++;
				
			}else{
				carDrive(30, 4500);
			}
			
			break;
		
			
		case 4: //Brik 4
			carDrive(70, 1500); //HAstigheden op - bunden af bakken
			break;
			
		case 5: //Brik 5
			carDrive(40, 6000); //hastigheden lidt ned - gør klar til snart at stoppe
			break;
			
		case 6: //Brik 6
			carDrive(-60, 100); //Kør tilbage til refleksbrik 5
			break;
			
		case 7: //Brik 6
			carDrive(-60, 1500); //Refelksbrik 6 igen
			break;
			
		case 8: //Brik 5
			carDrive(70, 200); //Kør frem igen
			break;
			
		case 9: //Brik 5
			carDrive(70, 1000); //Kør frem igen
			break;
			
		case 10: //Brik 6
			carDrive(50, 6000); //Kør frem igen	
			break;
			
			
			
		}

	}while (counter < 11); //Går ud af do-while når refliksbrik 7 er nået
	
	carStop();
	_delay_ms(100);
	turnOffFront();
	turnOffRear();
	_delay_ms(1000);
	playStop();
	//
	//turnOffUnder();
	counter = 0;
}