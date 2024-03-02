/*
 * DIO_DRIVER.h
 *
 * Created: 4/21/2023 12:12:05 AM
 *  Author: johnr
 */ 


#ifndef DIO_DRIVER_H_
#define DIO_DRIVER_H_

/*
Function name   : DIO_SetPinDir
Function return : void
Function Arguments : unsigned char port_name,unsigned char pin,unsigned char dir
Function describtion : this function recieves the port name and the pin number and the direction of the pin 
and then the function set the direction of the pin in the bit of the pin in the DDRx which x could be (A,B,C,D)
the direcrtion of the pin should bs ( 1 if the pin is output or 0 if the pin is input   
*/
void DIO_SetPinDir(unsigned char port_name,unsigned char pin,unsigned char dir);



/*
Function name   : DIO_Write
Function return : void
Function Arguments : unsigned char port_name,unsigned char pin,unsigned char output_value (1 or 0 )
Function description : this function recieves the port name and the pin number and the output value of the pin
and then the function set the output value of the pin in the bit of the pin in the PORTx which x could be (A,B,C,D)
the output value of the pin should be ( 1 or 0 )
*/
void DIO_Write(unsigned char port_name,unsigned char pin ,unsigned char output_value);



/*
Function name   : DIO_u8read
Function return : char and called in the function return_value
Function Arguments : unsigned char port_name,unsigned char pin_number
Function description : this function recieves the port name and the pin number and then read the value in PINx register 
of the pin and the return value is (1 or 0)
*/
char DIO_u8read(unsigned char port_name,unsigned char pin_number );



/*
Function name   : DIO_toggle_portregister
Function return : void
Function Arguments : unsigned char port_name,unsigned char pin_number
Function description : this function recieves the port name and the pin number and toggle the chosen bit in PORTX register 
*/
void DIO_toggle_portregister (unsigned char port_name,unsigned char pin_number);



/*
Function name   : DIO_Set_Port_Direction 
Function return : void
Function Arguments : unsigned char port_name,unsigned char direction as 8 bit number or 2 digit hexadesimal number 
Function description : this function set the direction of all bits in the register in one time you should only send the value you want the 
register to store
*/
void DIO_Set_Port_Direction(unsigned char port_name,unsigned char direction);



/*
Function name   : DIO_Write_Port
Function return : void
Function Arguments : unsigned char port_name,unsigned char value_in_port as 8 bit number or 2 digit hexadesimal number
Function description : this function set the value of all bits in the register in one time you should only send the value you want the
register to store
*/
void DIO_Write_Port(unsigned char port_name,unsigned char value_in_port);



/*
Function name   : DIO_read_Port
Function return : unsigned char
Function Arguments : unsigned char port_name
Function description : this function read the 8 bit value in PINX register and return it as an unsigned char 
*/
unsigned char DIO_read_port(unsigned char port_name);



/*
Function name   : DIO_enable_pull_up
Function return :  void
Function Arguments : unsigned char port_name,unsigned char pin,unsigned char enable
Function description : this function enable or dienable the internal pull up on the specific pin you chose
if you chose 1 on the enable the pull up will be activated if you put 0 on the enable the internal pull up will not be activated
*/
void DIO_enable_pull_up(unsigned char port_name,unsigned char pin,unsigned char enable);





/*
Function name   : DIO_Write_low_nibble
Function return :  void
Function Arguments : unsigned char port_name,unsigned char number 
Function description :this function write the first four bits from the number you sent on the first four pins from the port you sent 
*/
void DIO_Write_low_nibble(unsigned char port_name,unsigned char number);


/*
Function name   : DIO_Write_high_nibble
Function return :  void
Function Arguments : unsigned char port_name,unsigned char number
Function description :this function write the first four bits from the number you sent on the last four pins from the port you sent
*/
void DIO_Write_high_nibble(unsigned char port_name,unsigned char number);
#endif /* DIO_DRIVER_H_ */