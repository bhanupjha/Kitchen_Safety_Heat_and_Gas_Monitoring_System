//Event_Log.c

#include "types.h"
#include "defines.h"
#include "LCD.h"
#include "RTC.h"
#include "timer0.h"
#include "Event_Log.h"


static u32 ev_valid = 0;      // 0 = nothing stored yet, 1 = an event is stored
static u32 ev_sensor = 0;     
static f32 ev_value = 0;      
static u32 ev_hour, ev_min, ev_sec;


static u32 temp_unsafe = 0;
static u32 gas_unsafe = 0;


static u32 period_start = 0;  


// read only the seconds from the RTC
static u32 get_rtc_seconds(void)
{
	s32 h, m, s;

	GET_RTC_Time_Info(&h, &m, &s);
	return s;
}

// print a number as 2 digits, example 7 -> 07
static void print_2digits(u32 n)
{
	WRITE_LCD_DATA(n/10 + '0');
	WRITE_LCD_DATA(n%10 + '0');
}

// save sensor name, value and current RTC time
static void record_event(u32 sensor, f32 value)
{
	s32 h, m, s;

	GET_RTC_Time_Info(&h, &m, &s);

	ev_sensor = sensor;
	ev_value  = value;
	ev_hour   = h;
	ev_min    = m;
	ev_sec    = s;
	ev_valid  = 1;
}

// show the stored event on the LCD
static void show_event_screen(void)
{
	WRITE_LCD_CMD(CLEAR_LCD);

	// line 1 : which sensor crossed its set point
	WRITE_LCD_CMD(GOTO_LINE1_POS0);
	strLCD("LAST EVT: ");
	if(ev_sensor == 1)
	{
		strLCD("TEMP");
	}
	else
	{
		strLCD("GAS");
	}

	// line 2 : recorded value and time of occurrence
	WRITE_LCD_CMD(GOTO_LINE2_POS0);
	if(ev_sensor == 1)
	{
		f32LCD(ev_value, 1);
		WRITE_LCD_DATA(0xDF);      // degree symbol
		WRITE_LCD_DATA('C');
	}
	else
	{
		strLCD("G:");
		u32LCD((u32)ev_value);
	}
	WRITE_LCD_DATA(' ');
	print_2digits(ev_hour);
	WRITE_LCD_DATA(':');
	print_2digits(ev_min);
	WRITE_LCD_DATA(':');
	print_2digits(ev_sec);
}


// Intialize -> after RTC
void EventLog_Init(void)
{
	ev_valid = 0;
	temp_unsafe = 0;
	gas_unsafe = 0;

	Init_timer0();                       
	period_start = get_rtc_seconds();
}

//  an event only when a sensor goes from SAFE to UNSAFE
void EventLog_Update(f32 tempc, f32 tempSetPoint, u32 gasLogic)
{
	
	if(tempc > tempSetPoint)
	{
		if(temp_unsafe == 0)             
		{
			temp_unsafe = 1;
			record_event(1, tempc);
		}
	}
	else if(tempc <= tempSetPoint - 2)   // 2 degC below set point -> rest temp -> ready for next crossing
	{
		temp_unsafe = 0;
	}

	// gas detected -> 0
	if(gasLogic == 0)
	{
		if(gas_unsafe == 0)              
		{
			gas_unsafe = 1;
			record_event(2, gasLogic);
		}
	}
	else
	{
		gas_unsafe = 0;
	}
}


u32 EventLog_DisplayTask(void)
{
	u32 now;

	now = get_rtc_seconds();

		if((now + 60 - period_start) % 60 >= EVENT_PERIOD_SEC)
	{
		period_start = now;

		if(ev_valid == 1)                
		{
			show_event_screen();
			tdelay_s(EVENT_SHOW_SEC);    // keep it on the LCD for 3 seconds (Timer0 delay)
			WRITE_LCD_CMD(CLEAR_LCD);    // main loop will draw the normal screen again
			return 1;
		}
	}

	return 0;
}
