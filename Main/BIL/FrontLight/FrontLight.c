#include "frontlight.h"
#include <avr/io.h>

void initFrontLight (void)
{
	PORTA = 0;
	DDRA = 0xFF; // Gør alle A pins til udgange
}
void turnOnFront (void)
{
	PORTA = PORTA | 0b00000001;
}
void turnOffFront (void)
{
	PORTA = PORTA & 0b11111110;
}