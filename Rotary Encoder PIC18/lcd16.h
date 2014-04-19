#ifndef __lcd16_h_
#define __lcd16_h_

#include <p18F458.h>

#define RS PORTCbits.RC3
#define EN PORTCbits.RC2

void numToLcd(unsigned char );
void gotoXy(unsigned char  ,unsigned char );
void lcdInit(void);
void lcdCmd(unsigned char);
void lcdData(unsigned char);
void lcdWriteNibble(unsigned char);
void waitLcd(unsigned char);
void prints(const rom char * message);
#endif