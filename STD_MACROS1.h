/*
 * STD_MACROS1.h
 *
 * Created: 4/20/2023 11:53:08 PM
 *  Author: johnr
 */ 


#ifndef STD_MACROS1_H_
#define STD_MACROS1_H_
#define REGISTER_SIZE 8
#define set_bit(reg,pin) (reg|=(1<<pin))
#define clear_bit(reg,pin) (reg&=(~(1<<pin)))
#define toggle_bit(reg,pin) (reg^=(1<<pin))
#define read_bit(reg,pin) ((reg&(1<<pin))>>pin)
#define is_bit_set(reg,pin) ((reg&(1<<pin)>>pin)==1)
#define is_bit_clear(reg,pin) ((reg&(1<<pin)>>pin)==0)
#define ROR(reg,num) reg=(reg<<(REGISTER_SIZE-num))|(reg>>num) 
#define ROL(reg,num) reg=(reg>>(REGISTER_SIZE-num))|(reg<<num) 
#endif /* STD_MACROS1_H_ */