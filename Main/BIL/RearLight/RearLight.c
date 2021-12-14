#include "rearlight.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void initRearLight (void)
{
	DDRE = 0xFF; //S�tter E til udgang da det er en E der sender PWM ud.
	TCCR3A = 0b10000011; //Del A til timer 3
	TCCR3B = 0b00000000; //Del B til timer 3
	
	TCCR4A = 0b00000000;
	TCCR4B = 0b00000000;
	TIMSK4 = 0b00000001;
}

void turnOnRearLightBreak (void)
{
	TCCR3B |= 0b00000001; //Bruges kun indtil implementering p� bil da ellers un�dvendig
	OCR3A=1023; //100% af 5V hvilket giver 50mA pr. leds�t
	
	TCCR4B |= 0b00000101;
	TCNT4 = 57723;
}

void turnOnRearLightDrive (void)
{
	TCCR3B |= 0b00000001; // S�tter prescaleren for at t�nde for PWM
	OCR3A = 205; // 20% af max (5V) hvilket giver 10mA pr. leds�t
}

void turnOffRear (void)
{
	OCR3A = 1;
	TCCR3B = TCCR3B & 0b11111000; // Slukker PWM til baglys
}

void turnOnReverse (void)
{
	PORTC = PORTC | 0b00000010; // Sender 5V ud til C1
}

void turnOffReverse (void)
{
	PORTC = PORTC & 0b11111101; // Sender 0V ud til C1
}