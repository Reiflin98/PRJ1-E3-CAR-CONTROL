#include "rearlight.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void initRearLight (void)
{
	TCCR3A = 0b10000011;
	TCCR3B = 0b00000000;
	
	TCCR4A = 0b00000000;
	TCCR4B = 0b00000000;
}

void turnOnRearLightBreak (void)
{
	if (OCR3A!=1023)
	{
		TCCR3B = 0b00000001;
		OCR3A=1023;
		TCCR4B = 0b00000101;
	}
	
	TCNT4 = 57724;
}

void turnOnRearLightDrive (void)
{
	TCCR3B = 0b00000001;
	OCR3A = 204;
}

void turnOffRear (void)
{
	TCCR3B = 0b00000000;
}

void turnOnReverse (void)
{
	PORTA = PORTA | 0b00000010;
}

void turnOffReverse (void)
{
	PORTA = PORTA & 0b11111101;
}