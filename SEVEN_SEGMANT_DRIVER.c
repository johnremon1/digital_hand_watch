/*
 * SEVEN_SEGMANT_DRIVER.c
 *
 * Created: 8/2/2023 9:06:27 PM
 *  Author: johnr
 */ 

#include "DIO_DRIVER.h"
#include "STD_MACROS1.h"



void Sevensegmant_vinit(unsigned char port_name)
{
	for (unsigned char i=0;i<=6;i++)
	{
		DIO_SetPinDir(port_name,i,1);
	}
}


void Sevensegmant_com_cath_vwrite(unsigned char port_name,unsigned char number)
{
	char arr_number[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6D,0x7D,0x07,0xff,0x6f};

		DIO_Write_Port(port_name,arr_number[number]);		
	
}

void Sevensegmant_com_cath_vwrite_word_timer(unsigned char port_name,unsigned char number)
{

	switch (number)
	{
	 case ('T') :
	 DIO_Write_Port(port_name,0X78);
	 break;
	 case ('I') :
	 DIO_Write_Port(port_name,0X06);
	 break;
	 case ('N') :
	 DIO_Write_Port(port_name,0X37);
	 break;
	 case ('E') :
	 DIO_Write_Port(port_name,0X79);
	 break;
	 case ('R') :
	 DIO_Write_Port(port_name,0X31);
	 break;  
	 case ('S') :
	 DIO_Write_Port(port_name,0X6D);
	 break; 
	 case ('O') :
	 DIO_Write_Port(port_name,0X3F);
	 break; 
	 case ('P') :
	 DIO_Write_Port(port_name,0X73);
	 break; 
	 case ('U') :
	 DIO_Write_Port(port_name,0X3E);
	 break; 
	 case ('A') :
	 DIO_Write_Port(port_name,0X77);
	 break; 
	 case ('C') :
	 DIO_Write_Port(port_name,0X39);
	 break;
	 case ('H') :
	 DIO_Write_Port(port_name,0X74);
	 break;  
	}



}




void Sevensemgant_com_anod_vinit(unsigned char port_name)
{
	for (unsigned char i=0;i<=6;i++)
	{
		DIO_SetPinDir(port_name,i,1);
		DIO_Write(port_name,i,1);
	}
}



void Sevensegmant_com_anod_vwrite(unsigned char port_name,unsigned char number)
{
char arr_number[10]={0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10};

DIO_Write_Port(port_name,arr_number[number]);

}

void Seven_Seg_bcd_init(unsigned char port_name,unsigned char pins[4])
{
	DIO_SetPinDir(port_name,pins[0],1);
	DIO_SetPinDir(port_name,pins[1],1);
	DIO_SetPinDir(port_name,pins[2],1);
	DIO_SetPinDir(port_name,pins[3],1);
	
}

void Seven_Seg_bcd_write(unsigned char port_name,unsigned char pins[4],unsigned char number)
{
	DIO_Write(port_name,pins[0],read_bit(number,0));
	DIO_Write(port_name,pins[1],read_bit(number,1));
	DIO_Write(port_name,pins[2],read_bit(number,2));
	DIO_Write(port_name,pins[3],read_bit(number,3));
}