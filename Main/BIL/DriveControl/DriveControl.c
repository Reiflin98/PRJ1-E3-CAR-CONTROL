/*
 * DriveControl.c
 *
 * Created: 28-10-2021 13:31:26
 *  Author: thoma
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include "DriveControl.h"
#include "../FrontLight/FrontLight.h"
#include "../MotorDriver/Motor.h"
#include "../MP3/MP3.h"
#include "../RearLight/RearLight.h"
#include "../Underglow/Underglow.h"
#include "../Drivers/switch.h"

void initSystem()
{
	initFrontLight();
	initRearLight();
	initUnderglow();
	initMP3();
	initMotor();
	initSwitchPort();
}

void driveControl()
{
	turnOnUnder();
	_delay_ms(5000);
	playStart();
	_delay_ms(5000);
	turnOnFront();
	turnOnRear();
	
	do{
		switch (counter)
		{
		case 0: //ingen brik endnu
			accelerateForward(50); //Accelerer inden 1. brik
			break;
			
		case 1: //Brik 1
			accelerateForward(35); //Nedsæt hastigheden lidt (Bakke snart)
			break;
			
		case 2: //Brik 2
			accelerateForward(20); //Bakke start - hastighed ydeligere ned
			break;
			
		case 3: //Brik 3
			accelerateForward(10); //Hastighed ned inden bakken kører ned
			break;
			
		case 4: //Brik 4
			accelerateForward(50); //HAstigheden op - bunden af bakken
			break;
			
		case 5: //Brik 5
			accelerateForward(40); //hastigheden lidt ned - gør klar til snart at stoppe
			break;
			
		case 6: //Brik 6
			accelerateBackwards(30); //Kør tilbage til refleksbrik 5
			break;
			
		case 7: //Brik 6
			accelerateBackwards(40); //Refelksbrik 6 igen
			break;
			
		case 8: //Brik 5
			accelerateForward(50); //Kør frem igen
			break;
			
		case 9: //Brik 5
			accelerateForward(50); //Kør frem igen
			break;
			
		case 10: //Brik 6
			accelerateForward(30); //Kør frem igen	
			break;
			
		}
	}while (counter < 11); //Går ud af do-while når refliksbrik 7 er nået
	
	carStop(); 
	playStop();
	
	turnOffUnder();
	turnOffFront();
	turnOffRear();
}

