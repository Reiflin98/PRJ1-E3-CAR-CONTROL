#include "rearlight.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void initRearLight (void)
{
	DDRE = 0xFF;		 //Sætter E til udgang da det er en E der sender PWM ud.
	TCCR3A = 0b10000011; //Del A til timer 3
	TCCR3B = 0b00000000; //Del B til timer 3
	
	TCCR4A = 0b00000000; //Del A til timer 4
	TCCR4B = 0b00000000; //Del B til timer 4
}

void turnOnRearLightBreak (void)
{
	TCCR3B |= 0b00000001; //Starter timer 3
	OCR3A=1023;			  //100% af 5V hvilket giver 50mA pr. ledsæt
	
	TCCR4B |= 0b00000101; //Starter timer 4
	TIMSK4 = 0b00000001; //Starter timer 4
	TCNT4 = 57723;	     //Starttidspunkt der passer med 0,5s
}

void turnOnRearLightDrive (void)
{
	TCCR3B |= 0b00000001; // Sætter prescaleren for at tænde for PWM
	OCR3A = 205;		  // 20% af max (5V) hvilket giver 10mA pr. ledsæt
}

void turnOffRear (void)
{
	TCCR3B = 0b00000000; // Slukker PWM til baglys
}

void turnOnReverse (void)
{
	PORTC = PORTC | 0b00000010; // Sender 5V ud til C1
}

void turnOffReverse (void)
{
	PORTC = PORTC & 0b11111101; // Sender 0V ud til C1
}