/*
 * DIO_DRIVER.c
 *
 * Created: 4/20/2023 11:51:14 PM
 *  Author: john
 */
#include "STD_MACROS1.h" 
#include <avr/io.h>
#include "DIO_DRIVER.h"
void DIO_SetPinDir(unsigned char port_name,unsigned char pin,unsigned char dir)
{
	switch (port_name)
	{
		case 'A':
		case 'a':
		if (dir==1)
		{
			set_bit(DDRA,pin);//1 means that this pin is set to be output pin
		}
		else if (dir==0)
		{
			clear_bit(DDRA,pin);//0 means that this pin is set to be input pin
		}
		break ;
		case 'B':
		case 'b':
		if (dir==1)
		{
			set_bit(DDRB,pin);//1 means that this pin is set to be output pin
		}
		else if (dir==0)
		{
			clear_bit(DDRB,pin);//0 means that this pin is set to be input pin
		}
		break ;
		case 'C':
		case 'c':
		if (dir==1)
		{
			set_bit(DDRC,pin);//1 means that this pin is set to be output pin
		}
		else if (dir==0)
		{
			clear_bit(DDRC,pin);//0 means that this pin is set to be input pin
		}
		break ;
		case 'D':
		case 'd':
		if (dir==1)
		{
			set_bit(DDRD,pin);//1 means that this pin is set to be output pin
		}
		else if (dir==0)
		{
			clear_bit(DDRD,pin);//0 means that this pin is set to be input pin
		}
	    break ;
		default:
		
		break ;
	}
	
}

void DIO_Write(unsigned char port_name,unsigned char pin ,unsigned char output_value)
{
	switch (port_name)
	{
		
		case 'A':
		case 'a':
		if (output_value==1)//this is for setting the value of the output of the pin to be HIGH OR 1
		{
			set_bit(PORTA,pin);
		}
		else if (output_value==0)//this is for setting the value of the output of the pin to be LOW or 0
		{
			clear_bit(PORTA,pin);
		}
		break;
		case 'B':
		case 'b':
		if (output_value==1)
		{
			set_bit(PORTB,pin);
		}
		else if (output_value==0)
		{
			clear_bit(PORTB,pin);
		}
		break;
		case 'C':
		case 'c':
		if (output_value==1)
		{
			set_bit(PORTC,pin);
		}
		else if (output_value==0)
		{
			clear_bit(PORTC,pin);
		}
		break;
		case 'D':
		case 'd':
		if (output_value==1)
		{
			set_bit(PORTD,pin);
		}
		else if (output_value==0)
		{
			clear_bit(PORTD,pin);
		}
		break;
	}
}

char DIO_u8read(unsigned char port_name,unsigned char pin_number )
{
    unsigned char return_value =0;
	switch (port_name)
	{
		case 'A':
		case 'a':
		return_value=read_bit(PINA,pin_number);//this is for reading the value in PINA and putting it in return value
		break ;
		case 'B':
		case 'b':
		return_value=read_bit(PINB,pin_number);//Read the value from the given pin in port B
		break ;
		case 'C':
		case 'c':
		return_value=read_bit(PINC,pin_number);//Read the value from the given pin in port c
		break ;
		case 'D':
		case 'd':
		return_value=read_bit(PIND,pin_number);//Read the value from the given pin in port d
		break ;
	}
	return return_value ;
}

void DIO_toggle_portregister (unsigned char port_name,unsigned char pin_number)
{
	switch (port_name) 
	{
		case 'A':
		case 'a':
		toggle_bit(PORTA,pin_number);
		break ;
		case 'B':
		case 'b':
		toggle_bit(PORTB,pin_number);
		break ;
		case 'C':
		case 'c':
		toggle_bit(PORTC,pin_number);
		break ;
		case 'D':
		case 'd':
		toggle_bit(PORTD,pin_number);
		break ;
	}	
}

void DIO_Set_Port_Direction(unsigned char port_name,unsigned char direction)
{
	switch (port_name)
	{
		case 'A':
		case 'a':
		DDRA=direction;
		break;
		case 'B':
		case 'b':
		DDRB=direction;
		break;
		case 'C':
		case 'c':
		DDRC=direction;
		break;
		case 'D':
		case 'd':
		DDRD=direction;
		break;
		default:
		break;
		}
}

void DIO_Write_Port(unsigned char port_name,unsigned char value_in_port)
{
	switch (port_name) 
	{
		case 'A':
		case 'a':
		PORTA=value_in_port;
		break;
		case 'B':
		case 'b':
		PORTB=value_in_port;
		break;
		case 'C':
		case 'c':
		PORTC=value_in_port;
		break;
		case 'D':
		case 'd':
		PORTD=value_in_port;
		break;		
	}
	
}

unsigned char DIO_read_port(unsigned char port_name)
{
	unsigned char return_value=0;
	switch (port_name)
	{
	case 'A':
	case 'a':
	return_value=PINA;
	break;
	case 'B':
	case 'b':
	return_value=PINB;
	break;
	case 'C':
	case 'c':
	return_value=PINC;
	break;
	case 'D':
	case 'd':
	return_value=PIND;
	break;	
	}
	return return_value;
}

		{
			set_bit(PORTA,pin);
		}
		{
			set_bit(PORTB,pin);
		}
		{
			set_bit(PORTC,pin);
		}
		{
			set_bit(PORTD,pin);
		}