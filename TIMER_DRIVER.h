/*
 * TIMER_DRIVER.h
 *
 * Created: 9/7/2023 3:52:16 PM
 *  Author: johnr
 */ 


#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H_




/*
Function name   : Timrer_CTC_interrupt_enable
Function return : void
Function Arguments : (void)
Function description : this function activate the ctc mood,but 80 in OCR0,and activate the interrupt for CTC mood 
so because of the OCR0 has 80 in it so the timer go the ISR every 10 ms so if you want to detect every second you need to make counter that counts until it reach 100 and 
by then a 1 second had passed
note that you can change the value of the OCR0 by going into the function 
note that the clock is set to be the MC clock divided by the prescalor 1024 and you can change it 
*/
void Timer0_CTC_interrupt_mood(void);


/*
Function name   : Timer0_overflow_mood()
Function return : void
Function Arguments : (void)
Function description :this function activate the normal mood (over flow) mood of timer0 by entering a clock into it 
note that the current clock is the system clock divided by 1024 and you can change it by going into the function it self from the c file 
this function also activate the interrupt of timer0 ISR so you need to make THE ISR timer0 overflow
*/
void Timer0_overflow_interrupt_mood();


/*
Function name   : Timer0_ctc_oc0_enbale(unsigned char ocr0_value)
Function return : void
Function Arguments : unsigned char ocr0_value
Function description : this function activate the ctc mood and set the colck to the system clock over 1024 (adjustable) and activate the oc0 
and program the oc0 to toogle every compare match happens you can use it with function --Timer0_CTC_interrupt_mood(void)-- if you want to interrupt happens every
compare match 
*/
void Timer0_ctc_oc0_enbale(unsigned char ocr0_value);


/*
Function name   : Timer0_fastpwm_mood(unsigned char ocr0_value)
Function return : void
Function Arguments : unsigned char ocr0_value
Function description : this function activate the pwm mood for timer 0 and choose the clock to be the system clock over 1024 and make the pb3 as output pin 
and choose that the oc0 will be set every compare match and will be cleared every over flow (non inverting mood) (adjustable)
*/
void Timer0_fastpwm_mood(unsigned char ocr0_value);

/*
Function name   : Timer0_phasecorresct_mood(unsigned char ocr0_value)
Function return : void
Function Arguments : unsigned char ocr0_value
Function description : this function activate the phase correct pwm mood for timer 0 and choose the clock to be the system clock over 1024 and make the pb3 as output pin
and choose that the oc0 will be set every compare match on up counting and will be cleared every compare match on down counting (adjustable)
*/
void Timer0_phasecorresct_mood(unsigned char ocr0_value);


/*
Function name   : Timrer2_CTC_interrupt_enable
Function return : void
Function Arguments : (void)
Function description : this function activate the ctc mood,but 80 in OCR2,and activate the interrupt for CTC mood 
so because of the OCR2 has 80 in it so the timer go the ISR every 10 ms so if you want to detect every second you need to make counter that counts until it reach 100 and 
by then a 1 second had passed
note that you can change the value of the OCR0 by going into the function 
note that the clock is set to be the MC clock divided by the prescalor 1024 and you can change it 
*/
void Timer2_CTC_interrupt_mood(void);


/*
Function name   : Timer2_overflow_mood()
Function return : void
Function Arguments : (void)
Function description :this function activate the normal mood (over flow) mood of timer2 by entering a clock into it 
note that the current clock is the system clock divided by 1024 and you can change it by going into the function it self from the c file 
this function also activate the interrupt of timer0 ISR so you need to make THE ISR timer0 overflow
*/
void Timer2_overflow_interrupt_mood();


/*
Function name   : Timer0_ctc_oc0_enbale(unsigned char ocr0_value)
Function return : void
Function Arguments : unsigned char ocr0_value
Function description : this function activate the ctc mood and set the colck to the system clock over 1024 (adjustable) and activate the oc0 
and program the oc0 to toogle every compare match happens you can use it with function --Timer0_CTC_interrupt_mood(void)-- if you want to interrupt happens every
compare match 
*/
void Timer2_ctc_oc0_enbale(unsigned char ocr0_value);


/*
Function name   : Timer0_fastpwm_mood(unsigned char ocr0_value)
Function return : void
Function Arguments : unsigned char ocr0_value
Function description : this function activate the pwm mood for timer 0 and choose the clock to be the system clock over 1024 and make the pb3 as output pin 
and choose that the 
*/
void Timer2_fastpwm_mood(unsigned char ocr0_value);

/*
Function name   : Timer0_phasecorresct_mood(unsigned char ocr0_value)
Function return : void
Function Arguments : unsigned char ocr0_value
Function description : this function activate the phase correct pwm mood for timer 0 and choose the clock to be the system clock over 1024 and make the pb3 as output pin
and choose that the oc0 will be set every compare match on up counting and will be cleared every compare match on down counting (adjustable)
*/
void Timer2_phasecorresct_mood(unsigned char ocr0_value);



void Timer2_real_time_project();


#endif /* TIMER_DRIVER_H_ */