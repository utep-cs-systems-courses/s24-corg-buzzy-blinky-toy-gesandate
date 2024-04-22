#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "led.h"
//#include "method.c"
#define A 440
#define B 494

#define LED_RED BIT0               // P1.0
#define LED_GREEN BIT6             // P1.6
#define LEDS (LED_RED | LED_GREEN)

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
    
    P1DIR |= LEDS;
    P1OUT &= ~LED_GREEN;
    //P1OUT |= LED_RED;
    P1OUT &= ~LED_RED;
    

    P2REN |= SWITCHES;
    P2IE  |= SWITCHES;
    P2OUT |= SWITCHES;
    P2DIR &= ~SWITCHES;
    
    //buzzer_set_period(0000);
    
    or_sr(0x18);          // CPU off, GIE on
}

//global state variable
int secondCount = 0;

//this is for S1
void __interrupt_vec(WDT_VECTOR) WDT() {

  //inputs start at 2
  //one breaks it
  secondCount++;
  /*
  if (secondCount <= 250){
    secondCount = 0;
    //buzzer_set_period(A);
    P1OUT ^= LED_GREEN;
  }
  */
  
  
  char s2 = P2IN;
  //when switch is pressed
  P1IES |= (s2 & SWITCHES);

  P2IES |= (s2 & SWITCHES);

  //when switch is releeased
  P1IES &= (s2 | ~SWITCHES);

  /*switch (s2){
  case (SW1):
    buzzer_set_period(A);
  
  default:
    buzzer_set_period(0);

    }*/

  //P2IES &= (s2 | ~SWITCH3);
  
  if (s2 & SW1) {
    P1OUT ^= ~LED_RED;
    P1OUT ^= ~LED_GREEN;
    buzzer_set_period(0);
  } else {
    buzzer_set_period(700);
    P1OUT ^+ LED_RED;
    P1OUT ^+ LED_GREEN;
    //P2OUT |= (s2 & SWITCHES);
  
    }
  
  if (s2 & SW2) {
    buzzer_set_period(0);
  } else {
    buzzer_set_period(A);
  }
  /*
  if (s2 | ~SW1) {
    buzzer_set_period(A);
  }
  if (s2 | ~SW3){
    //P1OUT |= LED_RED;
    buzzer_set_period(A);
    //buzzer_set_period(B);
  }
  if (s2 | ~SW2){
    buzzer_set_period(A);
  }
  if (s2 | ~SW4) {
    buzzer_set_period(0);
  }*/

  
}

//this is for S2

/*void __interrupt_vec1(WDT_VECTOR) WDT() {
  //int count = 0;
  
  char p2 = P2IN;

  //when switch is pressed
  P2IES |= (p2 & SWITCHES);
  //when released
  P2IES &= (p2 | ~SWITCHES);
  
  if (p2 & SW2) {
    buzzer_set_period(0000);
  }else{
    buzzer_set_period(B);
  }
}

*/
