/*
 * Motor.c
 *
 * Created: 28-10-2021 13:32:57
 *  Author: Sebastian Kriegbaum
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#define delay _delay_ms(5)

void initMotor(void)
{
	OCR1A = 0x3ff;
	TCCR1A = 0b11000011;
	TCCR1B = 0;
	DDRB = 0xff;
	PORTB = 0b00001000;
}


void carDrive(int speed)
{
	int requestedSpeed = 1023-(sqrt(speed * speed)*(1023/100)); 
	if (speed == 0) //bilen skal holde stille.
	{
		carStop();
		return;
	}
	if (TCCR1B == 0)
	{
		TCCR1B = 0b00000010;
	}
	if (speed < 0) //bilen skal k�re bagl�ns.
	{
		if (PINB == 0b00001000) //hvis bit 3 er sat, k�rer bilen fremad.
		{
			if (OCR1A == 1023) //tjekker om bilen holder stille.
			{
				PORTB = 0b00000000; //clearer bit 3, s� bilen bakker. 
			}
			else
			{
				OCR1A++;
				delay;
			}
		}
		
		else //bilen k�rer allerede bagl�ns.
		{
			if (OCR1A < requestedSpeed) //hvis bilen k�rer for hurtigt.
			{
				OCR1A++;
				delay;
			}
			else if (OCR1A > requestedSpeed) //hvis bilen k�rer for langsomt.
			{
				OCR1A--;
				delay;
			}
			else //hvis bilens hastighed er korrekt, skal der intet foretages.
			{
				return;
			}
		}
	}
	
	else //bilen skal k�re forl�ns.
	{
		if (PINB == 0b00001000) //hvis bit 3 er sat, k�rer bilen fremad.
		{
			if (OCR1A < requestedSpeed) //hvis bilen k�rer for hurtigt.
			{
				OCR1A++;
				delay;
			}
			else if (OCR1A > requestedSpeed) //hvis bilen k�rer for langsomt.
			{
				OCR1A--;
				delay;
			}
			else //hvis bilens hastighed er korrekt, skal der intet foretages.
			{
				return;
			}	
		}
		else //bilen k�ererer bagl�ns.
		{
			if (OCR1A == 1023) //tjekker om bilen holder stille.
			{
				PORTB = 0b00001000; //setter bit 3, s� bilen k�ererererer forl�ns.
			}
			else
			{
				OCR1A++;
				delay;
			}
		}

	}
}


void carStop()
{
	while (OCR1A != 1023)
	{
		OCR1A++;
		delay;
	}
	TCCR1B = (0b11111000 & TCCR1B);
	return;
}