/*
 * INTERRUPT_DRIVER.h
 *
 * Created: 10/6/2023 12:47:01 AM
 *  Author: johnr
 */ 


#ifndef INTERRUPT_DRIVER_H_
#define INTERRUPT_DRIVER_H_

#include "STD_MACROS1.h"
#include "DIO_DRIVER.h"
#include <avr/interrupt.h>


void INT0_enable();

void INT1_enable();
void INT1_disenable();

void INT2_enable();


#endif /* INTERRUPT_DRIVER_H_ */