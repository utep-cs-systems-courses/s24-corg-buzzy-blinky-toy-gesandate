#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
//#include "method.c"
#define NOTE_A 440
#define NOTE_B 494

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
    
    //buzzer_set_period(0000);
    
    or_sr(0x18);          // CPU off, GIE on
}

void __interrupt_vec(WDT_VECTOR) WDT() {

  char p1 = P2IN;
  char p2 = P3IN;
  //char p3 = P4IN;

  //when switch is pressed
  P1IES |= (p1 & SWITCH2);
  //when switch is releeased
  P1IES &= (p1 | ~SWITCH2);  
  
  if (p1 & SWITCH1) {
    buzzer_set_period(0000);
  }else{
    buzzer_set_period(NOTE_A);
  }
  /*
  if (p2 & SWITCH2) {
    buzzer_set_period(0000);
  }else{
    buzzer_set_period(NOTE_B);
  }*/
  //buzzer_set_period(3000);

}
