/*
 * PUSH_BUTTON.h
 *
 * Created: 7/30/2023 7:23:57 PM
 *  Author: john
 */ 


#ifndef PUSH_BUTTON_H_
#define PUSH_BUTTON_H_

/*
Function name   : Button_vinit
Function return : void
Function Arguments : unsigned char port,unsigned char pin
Function description : this function on;y intialize the pin as it makes sure that the pin a input 
pin not an output pin
*/
void Button_vinit (unsigned char port,unsigned char pin);




/*
Function name   : Button_u8read
Function return : unsigned char 
Function Arguments : unsigned char port,unsigned char pin
Function description : this function read the value on the pin on the pin register for
the specific bit on pinx as x is the port name 
*/
 unsigned char Button_u8read(unsigned char port,unsigned char pin);
 
 
 
/*
Function name   : Button__pull_up_enable
Function return :  unsigned char
Function Arguments : unsigned char port_name,unsigned char pin,unsigned char enable
Function description : this function only activate the internal pull up resistance of a button
*/
void Button__pull_up_enable(unsigned char port_name,unsigned char pin,unsigned char enable);



#endif /* PUSH_BUTTON_H_ */