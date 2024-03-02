/*
 * LED_DRIVER.h
 *
 * Created: 7/30/2023 2:13:25 PM
 *  Author: johnr
 */ 


#ifndef LED_DRIVER_H_
#define LED_DRIVER_H_

/*
Function name   : Led_vinit
Function return : void
Function Arguments : unsigned char port,unsigned char pin
Function describtion :this function make the port the led on is an output pin so we can write 1 or 0 in the following 
function 
*/
void Led_vinit(unsigned char port,unsigned char pin);


/*
Function name   : Led_von 
Function return : void
Function Arguments : unsigned char port,unsigned char pin
Function description :this function write 1 on the chosen pin in the chosen port and 
make the led turn on 
*/
void Led_von(unsigned char port,unsigned char pin);



/*
Function name   : Led_voff
Function return : void
Function Arguments : unsigned char port.,unsigned char pin
Function description :this function write 0 on the chosen pin in the chosen port and make 
the led turn off 
*/
void Led_voff(unsigned char port,unsigned char pin);



/*
Function name   : Led_vtoggle
Function return : void
Function Arguments : unsigned char port_name,unsigned char pin
Function description : this function toggle the chosen bit in the chosen port in the chosen pin
and toggle 
*/
void Led_vtoggle(unsigned char port,unsigned char pin);

/*
Function name   :Led_u8read_state
Function return : unsigned char
Function Arguments : unsigned char port_name,unsigned char pin
Function description :this function read if the led is on or off and then send 1 if the led 
is on and the send 0 if the led was off
*/
unsigned char Led_u8read_state(unsigned char port,unsigned pin);


/*
Function name   : Led_vend
Function return : void
Function Arguments : unsigned char port_name,unsigned char pin
Function description : this function return every thing as it was before coneccting the led 
so the port became input not output
*/
void Led_vend(unsigned char port,unsigned char pin);


#endif /* LED_DRIVER_H_ */