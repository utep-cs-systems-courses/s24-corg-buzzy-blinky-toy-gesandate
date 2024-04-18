#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
//#include "led.h"
//#include "method.c"
#define A 440
#define B 494

#define SW1 BIT0
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3

#define SWITCH1 SW1
#define SWITCH2 SW2
#define SWITCH3 SW3
#define SWITCH4 SW4

#define SWITCHES (SWITCH1 | SWITCH2 | SWITCH3 | SWITCH4)


int main(void) {
    configureClocks();
 
    buzzer_init();

    int freq = 0;
    int secondCount = 0;
    enableWDTInterrupts();
    //buzzer_set_period(freq);	/* start buzzing!!! 2MHz/1000 = 2kHz*/
    
    P1REN |= SWITCH1;
    P1IE |= SWITCH1;
    P1OUT |= SWITCH1;
    P1DIR &= ~SWITCH1;

    P2REN |= SWITCH2;
    P2IE  |= SWITCH2;
    P2OUT |= SWITCH2;
    P2DIR &= ~SWITCH2;
    
    //buzzer_set_period(0000);
    
    or_sr(0x18);          // CPU off, GIE on
}

//this is for S1
void __interrupt_vec(WDT_VECTOR) WDT() {

  //inputs start at 2
  //one breaks it
  char s1 = P2IN;
  char s2 = P3IN;
  //when switch is pressed
  P1IES |= (s1 & SWITCH2);

  //P2IES |= (s2 & SWITCH3);

  //when switch is releeased
  P1IES &= (s1 | ~SWITCH2);

  //P2IES &= (s2 | ~SWITCH3);
  
  if (s1 & SWITCH1) {
    buzzer_set_period(0000);
  }else{
    buzzer_set_period(A);
  }
}

//this is for S2
void __interrupt_vec1() {
  //int count = 0;
  
  char p2 = P3IN;

  //when switch is pressed
  P2IES |= (p2 & SWITCH4);
  //when released
  P2IES &= (p2 | ~SWITCH4);
  
  if (p2 & SWITCH4) {
    buzzer_set_period(300);
  }else{
    buzzer_set_period(B);
  }
}  

