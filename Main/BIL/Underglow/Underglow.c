/*
 * Underglow.c

 *  Author: thoma
 */ 

#include <avr/io.h>
#include "Underglow.h"

void turnOnUnderglow (void)
{
	PORTC = PORTC | 0b00000100; // Sender 5V ud til C2
}
void turnOffUnderglow (void)
{
	PORTC = PORTC & 0b11111011; // Sender 0V ud til C2
}