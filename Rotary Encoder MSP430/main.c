/*
 * main.c
 */

#include <msp430g2211.h>
// Timer A0 interrupt service routine
#define REA BIT1
#define REB BIT3

unsigned char count;
void hand()
{
	static unsigned char oldstate;
	unsigned char port,state;
		if(P1IFG & 0x0A){
			__delay_cycles(6000);


			port = P1IN;

			state= (port & REB)>>3 | (port & REA);

			if(state==0x3){
			if(oldstate ==0x1)
				{
					count++;
					P1OUT ^=BIT0 ;
				}else if(oldstate == 0x2)
				{

					count--;
					P1OUT ^=BIT6 ;
				}
			}
			oldstate = state;




		}
		__delay_cycles(6000);
			P1IFG = 0x00;


	}

#pragma vector = PORT1_VECTOR
__interrupt void p1ch (void)
{
			P1OUT &= ~BIT5;

		hand();
		P1OUT |= BIT5;
}

#pragma vector = PORT2_VECTOR, TIMERA1_VECTOR,TIMERA0_VECTOR, NMI_VECTOR, WDT_VECTOR
__interrupt void Trap_ISR(void)
{
  while(1);
}

void InitializeClocks(void);
void main(void) {
	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
	P1SEL = 0x00;
	P1DIR = 0xE5;				//P1,P3,P4 input reset out
	P1REN = 0xA;
	P1IE = 0xA;
	P1IES = 0x00;
	P1OUT = 0x0B;
	InitializeClocks();

	__enable_interrupt();
	//__bis_SR_register(GIE);
	while(1)
	{

	}
	
}

void InitializeClocks(void)
{

  BCSCTL1 = RSEL0 +RSEL1+RSEL2+RSEL3;                    // Set range
  DCOCTL = DCO0+DCO1 + MOD0+MOD1+MOD2+MOD4;	//tune to  F Average = 16Mhz
  BCSCTL2 = SELM_0 ;

}
