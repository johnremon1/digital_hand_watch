/*
 * PUSH_BUTTON.c
 *
 * Created: 7/30/2023 7:18:56 PM
 *  Author: john
 */ 
#include "DIO_DRIVER.h"

void Button_vinit (unsigned char port,unsigned char pin)
{
	DIO_SetPinDir(port,pin,0);
}
 unsigned char Button_u8read(unsigned char port,unsigned char pin)
 {
	unsigned char return_value=0;
	return_value=DIO_u8read(port,pin);
	return return_value;
 }
 
void Button__pull_up_enable(unsigned char port_name,unsigned char pin,unsigned char enable)
 {
	 DIO_enable_pull_up(port_name,pin,enable);
 }