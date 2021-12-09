/*
 * MP3.c
 *
 * Created: 28-10-2021 13:33:49
 *  Author: thoma
 */ 
#include <avr/io.h>
#include "MP3.h"
#define XTAL 16000000

void InitUART(unsigned long BaudRate, unsigned char DataBit, unsigned char Rx_Int)
{
	if ((BaudRate >= 300) && (BaudRate <= 115200) && (DataBit >=5) && (DataBit <= 8))
	{
		// "Normal" clock, no multiprocessor mode (= default)
		UCSR1A = 0b00100000;
		// No interrupts enabled
		// Receiver enabled
		// Transmitter enabled
		// No 9 bit operation
		UCSR1B = 0b00011000;
		// Asynchronous operation, 1 stop bit
		// Bit 2 and bit 1 controls the number of data bits
		UCSR1C = (DataBit-5)<<1;
		// Set Baud Rate according to the parameter BaudRate:
		// Adding (8*Baudrate) ensures correct rounding (up/down)
		UBRR0 = (XTAL+(8*BaudRate))/(16*BaudRate) - 1;
		
		if (Rx_Int == 0)
		{
			UCSR0B = 0b00011000;
		}
		else
		{
			UCSR0B = 0b10011000;
		}
	}
}

void SendChar(char Tegn)
{
	// Wait for transmitter register empty (ready for new character)
	while ( (UCSR0A & (1<<5)) == 0 )
	{}
	// Then send the character
	UDR0 = Tegn;
}