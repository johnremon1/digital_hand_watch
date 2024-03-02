/*
 * INTERRUPT_DRIVER.c
 *
 * Created: 10/6/2023 12:44:39 AM
 *  Author: johnr
 */ 

#include "INTERRUPT_DRIVER.h"

void INT0_enable()
{
  sei();
  DIO_SetPinDir('D',2,0);
  set_bit(GICR,INT0);
  
  
  set_bit(MCUCR,ISC00);//this is for making the int happens with rising edge (adjustable)
  set_bit(MCUCR,ISC01);
 /*
 you can control it by 
 ISC0 (1:0) 00 for low level
 ISC0 (1:0) 01 for any change
 ISC0 (1:0) 10 for falling edge
 ISC0 (1:0) 11 for rising edge	
 */
}

void INT1_enable()
{
  sei();
  DIO_SetPinDir('D',3,0);
  set_bit(GICR,INT1);
  
  
  set_bit(MCUCR,ISC10);//this is for making the int happens with rising edge (adjustable)
  set_bit(MCUCR,ISC11);
 /*
 you can control it by 
 ISC1 (1:0) 00 for low level
 ISC1 (1:0) 01 for any change
 ISC1 (1:0) 10 for falling edge
 ISC1 (1:0) 11 for rising edge	
 */
}
INT1_disenable()
{
	clear_bit(GICR,INT1);
}

void INT2_enable()
{
  sei();
  DIO_SetPinDir('B',2,0);
  set_bit(GICR,INT2);
  
   set_bit(MCUCSR,ISC2);//making the int2 happens with the rising edge 
   /*
   ISC2 0 FOR falling edge
   ISC2 1 FOR rising edge
   */
}