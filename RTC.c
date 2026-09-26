#include <lpc21xx.h>
#include "types.h"
#include "defines.h"
#include "LCD.h"

char week[][4] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};

void RTC_Init(void)
{
	// Disable and reset the RTC
//	CCR = RTC_RESET;
	
	#ifdef CPU_LPC2148
	
		CCR |= RTC_ENABLE | RTC_CLKSRC;
	
	#else

		PREINT = PREINT_VAL;
		PREFRAC = PREFRAC_VAL;
	
		CCR = RTC_ENABLE; 


    #endif
} 

void SET_RTC_Time_Info(u32 hour, u32 minute, u32 second)
{
	HOUR = hour;
	MIN = minute;
	SEC = second;
}

void GET_RTC_Time_Info(s32 *hour, s32 *minute, s32 *second)
{
	*hour = HOUR;
	*minute = MIN;
	*second = SEC;
}

void Display_RTC_Time(u32 hour, u32 minute, u32 second)
{
	WRITE_LCD_CMD(GOTO_LINE1_POS0);
	WRITE_LCD_DATA(hour/10+48);
	WRITE_LCD_DATA(hour%10+48);
	WRITE_LCD_DATA(':');
	WRITE_LCD_DATA(minute/10+48);
	WRITE_LCD_DATA(minute%10+48);
	WRITE_LCD_DATA(':');
	WRITE_LCD_DATA(second/10+48);
	WRITE_LCD_DATA(second%10+48);
}	

void SET_RTC_Date_Info(u32 date, u32 month, u32 year)
{
	DOM = date;
	MONTH = month;
	YEAR = year;
}

void GET_RTC_Date_Info(s32 *date, s32 *month, s32 *year)
{
	*date = DOM;
	*month = MONTH;
	*year = YEAR;
}

void Display_RTC_Date(u32 date, u32 month, u32 year)
{
	WRITE_LCD_CMD(GOTO_LINE2_POS0);
	WRITE_LCD_DATA(date/10+48);
	WRITE_LCD_DATA(date%10+48);
	WRITE_LCD_DATA('/');
	WRITE_LCD_DATA(month/10+48);
	WRITE_LCD_DATA(month%10+48);
	WRITE_LCD_DATA('/');
	u32LCD(year);
}

void SET_RTC_DAY(u32 dow)
{
	DOW = dow;
}

void GET_RTC_DAY(s32 *dow)
{
	*dow = DOW;
}

void Display_RTC_Day(u32 day)
{
	WRITE_LCD_CMD(GOTO_LINE1_POS0 + 10);
	strLCD(week[day]);
}
