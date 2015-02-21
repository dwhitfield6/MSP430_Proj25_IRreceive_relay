#include "msp430.h"

#define LED0 BIT6
#define LED1 BIT0
#define relay1 BIT5
#define relay2 BIT0
#define IRrec BIT1
#define IRrec1 BIT2

int bit =0;
int bitt =0;
int count =0;
int resetcount =0;
int loopcount=0;
int loopcountMAX=0;
int one =0;
int two=0;
int three =0;
int four=0;
int five=0;
int six=0;
int seven=0;
int eight =0;
int ledcount =0;
int odd=0;
unsigned long realdata =0;
unsigned long rxdata =0;



void main(void){

  WDTCTL = WDTPW + WDTHOLD;                            // Stop watchdog timer

  P1DIR |= (LED1 + LED0);                            // Set all pins but RXD to output
  P1OUT =0;
  P2DIR |= relay1 + relay2;
  P2IE |= IRrec; // P1.3 interrupt enabled
  P2IES &= ~IRrec; // P1.3 interrupt enabled
  P2IFG &= ~IRrec; // P1.3 IFG cleared
  P2IE |= IRrec1; // P1.3 interrupt enabled
  P2IES |= IRrec1; // P1.3 interrupt enabled
  P2IFG &= ~IRrec1; // P1.3 IFG cleared

  TA0CCTL0 |= CCIE;                             // CCR0 interrupt enabled
  TA0CTL = TASSEL_2 + MC_1 + ID_2;           // SMCLK/8, upmode
  TA0CCR0 =  20;



  __enable_interrupt(); // enable all interrupts                                   // Enable CPU interrupts



  while(1)
  {
        _delay_cycles(100);

        if(resetcount == 200)
        {
          loopcountMAX=loopcount;
          loopcount =0;
          realdata = rxdata >> 1;

        }
        if(realdata != 0) //gun 1 code
            {
              P1OUT |=LED1;
              P1OUT &=~LED0;
              ledcount=0;
            }
        if(realdata == 0xFF17943) //gun 1 code
        {
            P2OUT ^=relay1;
          realdata =0;
        }
        else if(realdata == 0xFF46731) //gun 2 code
        {
            P2OUT ^=relay2;
          realdata =0;
        }
        else if(realdata == 0xFF9992) //gun 2 code
        {
        	P2OUT ^=relay1;
          realdata =0;
        }
        else if(realdata == 0xFF9912) //gun 2 code
        {
        	P2OUT ^=relay2;
          realdata =0;
        }
        else
        {
        	realdata =0;
        }
        if(ledcount ==2000)
        {
            P1OUT |=LED0;
            P1OUT &=~LED1;
        }
        if(ledcount == 4000)
        {
            P1OUT &=~LED0;
            P1OUT &=~LED1;
        }
ledcount++;
if(ledcount >5000)
{
    ledcount =5000;
}
                resetcount++;
            if(resetcount >1000)
            {
              resetcount =999;
            }
            if(count >1000)
            {
              count =999;
            }

  }
}




#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
  TA0CTL |= TACLR;

  if(loopcount == 0)
  {
    rxdata =0;
  }
  if (loopcount == 50)
  {
    one = count;
  }
  else if (loopcount ==51)
  {
    two = count;
  }
  else if(loopcount ==52)
  {
    three = count;
  }
  else if(loopcount ==53)
  {
    four = count;
  }
  else if(loopcount == 54)
  {
    five = count;

  }
  else if(loopcount == 55)
  {
    six = count;

  }
  else if(loopcount == 56)
  {
    seven = count;

  }
  else if(loopcount == 57)
  {
    eight = count;

  }

  odd = (loopcount & 0x1);
  if(odd == 0)
  {
        if(count >13 && count < 24)
            {
                bit = 1;
            }
        else
        {
            bit = 0;
        }

                rxdata += bit;
                rxdata<<=1;
  }

loopcount++;
  count=0;
  resetcount=0;
  P2IFG &= ~IRrec; // P1.3 IFG cleared
  P2IFG &= ~IRrec1; // P1.3 IFG cleared
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0 (void)
{
  count++;
}
