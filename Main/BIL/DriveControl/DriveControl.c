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
// 	initFrontLight();
// 	initRearLight();
// 	initUnderglow();
// 	initMP3();
	initMotor();
	initSwitchPort();
	
}

void driveControl()
{
	
	PORTB |= 0b00000001;
	PORTB &= 0b11111110;
	int ned_af_bakke = 0;
	//turnOnUnder();
	//_delay_ms(5000);
	//playStart();
	//_delay_ms(5000);
	//turnOnFront();
	//turnOnRear();
	//
	do{
		switch (counter)
		{
		case 0:
			carDrive(30,2);
			break;
		
		case 1: //Brik 1
			carDrive(50, 4); //Neds�t hastigheden lidt (Bakke snart)
			break;
			
		case 2: //Brik 2
			carDrive(80, 2); //Bakke start - hastighed ydeligere ned
			break;
			
		case 3: //Brik 3
			if (ned_af_bakke < 500)
			{
				carDrive(-17, 1); //Hastighed ned inden bakken k�rer ned
				ned_af_bakke++;
				
			}else{
				carDrive(30, 7);
			}
			
			break;
		
			
		case 4: //Brik 4
			carDrive(70, 2); //HAstigheden op - bunden af bakken
			break;
			
		case 5: //Brik 5
			carDrive(50, 8); //hastigheden lidt ned - g�r klar til snart at stoppe
			break;
			
		case 6: //Brik 6
			carDrive(-40, 1); //K�r tilbage til refleksbrik 5
			break;
			
		case 7: //Brik 6
			carDrive(-50, 2); //Refelksbrik 6 igen
			break;
			
		case 8: //Brik 5
			carDrive(70, 1); //K�r frem igen
			break;
			
		case 9: //Brik 5
			carDrive(70, 2); //K�r frem igen
			break;
			
		case 10: //Brik 6
			carDrive(50, 7); //K�r frem igen	
			break;
			
			
			
		}

	}while (counter < 11); //G�r ud af do-while n�r refliksbrik 7 er n�et
	
	carStop();
	
	//playStop();
	//
	//turnOffUnder();
	//turnOffFront();
	//turnOffRear();
	counter = 0;
}