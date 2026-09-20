#include "LCD.h"
#include "RTC.h"
#include "types.h"
#include "defines.h"
#include "LM35.h"
#include "ADC.h"
#include "pin_define.h"
#include  <lpc21xx.h>

s32 hour, min, sec, date, month, year, day;
f32 tempc;
u32 gas_logic;
int main()
{
	// Initialize RTC
	RTC_Init();
	
	// Initialize the LCD
	Init_LCD();
	
	// Intialize the ADC
	Init_ADC();
	
	// set the initial time(hours, minute, seconds)
	SET_RTC_Time_Info(11, 36, 0);
	
	// set the initial date (date, month, year)
	SET_RTC_Date_Info(9, 19, 2026);
	
	// set initial day (SUN to SAT)
	SET_RTC_DAY(FRI);
	
	while(1)
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
		
		tempc = LM35tc();
	  display_temp(tempc);
		gas_logic = ((IOPIN0>>MQ2_Gas)&1);
		display_gas(gas_logic);
		LED_Buzzer_check(tempc, gas_logic);
			  
	}
	
}
