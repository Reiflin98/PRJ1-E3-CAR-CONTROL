/*
 * Motor.c
 *
 * Created: 28-10-2021 13:32:57
 *  Author: Sebastian Kriegbaum
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define delay _delay_ms(5)

void initMotor(void)
{
	OCR3A = 0x3ff;
	TCCR3A = 0b11000011;
	TCCR3B = 0;
	DDRB = 0xff;
	return;
}


void carDrive(int speed)
{
	
	int requestedSpeed = 1023-(sqrt(speed^2)*(1023/100));
	if (speed == 0) //bilen skal holde stille.
	{
		carStop();
		return;
	}
	if (TCCR3B != 0)
	{
		TCCR3B = 0b00000010;
	}
	if (speed < 0) //bilen skal køre baglæns.
	{
		if (PINB == 0b00001000) //hvis bit 3 er sat, kører bilen fremad.
		{
			if (OCR3A == 1023) //tjekker om bilen holder stille.
			{
				PORTB = 0b00000000; //clearer bit 3, så bilen bakker. 
			}
			else
			{
				OCR3A++;
				delay;
			}
		}
		
		else //bilen kører allerede baglæns.
		{
			if (OCR3A < requestedSpeed) //hvis bilen kører for hurtigt.
			{
				OCR3A++;
				delay;
			}
			else if (OCR3A > requestedSpeed) //hvis bilen kører for langsomt.
			{
				OCR3A--;
				delay;
			}
			else //hvis bilens hastighed er korrekt, skal der intet foretages.
			{
				return;
			}
		}
	}
	
	else //bilen skal køre forlæns.
	{
		if (PINB == 0b00001000) //hvis bit 3 er sat, kører bilen fremad.
		{
			if (OCR3A < requestedSpeed) //hvis bilen kører for hurtigt.
			{
				OCR3A++;
				delay;
			}
			else if (OCR3A > requestedSpeed) //hvis bilen kører for langsomt.
			{
				OCR3A--;
				delay;
			}
			else //hvis bilens hastighed er korrekt, skal der intet foretages.
			{
				return;
			}	
		}
		else //bilen køererer baglæns.
		{
			if (OCR3A == 1023) //tjekker om bilen holder stille.
			{
				PORTB = 0b00001000; //setter bit 3, så bilen køererererer forlæns.
			}
			else
			{
				OCR3A++;
				delay;
			}
		}

	}
}


void carStop(void)
{
	while (OCR3A != 1023)
	{
		OCR3A++;
		delay;
	}
	TCCR3B = (0b11111000 & TCCR3B);
	return;
}