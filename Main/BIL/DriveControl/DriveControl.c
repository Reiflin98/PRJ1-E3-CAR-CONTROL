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
			carDrive(50, 5); //Nedsæt hastigheden lidt (Bakke snart)
			break;
			
		case 2: //Brik 2
			carDrive(80, 1); //Bakke start - hastighed ydeligere ned
			break;
			
		case 3: //Brik 3
			if (ned_af_bakke < 5000)
			{
				carDrive(-17, 1); //Hastighed ned inden bakken kører ned
				ned_af_bakke++;
				
			}else{
				carDrive(30, 7);
			}
			
			break;
		
			
		case 4: //Brik 4
			carDrive(70, 5); //HAstigheden op - bunden af bakken
			break;
			
		case 5: //Brik 5
			carDrive(50, 10); //hastigheden lidt ned - gør klar til snart at stoppe
			break;
			
		case 6: //Brik 6
			carDrive(-30, 1); //Kør tilbage til refleksbrik 5
			break;
			
		case 7: //Brik 6
			carDrive(-50, 3); //Refelksbrik 6 igen
			break;
			
		case 8: //Brik 5
			carDrive(70, 1); //Kør frem igen
			break;
			
		case 9: //Brik 5
			carDrive(70, 4); //Kør frem igen
			break;
			
		case 10: //Brik 6
			carDrive(50, 7); //Kør frem igen	
			break;
			
			
			
		}

	}while (counter < 11); //Går ud af do-while når refliksbrik 7 er nået
	
	carStop();
	
	//playStop();
	//
	//turnOffUnder();
	//turnOffFront();
	//turnOffRear();
	counter = 0;
}