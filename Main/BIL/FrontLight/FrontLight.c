#include "frontlight.h"
#include <avr/io.h>

void initFrontLight (void)
{
	DDRC = 0xFF; // Gør alle C pins til udgange
}
void turnOnFront (void)
{
	PORTC = PORTC | 0b00000001; // Sender 5V ud til C0
}
void turnOffFront (void)
{
	PORTC = PORTC & 0b11111110; // Sender 0V ud til C0
}