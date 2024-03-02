/*
 * LED_DRIVER.c
 *
 * Created: 7/30/2023 2:13:07 PM
 *  Author: john
 */ 
#include "DIO_DRIVER.h"

void Led_vinit(unsigned char port,unsigned char pin)
{
	DIO_SetPinDir(port,pin,1);
}

void Led_von(unsigned char port,unsigned char pin)
{
	DIO_Write(port,pin,1);
}

void Led_voff(unsigned char port,unsigned char pin)
{
	DIO_Write(port,pin,0);
}
void Led_vtoggle(unsigned char port,unsigned char pin)
{
	DIO_toggle_portregister(port,pin);
}

unsigned char Led_u8read_state(unsigned char port,unsigned pin)
{
	char return_value=0;
	return_value=DIO_u8read(port,pin);
	return return_value;
}



void Led_vend(unsigned char port,unsigned char pin)
{
	DIO_SetPinDir(port,pin,0);
}


