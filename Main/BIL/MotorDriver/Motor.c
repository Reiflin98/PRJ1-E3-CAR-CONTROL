/*
 * Motor.c
 *
 * Created: 28-10-2021 13:32:57
 *  Author: Sebastian Kriegbaum
 */ 

#include "Motor.h"
#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

void initMotor(void)
{
	OCR1A = 0x3FF;
	TCCR1A = 0b11000011;
	TCCR1B = 0b00000000;
	DDRB = 0b11111111;
	PORTB = 0b00001000;
	
}


void carDrive(int speed, char acceleration)
{

	if(speed == 100){
	speed = 99;
	}
	volatile int requestedSpeed = (1023-((sqrt(speed * speed))*(1023/100))); 
	
	if (speed == 0) //bilen skal holde stille.
	{
		carStop();
		return;
	}
	if ((TCCR1B & 0b00000010) == 0)
	{
		TCCR1B = TCCR1B | 0b00000010;
	}
	if (speed < 0) //bilen skal køre baglæns.
	{
		if (PORTB == 0b00001000) //hvis bit 3 er sat, kører bilen fremad.
		{
			if (OCR1A == 0x3FF) //tjekker om bilen holder stille.
			{
				PORTB = 0b00000000; //clearer bit 3, så bilen bakker. 
			}
			else
			{
				OCR1A++;
				delay_ms(acceleration);
			}
		}
		
		else //bilen kører allerede baglæns.
		{
			if (OCR1A < requestedSpeed) //hvis bilen kører for hurtigt.
			{
				OCR1A++;
				delay_ms(acceleration);
			}
			else if (OCR1A > requestedSpeed) //hvis bilen kører for langsomt.
			{
				OCR1A--;
				delay_ms(acceleration);
			}
			else //hvis bilens hastighed er korrekt, skal der intet foretages.
			{
				return;
			}
		}
	}
	
	else //bilen skal køre forlæns.
	{
		if (PORTB == 0b00001000) //hvis bit 3 er sat, kører bilen fremad.
		{
			if (OCR1A < requestedSpeed) //hvis bilen kører for hurtigt.
			{
				OCR1A++;
				delay_ms(acceleration);
			}
			else if (OCR1A > requestedSpeed) //hvis bilen kører for langsomt.
			{
				OCR1A = OCR1A-1;
				delay_ms(acceleration);
			}
			else //hvis bilens hastighed er korrekt, skal der intet foretages.
			{
				return;
			}	
		}
		else //bilen køererer baglæns.
		{
			if (OCR1A == 0x3FF) //tjekker om bilen holder stille.
			{
				PORTB = 0b00001000; //setter bit 3, så bilen køererererer forlæns.
			}
			else
			{
				OCR1A++;
				delay_ms(acceleration);
			}
		}

	}
}


void carStop()
{
	while (OCR1A != 0x3FF)
	{
		OCR1A++;
		_delay_ms(2);
	}
	TCCR1B = (0b11111000 & TCCR1B);
	return;
}

void delay_ms(unsigned char milliseconds)
{
	while(milliseconds > 0)
	{
		milliseconds--;
		_delay_ms(1);
	}
}