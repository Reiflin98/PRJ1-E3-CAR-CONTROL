/*
 * MP3.h
 *
 * Created: 28-10-2021 13:38:52
 *  Author: thoma
 */ 

void InitUART(unsigned long BaudRate, unsigned char DataBit);
void SendChar(char Tegn);
void startSound(void);
void gunSound(void);
void endSound(void);