#include <avr/io.h>
#include <stdlib.h>
#include "MP3.h"
#define F_CPU 16000000
#include <util/delay.h>

// Target CPU frequency
#define XTAL 16000000

/*************************************************************************
USART initialization.
    Asynchronous mode.
    RX and TX enabled.
    No interrupts enabled.
    Number of Stop Bits = 1.
    No Parity.
    Baud rate = Parameter.
    Data bits = Parameter.
Parameters:
    BaudRate:Wanted Baud Rate (300-115200).
    Databit: Wanted number of Data Bits (5-8).
    Parity: 'E' (Even parity), 'O' (Odd parity), otherwise No Parity.
*************************************************************************/
void InitUART(unsigned long BaudRate, unsigned char DataBit)
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
    UBRR1 = (XTAL+(8*BaudRate))/(16*BaudRate) - 1;
	}  
		// set volume to 30
		SendChar(0x7E);
		SendChar(0x06);
		SendChar(0x00);
		SendChar(0x00);
		SendChar(0xE1);
		SendChar(0xFF);
		SendChar(0xDC);
		SendChar(0xEF);	
}


/*************************************************************************
Awaits transmitter register ready.
Then send the character.
Parameter :
	Tegn : Character for sending. 
*************************************************************************/
void SendChar(char Tegn)
{
  // Wait for transmitter register empty (ready for new character)
  while ( (UCSR1A & (1<<5)) == 0 )
  {}
  // Then send the character
  UDR1 = Tegn;
}

void playStart()
{
	// Afspil track 1
	SendChar(0x7E);
	SendChar(0x03);
	SendChar(0x00);
	SendChar(0x00);
	SendChar(0x01);
	SendChar(0xFF);
	SendChar(0xFC);
	SendChar(0xEF);
	
	_delay_ms(5000);
}

void playReflex()
{
	// Afspil track 2
	SendChar(0x7E);
	SendChar(0x03);
	SendChar(0x00);
	SendChar(0x00);
	SendChar(0x02);
	SendChar(0xFF);
	SendChar(0xFB);
	SendChar(0xEF);
	
	_delay_ms(3000);
}

void playStop()
{
	// Afspil track 3
	SendChar(0x7E);
	SendChar(0x03);
	SendChar(0x00);
	SendChar(0x00);
	SendChar(0x03);
	SendChar(0xFF);
	SendChar(0xFA);
	SendChar(0xEF);
	
	_delay_ms(5000);
}