#include "LCD.h"
#include "RTC.h"
#include "types.h"
#include "defines.h"
#include "LM35.h"
#include "ADC.h"
#include "pin_define.h"
#include "Event_Log.h"
#include "eint0.h"
#include  <lpc21xx.h>
#include "security.h"
#include "kpm.h"
#include "timer0.h"

s32 hour, min, sec, date, month, year, day;
f32 tempc;
u32 gas_logic;

int main()
{
	// Initialize interrupt
	eint1_enable();
	
	// Initialize timer
	Init_timer0();
	
	// intialize kpm
	InitKPM();
	
	// Initialize RTC
	RTC_Init();
	
	// Initialize the LCD
	Init_LCD();
	
	// Intialize the ADC
	Init_ADC();
	
	// set the initial time(hours, minute, seconds)
	SET_RTC_Time_Info(11, 36, 0);
	
	// set the initial date (date, month, year)
	SET_RTC_Date_Info(19, 9, 2026);		
	
	// set initial day (SUN to SAT)
	SET_RTC_DAY(FRI);
	
	// Initialize the event log (after the RTC is set)
	EventLog_Init();

	
	while(1)
	{
		// read both sensors
		tempc = LM35tc();
		gas_logic = ((IOPIN0>>MQ2_Gas)&1);
		
		// save event if a sensor just crossed its set point
		EventLog_Update(tempc, temp_threshold, gas_logic);
		
		// buzzer and LED alert
		LED_Buzzer_check(tempc, gas_logic);
		
		// every 10 s the event screen comes for 3 s, otherwise show the normal screen
		if(EventLog_DisplayTask() == 0)
		{
			// Get and display the current time info on LCD
			GET_RTC_Time_Info(&hour, &min, &sec);	
			Display_RTC_Time(hour, min, sec);
			
			// Get and display the current date info on LCD
			GET_RTC_Date_Info(&date, &month, &year);
			Display_RTC_Date(date, month,  year);
			
			// Get and display the current day info on LCD
			//GET_RTC_DAY(&day);
			//Display_RTC_Day(day);
			
			display_temp(tempc);
			display_gas(gas_logic);
		}
		if(edit_mode == 1)
		{
			edit_mode =0;
			  if(CheckPassword())
			  {
				  Access_Granted();
				  Edit_Menu();
			  }
			  else
			  {
				  Access_Denied();
			  }
		}
		
	}
}
