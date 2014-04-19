/* 
 * File:   main.c
 * Author: Gaurav
 *
 * Created on September 2, 2013, 11:49 PM
 */
#pragma config OSC = HS, OSCS = OFF				//configuration settings 
#pragma config PWRT= OFF , BOR=OFF, BORV = 27
#pragma config WDT = OFF
#pragma config LVP =OFF , STVR =OFF

#include <p18f458.h> 
#include "lcd16.h"	//includes the lcd routines header file, the rotary encoder is not dependent on this but in this demo required to display.
#include <delays.h> //C18 compiler delay routine header file  
/*
 * 
 */


#define REA LATBbits.LATB4 	// Rotary encoder pin definition
#define REB LATBbits.LATB5


void pbchange(void);		//portb change routine this routine is being called by the interrrupt serivice routine on portb change interrupts
void callISR(void);			

#pragma code highPI = 0x008	// to put the code on Interrupt Vector 
void highPI(void)
{
_asm 
goto callISR
 _endasm
}
#pragma code 

#pragma interrupt callISR	//checks which one of the interrupt is occured
void callISR(void)
{

 if(INTCONbits.RBIF==1)		//check for PortB change interrupt
	{
       pbchange();			//call the routine
	}

}

unsigned char count;		//this variable will incremented or decremented on encoder rotation
void main() {
   
	TRISD = 0x00;			// set the PORTD to output 
	TRISC = 0x00;			// set the PORTC to output
    TRISBbits.TRISB4=1;		// set rotary encoder pins to input
	TRISBbits.TRISB5=1;
	lcdInit();				// inilized the LCD
	prints("Count = ");   	
	numToLcd(count);		// display count to lcd
	INTCON2bits.RBPU  =0; 	// enable pullups 
	INTCONbits.RBIF = 0;	// clear the interrupt flag 
	INTCONbits.RBIE = 1;	// enable PORTB change interrupt
    INTCONbits.GIE  = 1;	// enable the global interrupt
while(1)
{

}

}





void pbchange(void )
{
	unsigned char state;
	static unsigned char oldstate;  // this variable need to be static as it has to retain the value between calls 
	Delay1KTCYx(5); 				//	delay for 1ms here for debounce 
	state= REB<<1 | REA;			//  combine the pin status and assign to state variable 
	if(oldstate==0x0){				
	if( state ==0x1)
		{
			count--;				//decrement the count 
			gotoXy(8,0);			//goto proper position on the LCD screen
			numToLcd(count);		//display the count value on to LCD
		}else if( state == 0x2)
		{
			
			count++;				//decrement the count 
			gotoXy(8,0);			//goto proper position on the LCD screen
			numToLcd(count);		//display the count value on to LCD
		}
		
	}	
	oldstate = state;				// store the current state value to oldstate value this value will be used in next call					

	PORTB = PORTB;					// read or Any read or write of PORTB,This will end the mismatch condition
	INTCONbits.RBIF = 0; 			// clear the porb change intrrupt flag 
}

