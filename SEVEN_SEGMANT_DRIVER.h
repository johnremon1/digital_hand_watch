/*
 * SEVEN_SEGMANT_DRIVER.h
 *
 * Created: 8/2/2023 9:36:55 PM
 *  Author: johnr
 */ 


#ifndef SEVEN_SEGMANT_DRIVER_H_
#define SEVEN_SEGMANT_DRIVER_H_


/*
Function name   : Sevensemgant_vinit
Function return : void
Function Arguments : unsigned char port_name
Function description : this function set all the pins in the array as output pins for the seven segmant and the pins must be of 7 elements as follows 
1 for a ,2 for b ,3 for c ,4 for d ,5 for e ,6 for f,7 for g
*/
void Sevensegmant_vinit(unsigned char port_name);



/*
Function name   : Sevensegmant_com_cath_vwrite
Function return : void
Function Arguments : unsigned char port_name
Function description : this function write on all the pins in the array  for the seven segment and the array must be of 7 elements as follows
1 for a ,2 for b ,3 for c ,4 for d ,5 for e ,6 for f,7 for g
and you write the number you want to be on the seven segment in the char variable number
important note pin 6 for f and pin 7 for g not the opposite as it is inverted on the hardware on most of the seven segments so be alerted
note this function only for common cathode seven segment 
*/
void Sevensegmant_com_cath_vwrite(unsigned char port_name,unsigned char number);



/*
Function name   : Sevensegmant_com_anod_vwrite
Function return : void
Function Arguments : unsigned char port_name
Function description : this function write on all the pins in the array  for the seven segment and the array must be of 7 elements as follows
1 for a ,2 for b ,3 for c ,4 for d ,5 for e ,6 for f,7 for g
and you write the number you want to be on the seven segment in the char variable number
important note pin 6 for f and pin 7 for g not the opposite as it is inverted on the hardware on most of the seven segments so be alerted
note this function only for common anode seven segment
*/
void Sevensegmant_com_anod_vwrite( unsigned char port_name,unsigned char number);



/*
Function name   : Seven_Seg_bcd_init
Function return : void
Function Arguments : unsigned char port_name,unsigned char pins[4]
Function description : this function recieves the four pins used for the seven segment on an array of four pins and make them output pins
*/
void Seven_Seg_bcd_init(unsigned char port_name,unsigned char pins[4]);

/*
Function name   : Seven_Seg_bcd_write
Function return : void
Function Arguments : unsigned char port_name,unsigned char pins[4],unsigned char number
Function description : this function recieves the pins used for the seven segment on an array of four pins and write the number on the pins
note:this function can work with com cath or com anod but it depends on the decoder you bought
*/
void Seven_Seg_bcd_write(unsigned char port_name,unsigned char pins[4],unsigned char number);


void Sevensegmant_com_cath_vwrite_word_timer(unsigned char port_name,unsigned char number);

#endif /* SEVEN_SEGMANT_DRIVER_H_ */