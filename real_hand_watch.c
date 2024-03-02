/*
 * real_hand_watch.c
 *
 * Created: 10/5/2023 11:24:00 PM
 *  Author: johnr
 */ 

#define F_CPU 8000000UL
#include <util/delay.h>
#include "SEVEN_SEGMANT_DRIVER.h"
#include "LED_DRIVER.h"
#include "PUSH_BUTTON.h"
#include "TIMER_DRIVER.h"
#include <AVR/interrupt.h>



#define OUTPUT_PORT 'D'
#define SEVEN_SEG_PORT 'A'
#define ENABLE_PORT 'C'
#define BUT1 2
#define BUT2 0
#define BUT3 3
#define BUT4 1
#define PM_LED 4
#define AM_LED 5
#define ALARM_LED 6
#define BUZZER 7

void clock_mood();
void edit_clock();
void alarm_mood();
void stopwatch_mood();
void timer_mood();
void show_only_seconds();
void show_minutes_and_seconds();
void sound_on_mood();

volatile unsigned char seconds=30;
volatile unsigned char minutes=0;
volatile unsigned char hours=1;
volatile unsigned char mood=1;
volatile unsigned char counter_timer0=0;
unsigned char clock_pm=0;
unsigned char alarm_minutes=0;
unsigned char alarm_hours=0;
unsigned char alarm_enable=0;
unsigned char alarm_on=0;
unsigned char alarm_pm=0;//if zero then am if 1 then pm
unsigned char alarm_pm_flag=1;
unsigned char timer_enable=0;
unsigned char timer_counter=0;
unsigned char timer_seconds=0;
unsigned char timer_minutes=0;
unsigned char timer_hours=0;
unsigned char timer_on=0;
unsigned char timer_start=0;
unsigned char stopwatch_enable=0;
unsigned char int2_disenable_flag=0;



int main(void)
{
  Sevensegmant_vinit(SEVEN_SEG_PORT);
  Timer0_CTC_interrupt_mood();
  Timer2_real_time_project();
  Button_vinit(OUTPUT_PORT,BUT1);
  Button_vinit(OUTPUT_PORT,BUT2);
  Button_vinit(OUTPUT_PORT,BUT3);
  Button_vinit(OUTPUT_PORT,BUT4);
  Led_vinit(OUTPUT_PORT,PM_LED);
  Led_vinit(OUTPUT_PORT,AM_LED);
  Led_vinit(OUTPUT_PORT,ALARM_LED);
  INT0_enable();
  Led_von(OUTPUT_PORT,PM_LED);
  clock_pm=1;
  Led_voff(OUTPUT_PORT,AM_LED);
  Led_vinit(OUTPUT_PORT,BUZZER);
  DIO_Set_Port_Direction(ENABLE_PORT,0X3F);
  mood=1;
    while(1)
    {
		switch (mood)
		{
			case 1:
			    clock_mood();
			break;
			
			case 2:
			    alarm_mood();
			break;
			    
			case 3:
			    INT1_enable();
			    stopwatch_mood();
			break;
			
			case 4:
			    timer_mood();
			break;
		}			
        
    }
}

ISR(INT0_vect)
{
	mood++;		
	if (mood>=5)
	{
		mood=1;
	}
	if(timer_enable=1)
	{
		timer_enable=0;
	}
}

ISR(INT1_vect)
{
	if (stopwatch_enable==0)
	{
		stopwatch_enable=1;
	}
	else if (stopwatch_enable==1)
	{
		stopwatch_enable=0;
	}
}

ISR(TIMER0_COMP_vect)
{
	counter_timer0++;
	if (counter_timer0>=7)
	{
		counter_timer0=1;
	}
}


ISR(TIMER2_OVF_vect)
{
	seconds++;
	
	if (seconds>=60)
	{
		seconds=0;
		minutes++;
		if (minutes>=60)
		{
			minutes=0;
			hours++;
			if (hours>=12)
			{
				hours=1;
				if (clock_pm==1)
				{
					clock_pm==0;
					Led_voff(OUTPUT_PORT,PM_LED);
					Led_von(OUTPUT_PORT,AM_LED);
				}
				else if (clock_pm==0)
				{
					clock_pm=1;
					Led_von(OUTPUT_PORT,PM_LED);
					Led_voff(OUTPUT_PORT,AM_LED);
				}	
			}
		}
	}
	if (alarm_enable==1)
	{
		if ((alarm_hours==hours)&&(alarm_minutes==minutes)&&(clock_pm==alarm_pm))
		{
			alarm_on=1;
		}
	}
	if (timer_enable==1)
	{
		timer_counter++;
		if (timer_start==1)
		{
		 timer_seconds--;
		 if (timer_hours==0&&timer_minutes==0&&timer_seconds==0)
		 {
			timer_on=1;
		 }
		 else if (timer_seconds==255)	
		 { 
			 if (timer_minutes!=255)
			 {
			   timer_seconds=59;
			   timer_minutes--;		  
			   if (timer_minutes==255)
			  {
				 timer_minutes=59;
				 if (timer_hours!=0)
				 {
					timer_hours--;  
				 } 
			  }
		    }
			}			 								
		}	 
	   }
	   if (stopwatch_enable==1)
	   {
		   timer_counter++;
	   }
	   
	
}

void clock_mood()
{
   if(int2_disenable_flag==1||stopwatch_enable==1)
   {
	   stopwatch_enable=1;
	   int2_disenable_flag=0;
	   INT1_disenable();
   }

   if(timer_enable==1)
   {
	   timer_enable=0;
   }	   
	while(mood==1)
	{	
		if (alarm_on==1)
		{
			alarm_enable=0;
			sound_on_mood();	
		}
		if (Button_u8read(OUTPUT_PORT,BUT4)==1)
		{
			edit_clock();
		}
		if (alarm_pm_flag==1)
		{
			alarm_pm_flag=0;
			if (clock_pm==1)
			{
				Led_von(OUTPUT_PORT,PM_LED);
				Led_voff(OUTPUT_PORT,AM_LED);
			}
			else if (clock_pm==0)
			{
				Led_voff(OUTPUT_PORT,PM_LED);
				Led_von(OUTPUT_PORT,AM_LED);
			}
		}
		
							
	 while(counter_timer0==1)
	 {
		DIO_Write(ENABLE_PORT,0,0);
		DIO_Write(ENABLE_PORT,1,1);
		DIO_Write(ENABLE_PORT,2,1);
		DIO_Write(ENABLE_PORT,3,1);
		DIO_Write(ENABLE_PORT,4,1);
		DIO_Write(ENABLE_PORT,5,1);
	    Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,hours/10);
	}
	 while(counter_timer0==2)
	 {
	     DIO_Write(ENABLE_PORT,0,1);
	     DIO_Write(ENABLE_PORT,1,0);
	     DIO_Write(ENABLE_PORT,2,1);
	     DIO_Write(ENABLE_PORT,3,1);
	     DIO_Write(ENABLE_PORT,4,1);
	     DIO_Write(ENABLE_PORT,5,1);
	    Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,hours%10);
	}
	 while(counter_timer0==3)
	 {
	   DIO_Write(ENABLE_PORT,0,1);
	   DIO_Write(ENABLE_PORT,1,1);
	   DIO_Write(ENABLE_PORT,2,0);
	   DIO_Write(ENABLE_PORT,3,1);
	   DIO_Write(ENABLE_PORT,4,1);
	   DIO_Write(ENABLE_PORT,5,1);
	   Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,minutes/10);
	}
	 while(counter_timer0==4)
	{
	   DIO_Write(ENABLE_PORT,0,1);
	   DIO_Write(ENABLE_PORT,1,1);
	   DIO_Write(ENABLE_PORT,2,1);
	   DIO_Write(ENABLE_PORT,3,0);
	   DIO_Write(ENABLE_PORT,4,1);
	   DIO_Write(ENABLE_PORT,5,1);
	   Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,minutes%10);
	}
	 while(counter_timer0==5)
	 {
	     DIO_Write(ENABLE_PORT,0,1);
	     DIO_Write(ENABLE_PORT,1,1);
	     DIO_Write(ENABLE_PORT,2,1);
	     DIO_Write(ENABLE_PORT,3,1);
	     DIO_Write(ENABLE_PORT,4,0);
	     DIO_Write(ENABLE_PORT,5,1);
	    Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,seconds/10);
	}
	 while(counter_timer0==6)
	 {
	     DIO_Write(ENABLE_PORT,0,1);
	     DIO_Write(ENABLE_PORT,1,1);
	     DIO_Write(ENABLE_PORT,2,1);
	     DIO_Write(ENABLE_PORT,3,1);
	     DIO_Write(ENABLE_PORT,4,1);
	     DIO_Write(ENABLE_PORT,5,0); 
	     Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,seconds%10);
	 }	
	}	

}

void edit_clock()
{
	unsigned char edit_minutes=minutes;
	unsigned char edit_hours=hours;
	mood=2;
	
	while(mood==2)
	{
		while(mood==2) //in this while we will edit only the minutes 
		{
			
			while(counter_timer0==5)
			{
				DIO_Write(ENABLE_PORT,0,1);
				DIO_Write(ENABLE_PORT,1,1);
				DIO_Write(ENABLE_PORT,2,1);
				DIO_Write(ENABLE_PORT,3,1);
				DIO_Write(ENABLE_PORT,4,0);
				DIO_Write(ENABLE_PORT,5,1);
				Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,seconds/10);
			}
			while(counter_timer0==6)
			{
				DIO_Write(ENABLE_PORT,0,1);
				DIO_Write(ENABLE_PORT,1,1);
				DIO_Write(ENABLE_PORT,2,1);
				DIO_Write(ENABLE_PORT,3,1);
				DIO_Write(ENABLE_PORT,4,1);
				DIO_Write(ENABLE_PORT,5,0);
				Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,seconds%10);
			}
			while(counter_timer0==4)
			{
				DIO_Write(ENABLE_PORT,0,1);
				DIO_Write(ENABLE_PORT,1,1);
				DIO_Write(ENABLE_PORT,2,0);
				DIO_Write(ENABLE_PORT,3,1);
				DIO_Write(ENABLE_PORT,4,1);
				DIO_Write(ENABLE_PORT,5,1);
				Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,edit_minutes/10);
			}
			while(counter_timer0==3)
			{
				DIO_Write(ENABLE_PORT,0,1);
				DIO_Write(ENABLE_PORT,1,1);
				DIO_Write(ENABLE_PORT,2,1);
				DIO_Write(ENABLE_PORT,3,0);
				DIO_Write(ENABLE_PORT,4,1);
				DIO_Write(ENABLE_PORT,5,1);
				Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,edit_minutes%10);
			}
			if  (Button_u8read(OUTPUT_PORT,BUT2)==1)
			{
				edit_minutes++;
				if (edit_minutes>=60)
				{
					edit_minutes=0;
				}
				while(Button_u8read(OUTPUT_PORT,BUT2)==1);
			}
			if (Button_u8read(OUTPUT_PORT,BUT3)==1)
			{
				minutes=edit_minutes;
				while(Button_u8read(OUTPUT_PORT,BUT3)==1);
				break;
			}
		}
		
		while(mood==2) //in this while we will edit only the hours
		{
			while(counter_timer0==2)
			{
				DIO_Write(ENABLE_PORT,0,0);
				DIO_Write(ENABLE_PORT,1,1);
				DIO_Write(ENABLE_PORT,2,1);
				DIO_Write(ENABLE_PORT,3,1);
				DIO_Write(ENABLE_PORT,4,1);
				DIO_Write(ENABLE_PORT,5,1);
				Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,edit_hours/10);
			}
			while(counter_timer0==1)
			{
				DIO_Write(ENABLE_PORT,0,1);
				DIO_Write(ENABLE_PORT,1,0);
				DIO_Write(ENABLE_PORT,2,1);
				DIO_Write(ENABLE_PORT,3,1);
				DIO_Write(ENABLE_PORT,4,1);
				DIO_Write(ENABLE_PORT,5,1);
				Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,edit_hours%10);
			}	
			if (Button_u8read(OUTPUT_PORT,BUT2)==1)
			{
				edit_hours++;
				if (edit_hours==13)
				{
					edit_hours=1;
				}
				while(Button_u8read(OUTPUT_PORT,BUT2)==1);
			}
			if (Button_u8read(OUTPUT_PORT,BUT3)==1)
			{
				hours=edit_hours;
				while(Button_u8read(OUTPUT_PORT,BUT3)==1);
				break;
			}
			
		}
		while(mood==2)
		{
			 while(counter_timer0==1)
			 {
				 DIO_Write(ENABLE_PORT,0,0);
				 DIO_Write(ENABLE_PORT,1,1);
				 DIO_Write(ENABLE_PORT,2,1);
				 DIO_Write(ENABLE_PORT,3,1);
				 DIO_Write(ENABLE_PORT,4,1);
				 DIO_Write(ENABLE_PORT,5,1);
				 Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,0);
			 }
			 while(counter_timer0==2)
			 {
				 DIO_Write(ENABLE_PORT,0,1);
				 DIO_Write(ENABLE_PORT,1,0);
				 DIO_Write(ENABLE_PORT,2,1);
				 DIO_Write(ENABLE_PORT,3,1);
				 DIO_Write(ENABLE_PORT,4,1);
				 DIO_Write(ENABLE_PORT,5,1);
				 Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,0);
			 }
				while(counter_timer0==4)
				{
					DIO_Write(ENABLE_PORT,0,1);
					DIO_Write(ENABLE_PORT,1,1);
					DIO_Write(ENABLE_PORT,2,0);
					DIO_Write(ENABLE_PORT,3,1);
					DIO_Write(ENABLE_PORT,4,1);
					DIO_Write(ENABLE_PORT,5,1);
					Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,0);
				}
				while(counter_timer0==3)
				{
					DIO_Write(ENABLE_PORT,0,1);
					DIO_Write(ENABLE_PORT,1,1);
					DIO_Write(ENABLE_PORT,2,1);
					DIO_Write(ENABLE_PORT,3,0);
					DIO_Write(ENABLE_PORT,4,1);
					DIO_Write(ENABLE_PORT,5,1);
					Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,0);
				}
				while(counter_timer0==5)
				{
					DIO_Write(ENABLE_PORT,0,1);
					DIO_Write(ENABLE_PORT,1,1);
					DIO_Write(ENABLE_PORT,2,1);
					DIO_Write(ENABLE_PORT,3,1);
					DIO_Write(ENABLE_PORT,4,0);
					DIO_Write(ENABLE_PORT,5,1);
					Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,0);
				}
				while(counter_timer0==6)
				{
					DIO_Write(ENABLE_PORT,0,1);
					DIO_Write(ENABLE_PORT,1,1);
					DIO_Write(ENABLE_PORT,2,1);
					DIO_Write(ENABLE_PORT,3,1);
					DIO_Write(ENABLE_PORT,4,1);
					DIO_Write(ENABLE_PORT,5,0);
					Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,0);
				}
			if (Button_u8read(OUTPUT_PORT,BUT2)==1)
			{
				if (clock_pm==0)
				{
					clock_pm=1;
					Led_von(OUTPUT_PORT,PM_LED);
					Led_voff(OUTPUT_PORT,AM_LED);
				}
				else if (clock_pm==1)
				{
					clock_pm=0;
					Led_voff(OUTPUT_PORT,PM_LED);
					Led_von(OUTPUT_PORT,AM_LED);	
				}
				while(Button_u8read(OUTPUT_PORT,BUT2)==1);
			}
			if (Button_u8read(OUTPUT_PORT,BUT3)==1)
			{
				mood=1;
				break;
			}
		}
					
			
	}
}

void alarm_mood()
{
	Led_von(OUTPUT_PORT,PM_LED);
	Led_voff(OUTPUT_PORT,AM_LED);
	alarm_pm=1;
	while(mood==2)
	{
		while(mood==2)
		{
			 while(counter_timer0==4)
			 {
				 DIO_Write(ENABLE_PORT,0,1);
				 DIO_Write(ENABLE_PORT,1,1);
				 DIO_Write(ENABLE_PORT,2,0);
				 DIO_Write(ENABLE_PORT,3,1);
				 DIO_Write(ENABLE_PORT,4,1);
				 DIO_Write(ENABLE_PORT,5,1);
				 Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,alarm_minutes/10);
			 }
			 while(counter_timer0==3)
			 {
				 DIO_Write(ENABLE_PORT,0,1);
				 DIO_Write(ENABLE_PORT,1,1);
				 DIO_Write(ENABLE_PORT,2,1);
				 DIO_Write(ENABLE_PORT,3,0);
				 DIO_Write(ENABLE_PORT,4,1);
				 DIO_Write(ENABLE_PORT,5,1);
				 Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,alarm_minutes%10);
			 }
			 if (Button_u8read(OUTPUT_PORT,BUT2)==1)
			 {
				 alarm_minutes++;
				 if (alarm_minutes>=60)
				 {
					 alarm_minutes=0;
				 }
				 while(Button_u8read(OUTPUT_PORT,BUT2)==1);
			 }
			 if (Button_u8read(OUTPUT_PORT,BUT3)==1)
			 {
				 while (Button_u8read(OUTPUT_PORT,BUT3)==1);
				 break;
			 }
		}
		while (mood==2)
	    {				
		 while(counter_timer0==1)
		 {
			 DIO_Write(ENABLE_PORT,0,0);
			 DIO_Write(ENABLE_PORT,1,1);
			 DIO_Write(ENABLE_PORT,2,1);
			 DIO_Write(ENABLE_PORT,3,1);
			 DIO_Write(ENABLE_PORT,4,1);
			 DIO_Write(ENABLE_PORT,5,1);
			 Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,alarm_hours/10);
		 }
		 while(counter_timer0==2)
		 {
			 DIO_Write(ENABLE_PORT,0,1);
			 DIO_Write(ENABLE_PORT,1,0);
			 DIO_Write(ENABLE_PORT,2,1);
			 DIO_Write(ENABLE_PORT,3,1);
			 DIO_Write(ENABLE_PORT,4,1);
			 DIO_Write(ENABLE_PORT,5,1);
			 Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,alarm_hours%10);
		 }
		 if (Button_u8read(OUTPUT_PORT,BUT2)==1)
		 {
			 alarm_hours++;
			 if(alarm_hours>=13)
			 {
				 alarm_hours=1;
			 }
			 while(Button_u8read(OUTPUT_PORT,BUT2)==1);
		 }
		 else if (Button_u8read(OUTPUT_PORT,BUT3)==1)
		 {
			 
			 while(Button_u8read(OUTPUT_PORT,BUT3)==1);
			 break;
		 }
		}
		while(mood==2)	
		{
			while(counter_timer0==1)
			{
				DIO_Write(ENABLE_PORT,0,0);
				DIO_Write(ENABLE_PORT,1,1);
				DIO_Write(ENABLE_PORT,2,1);
				DIO_Write(ENABLE_PORT,3,1);
				DIO_Write(ENABLE_PORT,4,1);
				DIO_Write(ENABLE_PORT,5,1);
				Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,0);
			}
			while(counter_timer0==2)
			{
				DIO_Write(ENABLE_PORT,0,1);
				DIO_Write(ENABLE_PORT,1,0);
				DIO_Write(ENABLE_PORT,2,1);
				DIO_Write(ENABLE_PORT,3,1);
				DIO_Write(ENABLE_PORT,4,1);
				DIO_Write(ENABLE_PORT,5,1);
				Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,0);
			}
			while(counter_timer0==4)
			{
				DIO_Write(ENABLE_PORT,0,1);
				DIO_Write(ENABLE_PORT,1,1);
				DIO_Write(ENABLE_PORT,2,0);
				DIO_Write(ENABLE_PORT,3,1);
				DIO_Write(ENABLE_PORT,4,1);
				DIO_Write(ENABLE_PORT,5,1);
				Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,0);
			}
			while(counter_timer0==3)
			{
				DIO_Write(ENABLE_PORT,0,1);
				DIO_Write(ENABLE_PORT,1,1);
				DIO_Write(ENABLE_PORT,2,1);
				DIO_Write(ENABLE_PORT,3,0);
				DIO_Write(ENABLE_PORT,4,1);
				DIO_Write(ENABLE_PORT,5,1);
				Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,0);
			}
			while(counter_timer0==5)
			{
				DIO_Write(ENABLE_PORT,0,1);
				DIO_Write(ENABLE_PORT,1,1);
				DIO_Write(ENABLE_PORT,2,1);
				DIO_Write(ENABLE_PORT,3,1);
				DIO_Write(ENABLE_PORT,4,0);
				DIO_Write(ENABLE_PORT,5,1);
				Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,0);
			}
			while(counter_timer0==6)
			{
				DIO_Write(ENABLE_PORT,0,1);
				DIO_Write(ENABLE_PORT,1,1);
				DIO_Write(ENABLE_PORT,2,1);
				DIO_Write(ENABLE_PORT,3,1);
				DIO_Write(ENABLE_PORT,4,1);
				DIO_Write(ENABLE_PORT,5,0);
				Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,0);
			}
			if (Button_u8read(OUTPUT_PORT,BUT2)==1)
			{
				if (alarm_pm==1)
				{
					alarm_pm_flag=1;
					alarm_pm=0;
					Led_voff(OUTPUT_PORT,PM_LED);
					Led_von(OUTPUT_PORT,AM_LED);
				}
				else if (alarm_pm==0)
				{
					alarm_pm_flag=1;
					alarm_pm=1;
					Led_von(OUTPUT_PORT,PM_LED);
					Led_voff(OUTPUT_PORT,AM_LED);
				}
				
				while(Button_u8read(OUTPUT_PORT,BUT2)==1);
			}
			if (Button_u8read(OUTPUT_PORT,BUT3)==1)
			{
				while(Button_u8read(OUTPUT_PORT,BUT3)==1);
				mood=1;
				alarm_pm_flag=1;
				alarm_enable=1;
				Led_von(OUTPUT_PORT,ALARM_LED);
				break;
			}
			
		}
	}
	
}

void stopwatch_mood()
{
	timer_counter=0;
	stopwatch_enable=1;
	int2_disenable_flag=1;
	float y=0;
	unsigned char stopwatch_mseconds=0;
	unsigned char stopwatch_minutes=0;
	
	while(mood==3)
	{
	   if (timer_counter==2)
		{
		  break;	
		}
		 while(counter_timer0==1)
		 {
			 DIO_Write(ENABLE_PORT,0,0);
			 DIO_Write(ENABLE_PORT,1,1);
			 DIO_Write(ENABLE_PORT,2,1);
			 DIO_Write(ENABLE_PORT,3,1);
			 DIO_Write(ENABLE_PORT,4,1);
			 DIO_Write(ENABLE_PORT,5,1);
			 Sevensegmant_com_cath_vwrite_word_timer(SEVEN_SEG_PORT,'S');
		 }
		 while(counter_timer0==2)
		 {
			 DIO_Write(ENABLE_PORT,0,1);
			 DIO_Write(ENABLE_PORT,1,0);
			 DIO_Write(ENABLE_PORT,2,1);
			 DIO_Write(ENABLE_PORT,3,1);
			 DIO_Write(ENABLE_PORT,4,1);
			 DIO_Write(ENABLE_PORT,5,1);
			 Sevensegmant_com_cath_vwrite_word_timer(SEVEN_SEG_PORT,'T');
		 }
		 while(counter_timer0==3)
		 {
			 DIO_Write(ENABLE_PORT,0,1);
			 DIO_Write(ENABLE_PORT,1,1);
			 DIO_Write(ENABLE_PORT,2,0);
			 DIO_Write(ENABLE_PORT,3,1);
			 DIO_Write(ENABLE_PORT,4,1);
			 DIO_Write(ENABLE_PORT,5,1);
			 Sevensegmant_com_cath_vwrite_word_timer(SEVEN_SEG_PORT,'O');
		 }
		 while(counter_timer0==4)
		 {
			 DIO_Write(ENABLE_PORT,0,1);
			 DIO_Write(ENABLE_PORT,1,1);
			 DIO_Write(ENABLE_PORT,2,1);
			 DIO_Write(ENABLE_PORT,3,0);
			 DIO_Write(ENABLE_PORT,4,1);
			 DIO_Write(ENABLE_PORT,5,1);
			 Sevensegmant_com_cath_vwrite_word_timer(SEVEN_SEG_PORT,'P');
		 }
		 while(counter_timer0==5)
		 {
			 DIO_Write(ENABLE_PORT,0,1);
			 DIO_Write(ENABLE_PORT,1,1);
			 DIO_Write(ENABLE_PORT,2,1);
			 DIO_Write(ENABLE_PORT,3,1);
			 DIO_Write(ENABLE_PORT,4,1);
			 DIO_Write(ENABLE_PORT,5,1);
			 Sevensegmant_com_cath_vwrite_word_timer(SEVEN_SEG_PORT,0);
		 }
		 while(counter_timer0==6)
		 {
			 DIO_Write(ENABLE_PORT,0,1);
			 DIO_Write(ENABLE_PORT,1,1);
			 DIO_Write(ENABLE_PORT,2,1);
			 DIO_Write(ENABLE_PORT,3,1);
			 DIO_Write(ENABLE_PORT,4,1);
			 DIO_Write(ENABLE_PORT,5,1);
			Sevensegmant_com_cath_vwrite_word_timer(SEVEN_SEG_PORT,0);
		 }		
	}
	timer_counter=0;
	while(mood==3)
	{
	   if (timer_counter==2)
		{
		  break;	
		}
		 while(counter_timer0==1)
		 {
			 DIO_Write(ENABLE_PORT,0,0);
			 DIO_Write(ENABLE_PORT,1,1);
			 DIO_Write(ENABLE_PORT,2,1);
			 DIO_Write(ENABLE_PORT,3,1);
			 DIO_Write(ENABLE_PORT,4,1);
			 DIO_Write(ENABLE_PORT,5,1);
			 Sevensegmant_com_cath_vwrite_word_timer(SEVEN_SEG_PORT,'U');
		 }
		 while(counter_timer0==2)
		 {
			 DIO_Write(ENABLE_PORT,0,1);
			 DIO_Write(ENABLE_PORT,1,0);
			 DIO_Write(ENABLE_PORT,2,1);
			 DIO_Write(ENABLE_PORT,3,1);
			 DIO_Write(ENABLE_PORT,4,1);
			 DIO_Write(ENABLE_PORT,5,1);
			 Sevensegmant_com_cath_vwrite_word_timer(SEVEN_SEG_PORT,'U');
		 }
		 while(counter_timer0==3)
		 {
			 DIO_Write(ENABLE_PORT,0,1);
			 DIO_Write(ENABLE_PORT,1,1);
			 DIO_Write(ENABLE_PORT,2,0);
			 DIO_Write(ENABLE_PORT,3,1);
			 DIO_Write(ENABLE_PORT,4,1);
			 DIO_Write(ENABLE_PORT,5,1);
			 Sevensegmant_com_cath_vwrite_word_timer(SEVEN_SEG_PORT,'A');
		 }
		 while(counter_timer0==4)
		 {
			 DIO_Write(ENABLE_PORT,0,1);
			 DIO_Write(ENABLE_PORT,1,1);
			 DIO_Write(ENABLE_PORT,2,1);
			 DIO_Write(ENABLE_PORT,3,0);
			 DIO_Write(ENABLE_PORT,4,1);
			 DIO_Write(ENABLE_PORT,5,1);
			 Sevensegmant_com_cath_vwrite_word_timer(SEVEN_SEG_PORT,'T');
		 }
		 while(counter_timer0==5)
		 {
			 DIO_Write(ENABLE_PORT,0,1);
			 DIO_Write(ENABLE_PORT,1,1);
			 DIO_Write(ENABLE_PORT,2,1);
			 DIO_Write(ENABLE_PORT,3,1);
			 DIO_Write(ENABLE_PORT,4,0);
			 DIO_Write(ENABLE_PORT,5,1);
			 Sevensegmant_com_cath_vwrite_word_timer(SEVEN_SEG_PORT,'C');
		 }
		 while(counter_timer0==6)
		 {
			 DIO_Write(ENABLE_PORT,0,1);
			 DIO_Write(ENABLE_PORT,1,1);
			 DIO_Write(ENABLE_PORT,2,1);
			 DIO_Write(ENABLE_PORT,3,1);
			 DIO_Write(ENABLE_PORT,4,1);
			 DIO_Write(ENABLE_PORT,5,0);
			Sevensegmant_com_cath_vwrite_word_timer(SEVEN_SEG_PORT,'H');
		 }		
	}
	timer_counter=0;
	stopwatch_enable=0;
	while(mood==3)
	{
		while(counter_timer0==1)
		{
			DIO_Write(ENABLE_PORT,0,0);
			DIO_Write(ENABLE_PORT,1,1);
			DIO_Write(ENABLE_PORT,2,1);
			DIO_Write(ENABLE_PORT,3,1);
			DIO_Write(ENABLE_PORT,4,1);
			DIO_Write(ENABLE_PORT,5,1);
			Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,0);
		}
		while(counter_timer0==2)
		{
			DIO_Write(ENABLE_PORT,0,1);
			DIO_Write(ENABLE_PORT,1,0);
			DIO_Write(ENABLE_PORT,2,1);
			DIO_Write(ENABLE_PORT,3,1);
			DIO_Write(ENABLE_PORT,4,1);
			DIO_Write(ENABLE_PORT,5,1);
			Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,0);
		}
		while(counter_timer0==3)
		{
			DIO_Write(ENABLE_PORT,0,1);
			DIO_Write(ENABLE_PORT,1,1);
			DIO_Write(ENABLE_PORT,2,0);
			DIO_Write(ENABLE_PORT,3,1);
			DIO_Write(ENABLE_PORT,4,1);
			DIO_Write(ENABLE_PORT,5,1);
			Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,0);
		}
		while(counter_timer0==4)
		{
			DIO_Write(ENABLE_PORT,0,1);
			DIO_Write(ENABLE_PORT,1,1);
			DIO_Write(ENABLE_PORT,2,1);
			DIO_Write(ENABLE_PORT,3,0);
			DIO_Write(ENABLE_PORT,4,1);
			DIO_Write(ENABLE_PORT,5,1);
			Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,0);
		}
		while(counter_timer0==5)
		{
			DIO_Write(ENABLE_PORT,0,1);
			DIO_Write(ENABLE_PORT,1,1);
			DIO_Write(ENABLE_PORT,2,1);
			DIO_Write(ENABLE_PORT,3,1);
			DIO_Write(ENABLE_PORT,4,0);
			DIO_Write(ENABLE_PORT,5,1);
			Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,0);
		}
		while(counter_timer0==6)
		{
			DIO_Write(ENABLE_PORT,0,1);
			DIO_Write(ENABLE_PORT,1,1);
			DIO_Write(ENABLE_PORT,2,1);
			DIO_Write(ENABLE_PORT,3,1);
			DIO_Write(ENABLE_PORT,4,1);
			DIO_Write(ENABLE_PORT,5,0);
			Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,0);
		}
		if(stopwatch_enable==1)
		{
			break;
		}
	}
	while(mood==3)
	{
		if (Button_u8read(OUTPUT_PORT,BUT2))
		{
			timer_counter=0;
	        stopwatch_minutes=0;
			stopwatch_mseconds=0;
		}
		 
		if (stopwatch_enable==1)
		{
		  y=TCNT2;
		  stopwatch_mseconds=y*(100.0/265.0);
		}		 
		  if (timer_counter>=60)
		  {
			  stopwatch_minutes++;
			  timer_counter=0;
		  }	
		  if (timer_minutes>=60)
		  {
			  break;
		  }			  		  
		   while(counter_timer0==1)
		   {
			 DIO_Write(ENABLE_PORT,0,0);
			 DIO_Write(ENABLE_PORT,1,1);
			 DIO_Write(ENABLE_PORT,2,1);
			 DIO_Write(ENABLE_PORT,3,1);
			 DIO_Write(ENABLE_PORT,4,1);
			 DIO_Write(ENABLE_PORT,5,1);
			 Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,stopwatch_minutes/10);
		   }
		   while(counter_timer0==2)
		   {
			 DIO_Write(ENABLE_PORT,0,1);
			 DIO_Write(ENABLE_PORT,1,0);
			 DIO_Write(ENABLE_PORT,2,1);
			 DIO_Write(ENABLE_PORT,3,1);
			 DIO_Write(ENABLE_PORT,4,1);
			 DIO_Write(ENABLE_PORT,5,1);
			 Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,stopwatch_minutes%10);
		   }
		   while(counter_timer0==3)
		   {
			 DIO_Write(ENABLE_PORT,0,1);
			 DIO_Write(ENABLE_PORT,1,1);
			 DIO_Write(ENABLE_PORT,2,0);
			 DIO_Write(ENABLE_PORT,3,1);
			 DIO_Write(ENABLE_PORT,4,1);
			 DIO_Write(ENABLE_PORT,5,1);
			 Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,timer_counter/10);
		   }
		   while(counter_timer0==4)
		   {
			 DIO_Write(ENABLE_PORT,0,1);
			 DIO_Write(ENABLE_PORT,1,1);
			 DIO_Write(ENABLE_PORT,2,1);
			 DIO_Write(ENABLE_PORT,3,0);
			 DIO_Write(ENABLE_PORT,4,1);
			 DIO_Write(ENABLE_PORT,5,1);
		  	 Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,timer_counter%10);
		   }
		   while(counter_timer0==5)
		   {
			 DIO_Write(ENABLE_PORT,0,1);
			 DIO_Write(ENABLE_PORT,1,1);
			 DIO_Write(ENABLE_PORT,2,1);
			 DIO_Write(ENABLE_PORT,3,1);
			 DIO_Write(ENABLE_PORT,4,0);
			 DIO_Write(ENABLE_PORT,5,1);
			 Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,stopwatch_mseconds/10);
		   }
		   while(counter_timer0==6)
		   {
			 DIO_Write(ENABLE_PORT,0,1);
			 DIO_Write(ENABLE_PORT,1,1);
			 DIO_Write(ENABLE_PORT,2,1);
			 DIO_Write(ENABLE_PORT,3,1);
			 DIO_Write(ENABLE_PORT,4,1);
			 DIO_Write(ENABLE_PORT,5,0);
			 Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,stopwatch_mseconds%10);
		   } 
	   }
		

}


void timer_mood()
{
	timer_seconds=0;
	timer_minutes=0;
	timer_hours=0;
	timer_enable=1;
	timer_counter=0;
	timer_start=0;
	
	while(mood==4)
	{
		if (timer_counter==3)
		{
			break;
		}		
		 while(counter_timer0==1)
		 {
			 DIO_Write(ENABLE_PORT,0,0);
			 DIO_Write(ENABLE_PORT,1,1);
			 DIO_Write(ENABLE_PORT,2,1);
			 DIO_Write(ENABLE_PORT,3,1);
			 DIO_Write(ENABLE_PORT,4,1);
			 DIO_Write(ENABLE_PORT,5,1);
			 Sevensegmant_com_cath_vwrite_word_timer(SEVEN_SEG_PORT,'T');
		 }
		 while(counter_timer0==2)
		 {
			 DIO_Write(ENABLE_PORT,0,1);
			 DIO_Write(ENABLE_PORT,1,0);
			 DIO_Write(ENABLE_PORT,2,1);
			 DIO_Write(ENABLE_PORT,3,1);
			 DIO_Write(ENABLE_PORT,4,1);
			 DIO_Write(ENABLE_PORT,5,1);
			 Sevensegmant_com_cath_vwrite_word_timer(SEVEN_SEG_PORT,'I');
		 }
		 while(counter_timer0==3)
		 {
			 DIO_Write(ENABLE_PORT,0,1);
			 DIO_Write(ENABLE_PORT,1,1);
			 DIO_Write(ENABLE_PORT,2,0);
			 DIO_Write(ENABLE_PORT,3,1);
			 DIO_Write(ENABLE_PORT,4,1);
			 DIO_Write(ENABLE_PORT,5,1);
			 Sevensegmant_com_cath_vwrite_word_timer(SEVEN_SEG_PORT,'N');
		 }
		 while(counter_timer0==4)
		 {
			 DIO_Write(ENABLE_PORT,0,1);
			 DIO_Write(ENABLE_PORT,1,1);
			 DIO_Write(ENABLE_PORT,2,1);
			 DIO_Write(ENABLE_PORT,3,0);
			 DIO_Write(ENABLE_PORT,4,1);
			 DIO_Write(ENABLE_PORT,5,1);
			 Sevensegmant_com_cath_vwrite_word_timer(SEVEN_SEG_PORT,'N');
		 }
		 while(counter_timer0==5)
		 {
			 DIO_Write(ENABLE_PORT,0,1);
			 DIO_Write(ENABLE_PORT,1,1);
			 DIO_Write(ENABLE_PORT,2,1);
			 DIO_Write(ENABLE_PORT,3,1);
			 DIO_Write(ENABLE_PORT,4,0);
			 DIO_Write(ENABLE_PORT,5,1);
			 Sevensegmant_com_cath_vwrite_word_timer(SEVEN_SEG_PORT,'E');
		 }
		 while(counter_timer0==6)
		 {
			 DIO_Write(ENABLE_PORT,0,1);
			 DIO_Write(ENABLE_PORT,1,1);
			 DIO_Write(ENABLE_PORT,2,1);
			 DIO_Write(ENABLE_PORT,3,1);
			 DIO_Write(ENABLE_PORT,4,1);
			 DIO_Write(ENABLE_PORT,5,0);
			Sevensegmant_com_cath_vwrite_word_timer(SEVEN_SEG_PORT,'R');
		 }
		 
	}
	while(mood==4) //in this while we will edit only the minutes
	{	
		while(counter_timer0==5)
		{
			DIO_Write(ENABLE_PORT,0,1);
			DIO_Write(ENABLE_PORT,1,1);
			DIO_Write(ENABLE_PORT,2,1);
			DIO_Write(ENABLE_PORT,3,1);
			DIO_Write(ENABLE_PORT,4,0);
			DIO_Write(ENABLE_PORT,5,1);
			Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,timer_seconds/10);
		}
		 while(counter_timer0==6)
		 {
			 DIO_Write(ENABLE_PORT,0,1);
			 DIO_Write(ENABLE_PORT,1,1);
			 DIO_Write(ENABLE_PORT,2,1);
			 DIO_Write(ENABLE_PORT,3,1);
			 DIO_Write(ENABLE_PORT,4,1);
			 DIO_Write(ENABLE_PORT,5,0);
			Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,timer_seconds%10);
		}
		if  (Button_u8read(OUTPUT_PORT,BUT2)==1)
		{
			timer_seconds++;
			if (timer_seconds>=60)
			{
				timer_seconds=0;
			}
			while (Button_u8read(OUTPUT_PORT,BUT2)==1);
		}
		if (Button_u8read(OUTPUT_PORT,BUT3)==1)
		{
			timer_seconds--;
			if (timer_seconds==255||((timer_seconds>240)&&(timer_seconds<=255)))
			{
				timer_seconds=59;
			}
			while(Button_u8read(OUTPUT_PORT,BUT3)==1);
		}
		if (Button_u8read(OUTPUT_PORT,BUT4)==1)
		{
			while(Button_u8read(OUTPUT_PORT,BUT4)==1);
			break;
		}
	}
	while(mood==4) //in this while we will edit only the hours
	{
		while(counter_timer0==3)
		{
			DIO_Write(ENABLE_PORT,0,1);
			DIO_Write(ENABLE_PORT,1,1);
			DIO_Write(ENABLE_PORT,2,0);
			DIO_Write(ENABLE_PORT,3,1);
			DIO_Write(ENABLE_PORT,4,1);
			DIO_Write(ENABLE_PORT,5,1);
			Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,timer_minutes/10);
		}
		while(counter_timer0==4)
		{
			DIO_Write(ENABLE_PORT,0,1);
			DIO_Write(ENABLE_PORT,1,1);
			DIO_Write(ENABLE_PORT,2,1);
			DIO_Write(ENABLE_PORT,3,0);
			DIO_Write(ENABLE_PORT,4,1);
			DIO_Write(ENABLE_PORT,5,1);
			Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,timer_minutes%10);
		}
		if (Button_u8read(OUTPUT_PORT,BUT2)==1)
		{
			timer_minutes++;
			if (timer_minutes==60)
			{
				timer_minutes=0;
			}
			while(Button_u8read(OUTPUT_PORT,BUT2)==1);
		}
		if (Button_u8read(OUTPUT_PORT,BUT3)==1)
		{
			timer_minutes--;
			if (timer_minutes==255||((timer_minutes>240)&&(timer_minutes<=255)))
			{
				timer_minutes=59;
			}
			while(Button_u8read(OUTPUT_PORT,BUT3)==1);
		}
		if (Button_u8read(OUTPUT_PORT,BUT4)==1)
		{
			while(Button_u8read(OUTPUT_PORT,BUT4)==1);
			break;
		}
	}
	while(mood==4) //in this while we will edit only the hours
	{
		while(counter_timer0==1)
		{
			DIO_Write(ENABLE_PORT,0,0);
			DIO_Write(ENABLE_PORT,1,1);
			DIO_Write(ENABLE_PORT,2,1);
			DIO_Write(ENABLE_PORT,3,1);
			DIO_Write(ENABLE_PORT,4,1);
			DIO_Write(ENABLE_PORT,5,1);
			Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,timer_hours/10);
		}
		 while(counter_timer0==2)
		 {
			 DIO_Write(ENABLE_PORT,0,1);
			 DIO_Write(ENABLE_PORT,1,0);
			 DIO_Write(ENABLE_PORT,2,1);
			 DIO_Write(ENABLE_PORT,3,1);
			 DIO_Write(ENABLE_PORT,4,1);
			 DIO_Write(ENABLE_PORT,5,1);
			Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,timer_hours%10);
		}
		if (Button_u8read(OUTPUT_PORT,BUT2)==1)
		{
			timer_hours++;
			if (timer_hours>=100)
			{
				timer_hours=0;
			}
			while(Button_u8read(OUTPUT_PORT,BUT2)==1);
		}
		if (Button_u8read(OUTPUT_PORT,BUT3)==1)
		{
			timer_hours--;
			if (timer_hours==255||((timer_hours>240)&&(timer_hours<=255)))
			{
				timer_hours=99;
			}
			while(Button_u8read(OUTPUT_PORT,BUT3)==1);
		}
		if (Button_u8read(OUTPUT_PORT,BUT4)==1)
		{
			while(Button_u8read(OUTPUT_PORT,BUT4)==1);
			break;
		}	
	}
	while(mood==4)
	{
		 while(counter_timer0==1)
		 {
			 DIO_Write(ENABLE_PORT,0,0);
			 DIO_Write(ENABLE_PORT,1,1);
			 DIO_Write(ENABLE_PORT,2,1);
			 DIO_Write(ENABLE_PORT,3,1);
			 DIO_Write(ENABLE_PORT,4,1);
			 DIO_Write(ENABLE_PORT,5,1);
			 Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,timer_hours/10);
		 }
		 while(counter_timer0==2)
		 {
			 DIO_Write(ENABLE_PORT,0,1);
			 DIO_Write(ENABLE_PORT,1,0);
			 DIO_Write(ENABLE_PORT,2,1);
			 DIO_Write(ENABLE_PORT,3,1);
			 DIO_Write(ENABLE_PORT,4,1);
			 DIO_Write(ENABLE_PORT,5,1);
			 Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,timer_hours%10);
		 }
		 while(counter_timer0==3)
		 {
			 DIO_Write(ENABLE_PORT,0,1);
			 DIO_Write(ENABLE_PORT,1,1);
			 DIO_Write(ENABLE_PORT,2,0);
			 DIO_Write(ENABLE_PORT,3,1);
			 DIO_Write(ENABLE_PORT,4,1);
			 DIO_Write(ENABLE_PORT,5,1);
			 Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,timer_minutes/10);
		 }
		 while(counter_timer0==4)
		 {
			 DIO_Write(ENABLE_PORT,0,1);
			 DIO_Write(ENABLE_PORT,1,1);
			 DIO_Write(ENABLE_PORT,2,1);
			 DIO_Write(ENABLE_PORT,3,0);
			 DIO_Write(ENABLE_PORT,4,1);
			 DIO_Write(ENABLE_PORT,5,1);
			 Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,timer_minutes%10);
		 }
		 while(counter_timer0==5)
		 {
			 DIO_Write(ENABLE_PORT,0,1);
			 DIO_Write(ENABLE_PORT,1,1);
			 DIO_Write(ENABLE_PORT,2,1);
			 DIO_Write(ENABLE_PORT,3,1);
			 DIO_Write(ENABLE_PORT,4,0);
			 DIO_Write(ENABLE_PORT,5,1);
			 Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,timer_seconds/10);
		 }
		 while(counter_timer0==6)
		 {
			 DIO_Write(ENABLE_PORT,0,1);
			 DIO_Write(ENABLE_PORT,1,1);
			 DIO_Write(ENABLE_PORT,2,1);
			 DIO_Write(ENABLE_PORT,3,1);
			 DIO_Write(ENABLE_PORT,4,1);
			 DIO_Write(ENABLE_PORT,5,0);
			 Sevensegmant_com_cath_vwrite(SEVEN_SEG_PORT,timer_seconds%10);
		 }
		 if (Button_u8read(OUTPUT_PORT,BUT2))
		 {
			 timer_start=1; 
		 }
		 else if (Button_u8read(OUTPUT_PORT,BUT3))
		 {
			 timer_start=0;
		 }
		 if (timer_on==1)
		 {
			 timer_enable=0;
			 timer_seconds=0;
			 timer_minutes=0;
			 timer_hours=0;
			 timer_start=0;
			 sound_on_mood();
		 }
		
	}
}


	
void sound_on_mood()
{
		if ((seconds%2)==0)
		{
		  Led_von(OUTPUT_PORT,ALARM_LED);
		  Led_von(OUTPUT_PORT,BUZZER);
		  //alarm_counter++;
		  if ((Button_u8read(OUTPUT_PORT,BUT2)==1)||(Button_u8read(OUTPUT_PORT,BUT3)==1))
		  {
			timer_on=0;
			alarm_on=0;
			Led_voff(OUTPUT_PORT,ALARM_LED);
			Led_voff(OUTPUT_PORT,BUZZER);
			mood=1;
		  }
		}		 
		if ((seconds%2)==1)
		{
			Led_voff(OUTPUT_PORT,ALARM_LED);
			Led_voff(OUTPUT_PORT,BUZZER);	
			if ((Button_u8read(OUTPUT_PORT,BUT2)==1)||(Button_u8read(OUTPUT_PORT,BUT3)==1))
			{
				 timer_on=0;
		     	 alarm_on=0;
				 Led_voff(OUTPUT_PORT,ALARM_LED);
				 Led_voff(OUTPUT_PORT,BUZZER);	
				 mood=1;	
			}
		}
}
