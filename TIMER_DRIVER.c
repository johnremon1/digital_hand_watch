/*
 * TIMER_DRIVER.c
 *
 * Created: 9/7/2023 3:51:02 PM
 *  Author: johnr
 */ 

#include "TIMER_DRIVER.h"
#include "STD_MACROS1.h"
#include <avr/io.h>
#include <AVR/interrupt.h>

void Timer0_overflow_interrupt_mood()
{
	clear_bit(TCCR0,WGM00);
	clear_bit(TCCR0,WGM01);
	
	//choosing the clock the timer will be on
	set_bit(TCCR0,CS00);//clock set to be system clock over 1024
	clear_bit(TCCR0,CS01);
	set_bit(TCCR0,CS02);
	
	//now we activate the register needed for interrupt activation
	sei();
	set_bit(TIMSK,TOIE0);
}

void Timer0_CTC_interrupt_mood(void)
{
	//choosing the mode we want and it is the CTC mood (clear timer on compare match)
	set_bit(TCCR0,WGM01);
	
	//choosing the clock the timer will be on
	set_bit(TCCR0,CS00);
	clear_bit(TCCR0,CS01);
	set_bit(TCCR0,CS02);
	
	//choosing the number in the OCR0 
	OCR0=7;
	/*
	why 80 because our system clock is 8 mhz so to achieve 10 ms every compare match you must divide the 
	10 ms on the tick time which is 1024/8*10^6 which gives us aproximate number of 80 in the end of calculations
	*/
	
	//now we activate the register needed for interrupt activation
	sei();
	set_bit(TIMSK,OCIE0);
}

void Timer0_ctc_oc0_enbale(unsigned char ocr0_value)
{
	DIO_SetPinDir('B',3,1);
	//choosing the mode we want and it is the CTC mood (clear timer on compare match)
	set_bit(TCCR0,WGM01);
	clear_bit(TCCR0,WGM00);
	
	//choosing the clock the timer will be on 
	set_bit(TCCR0,CS00);
	clear_bit(TCCR0,CS01);
	set_bit(TCCR0,CS02);
	
	//choosing the number in the OCR0 
	OCR0=ocr0_value;
  
   //now we need to activate the oc0 pin and we will do that by changing the value in COM 0:1
   set_bit(TCCR0,COM00);
   clear_bit(TCCR0,COM01);
   //we made that every time the a compare match happens the oc0 toggle 
   /*
   com(0:1) 00 normal operation oc0 is not connected 
   com(0:1) 10 toggle the oc0 every compare match 
   com(0:1) 01 clear the oc0 every compare match 
   com(0:1) 11 set the oc0 every compare match 
   */    
}

void Timer0_fastpwm_mood(unsigned char ocr0_value)
{
	DIO_SetPinDir('B',3,1);
	
	//first we need to choose the mood of the timer 
	set_bit(TCCR0,WGM00);
	set_bit(TCCR0,WGM01);
	
	//then we need to choose the clock the timer will operate on 
	set_bit(TCCR0,CS00);
	clear_bit(TCCR0,CS01);
	set_bit(TCCR0,CS02);
	//we choose that the clock of the microcontroller will be the system clock divided by the prescalor 1024(adjuctable)
	
	OCR0=ocr0_value;//now we put the value you choose on the ocr0
	
	//now we need to choose the action that will happen on the ocr0 when the a compare match happens 
	clear_bit(TCCR0,COM00);
	set_bit(TCCR0,COM01);
    /*
      com(1:0) 00 normal operation oc0 is not connected 
      com(1:0) 01 reserved
      com(1:0) 10 clear the oc0 every compare match and set the oc0 every overflow (non inverting mood) bigger ocr0 value bigger duty cycle
      com(1:0) 11 set the oc0 every compare match and clear the oc0 every overflow (inverting mood ) bigger oc0 value smaller duty cycle
   */ 
	
	
}

void Timer0_phasecorresct_mood(unsigned char ocr0_value)
{
	DIO_SetPinDir('B',3,1);
	
	//first we need to choose the mood of the timer 
	set_bit(TCCR0,WGM00);
	clear_bit(TCCR0,WGM01);
	
	//then we need to choose the clock the timer will operate on 
	set_bit(TCCR0,CS00);
	clear_bit(TCCR0,CS01);
	set_bit(TCCR0,CS02);
	//we choose that the clock of the micro controller will be the system clock divided by the prescalor 1024(adjustable)
	
	OCR0=ocr0_value;//now we put the value you choose on the ocr0
	
	//now we need to choose the action that will happen on the ocr0 when the a compare match happens 
	clear_bit(TCCR0,COM00);
	set_bit(TCCR0,COM01);
    /*
      com(1:0) 00 normal operation oc0 is not connected 
      com(1:0) 01 reserved
      com(1:0) 10 clear the oc0 every compare match when up counting and set the oc0 in compare match when down counting
      com(1:0) 11 set the oc0 every compare match when up counting and clear the oc0 in compare match when down counting
	     */ 
	
}









void Timer2_overflow_interrupt_mood()
{
	clear_bit(TCCR2,WGM20);
	clear_bit(TCCR2,WGM21);
	
	//choosing the clock the timer will be on
	set_bit(TCCR2,CS20);//clock set to be system clock over 1024
	set_bit(TCCR2,CS21);
	set_bit(TCCR2,CS22);
	
	//now we activate the register needed for interrupt activation
	sei();
	set_bit(TIMSK,TOIE2);
}

void Timer2_CTC_interrupt_mood(void)
{
	//choosing the mode we want and it is the CTC mood (clear timer on compare match)
	clear_bit(TCCR2,WGM20);
	set_bit(TCCR2,WGM21);
	
	//choosing the clock the timer will be on
	set_bit(TCCR2,CS20);
	set_bit(TCCR2,CS21);
	set_bit(TCCR2,CS22);
	
	//choosing the number in the OCR0 
	OCR2=80;
	/*
	why 80 because our system clock is 8 mhz so to achieve 10 ms every compare match you must divide the 
	10 ms on the tick time which is 1024/8*10^6 which gives us aproximate number of 80 in the end of calculations
	*/
	
	//now we activate the register needed for interrupt activation
	sei();
	set_bit(TIMSK,OCIE2);
}

void Timer2_ctc_oc0_enbale(unsigned char ocr0_value)
{
	DIO_SetPinDir('D',7,1);
	//choosing the mode we want and it is the CTC mood (clear timer on compare match)
	set_bit(TCCR2,WGM21);
	clear_bit(TCCR2,WGM20);
	
	//choosing the clock the timer will be on 
	set_bit(TCCR2,CS20);
	set_bit(TCCR2,CS21);
	set_bit(TCCR2,CS22);
	
	//choosing the number in the OCR0 
	OCR2=ocr0_value;
  
   //now we need to activate the oc0 pin and we will do that by changing the value in COM 0:1
   set_bit(TCCR2,COM20);
   clear_bit(TCCR2,COM21);
   //we made that every time the a compare match happens the oc0 toggle 
   /*
   com(0:1) 00 normal operation oc0 is not connected 
   com(0:1) 10 toggle the oc0 every compare match 
   com(0:1) 01 clear the oc0 every compare match 
   com(0:1) 11 set the oc0 every compare match 
   */    
}

void Timer2_fastpwm_mood(unsigned char ocr0_value)
{
	DIO_SetPinDir('D',7,1);
	
	//first we need to choose the mood of the timer 
	set_bit(TCCR2,WGM20);
	set_bit(TCCR2,WGM21);
	
	//then we need to choose the clock the timer will operate on 
	set_bit(TCCR2,CS20);
	set_bit(TCCR2,CS21);
	set_bit(TCCR2,CS22);
	//we choose that the clock of the microcontroller will be the system clock divided by the prescalor 1024(adjuctable)
	
	OCR2=ocr0_value;//now we put the value you choose on the ocr0
	
	//now we need to choose the action that will happen on the ocr0 when the a compare match happens 
	clear_bit(TCCR0,COM00);
	set_bit(TCCR0,COM01);
    /*
      com(1:0) 00 normal operation oc0 is not connected 
      com(1:0) 01 reserved
      com(1:0) 10 clear the oc0 every compare match and set the oc0 every overflow (non inverting mood) bigger ocr0 value bigger duty cycle
      com(1:0) 11 set the oc0 every compare match and clear the oc0 every overflow (inverting mood ) bigger oc0 value smaller duty cycle
   */ 
	
	
}

void Timer2_phasecorresct_mood(unsigned char ocr0_value)
{
	DIO_SetPinDir('D',7,1);
	
	//first we need to choose the mood of the timer 
	set_bit(TCCR2,WGM20);
	clear_bit(TCCR2,WGM21);
	
	//then we need to choose the clock the timer will operate on 
	set_bit(TCCR2,CS20);
	set_bit(TCCR2,CS21);
	set_bit(TCCR2,CS22);
	//we choose that the clock of the micro controller will be the system clock divided by the prescalor 1024(adjustable)
	
	OCR2=ocr0_value;//now we put the value you choose on the ocr0
	
	//now we need to choose the action that will happen on the ocr0 when the a compare match happens 
	clear_bit(TCCR2,COM20);
	set_bit(TCCR2,COM21);
    /*
      com(1:0) 00 normal operation oc0 is not connected 
      com(1:0) 01 reserved
      com(1:0) 10 clear the oc0 every compare match when up counting and set the oc0 in compare match when down counting
      com(1:0) 11 set the oc0 every compare match when up counting and clear the oc0 in compare match when down counting
	     */ 
}

void Timer2_real_time_project()//note that you must connect the TOSC2 AND TOSC1  to a crystal of 32.768 so that the processor will go to the isr every second
{
	set_bit(ASSR,AS2);
	
	clear_bit(TCCR2,WGM20);
	clear_bit(TCCR2,WGM21);
	
	//choosing the clock the timer will be on
	set_bit(TCCR2,CS20);//clock set to be system clock over 124
	clear_bit(TCCR2,CS21);
	set_bit(TCCR2,CS22);
	
	//now we activate the register needed for interrupt activation
	sei();
	set_bit(TIMSK,TOIE2);

} 


