#include "LCD.h"
#include "RTC.h"
#include "types.h"
#include "defines.h"

s32 hour, min, sec, date, month, year, day;
int main()
{
	// Initialize RTC
	RTC_Init();
	
	// Initialize the LCD
	Init_LCD();
	
	// set the initial time(hours, minute, seconds)
	SET_RTC_Time_Info(12, 39, 0);
	
	// set the initial date (date, month, year)
	SET_RTC_Date_Info(18, 9, 2026);
	
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
		GET_RTC_DAY(&day);
		Display_RTC_Day(day);
	}
	
}
