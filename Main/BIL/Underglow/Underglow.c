/*
 * Underglow.c

 *  Author: thoma
 */ 

#include <avr/io.h>
#include "Underglow.h"

void turnOnUnder(void)
{
	PORTC = (PORTC | 0b00000100); // Sender 5V ud til C2
}
void turnOffUnder(void)
{
	PORTC = (PORTC & 0b11111011); // Sender 0V ud til C2
}