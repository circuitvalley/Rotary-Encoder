#include "lcd16.h"

void lcdCmd(unsigned char Data)
{

EN=0;
PORTD =((Data >> 4) & 0x0F);
RS=0; //because sending command
EN=1;
waitLcd(2);

EN=0;
PORTD  = (Data & 0x0F);
EN =1;
waitLcd(2);
EN=0;


}


void lcdData(unsigned char l)
{
EN=0;
PORTD =((l >> 4) & 0x0F);
RS=1;  //because sending data
EN=1;
waitLcd(2);
EN=0;

PORTD  = (l & 0x0F);
RS=1;  //because sending data
EN=1;
waitLcd(2);
EN=0;



}

void lcdInit(void)
{
RS=0;
EN=0;
PORTD= 0x3;
waitLcd(40);
EN=1;
EN=0;
waitLcd(5);
EN=1;
EN=0;
waitLcd(5);
EN=1;
EN=0;
waitLcd(2);
PORTD=2;
EN=1;
EN=0;
lcdCmd(0x28);   //set data length 4 bit 2 line
waitLcd(250); 
lcdCmd(0x0E);   // set display on cursor on blink on
waitLcd(250);
lcdCmd(0x01); // clear lcd 
waitLcd(250);
lcdCmd(0x06);  // cursor shift direction
waitLcd(250);
lcdCmd(0x80);  //set ram address
waitLcd(250);
}

void waitLcd(unsigned char x)
{
unsigned char i;
for (x ;x>1;x--)
{
for (i=0;i<=110;i++);
}
}



//gotoXy(column, row);
void gotoXy(unsigned char  x,unsigned char y)
{
 if(x<40)
 {
  if(y) x|=0b01000000;
  x|=0b10000000;
  lcdCmd(x);
  }
}





void prints(const rom char * message){	// Write message to LCD (C string type)
lcdCmd(0x8); // disable display;
		while (*message){			// Look for end of string
					lcdData(*message++);
					}
	lcdCmd(0xE); // enable display;
	}






void clearLcd(void)
{
	//	Send command to LCD (0x01)
	lcdCmd(0x01);	
}

void numToLcd(unsigned char num)
{
	
	lcdData((num/100)+0x30);
	lcdData(((num/10)%10)+0x30);
	lcdData((num%10)+0x30);
	
}