/*
 * Motor.c
 *
 * Created: 28-10-2021 13:32:57
 *  Author: Sebastian Kriegbaum
 */ 

#include "Motor.h"
#include "../RearLight/RearLight.h"
#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

void initMotor(void)
{
	OCR1A = 0x3FF;
	TCCR1A = 0b11000011;
	TCCR1B = 0b00000000;
	DDRB = 0b11111111;
	PORTB = 0b00001100;
	PORTB &= 0b11111011;
	
}


void carDrive(int speed, int acceleration)
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
	if (speed < 0) //bilen skal k�re bagl�ns.
	{
		if (PORTB == 0b00001000) //hvis bit 3 er sat, k�rer bilen fremad.
		{
			if (OCR1A == 0x3FF) //tjekker om bilen holder stille.
			{
				PORTB &= 0b11110111; //clearer bit 3, s� bilen bakker. 
				turnOnReverse();
			}
			else
			{
				OCR1A++;
				turnOnRearLightBreak();
				delay_us(acceleration);
			}
		}
		
		else //bilen k�rer allerede bagl�ns.
		{
			if (OCR1A < requestedSpeed) //hvis bilen k�rer for hurtigt.
			{
				OCR1A++;
				turnOnRearLightBreak();
				delay_us(acceleration);
			}
			else if (OCR1A > requestedSpeed) //hvis bilen k�rer for langsomt.
			{
				OCR1A--;
				delay_us(acceleration);
			}
			else //hvis bilens hastighed er korrekt, skal der intet foretages.
			{
				return;
			}
		}
	}
	
	else //bilen skal k�re forl�ns.
	{
		if (PORTB == 0b00001000) //hvis bit 3 er sat, k�rer bilen fremad.
		{
			if (OCR1A < requestedSpeed) //hvis bilen k�rer for hurtigt.
			{
				OCR1A++;
				turnOnRearLightBreak();
				delay_us(acceleration);
			}
			else if (OCR1A > requestedSpeed) //hvis bilen k�rer for langsomt.
			{
				OCR1A = OCR1A-1;
				delay_us(acceleration);
			}
			else //hvis bilens hastighed er korrekt, skal der intet foretages.
			{
				return;
			}	
		}
		else //bilen k�ererer bagl�ns.
		{
			if (OCR1A == 0x3FF) //tjekker om bilen holder stille.
			{
				PORTB |= 0b00001000; //setter bit 3, s� bilen k�ererererer forl�ns.
				turnOffReverse();
			}
			else
			{
				OCR1A++;
				turnOnRearLightBreak();
				delay_us(acceleration);
			}
		}

	}
}


void carStop()
{
	while (OCR1A != 0x3FF)
	{
		OCR1A++;
		turnOnRearLightBreak();
	}
	if((PORTB &0b00001000) != 0){ //Hvis bilen bakker og skal stoppe
		turnOffReverse();
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

void delay_us(int mikrosekunder)
{
	while(mikrosekunder > 0)
	{
		mikrosekunder--;
		_delay_us(1);
	}
}