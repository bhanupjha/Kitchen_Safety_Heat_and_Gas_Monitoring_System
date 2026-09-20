//Event_Log.c

#include "types.h"
#include "defines.h"
#include "LCD.h"
#include "RTC.h"
#include "timer0.h"
#include "Event_Log.h"

// ---------- the last event (only ONE is kept, a new event overwrites the old one) ----------
static u32 ev_valid = 0;      // 0 = nothing stored yet, 1 = an event is stored
static u32 ev_sensor = 0;     // 1 = TEMP, 2 = GAS
static f32 ev_value = 0;      // temp value in degC, or gas pin level
static u32 ev_hour, ev_min, ev_sec;

// ---------- remember if the sensor was already unsafe (so only the FIRST crossing is saved) ----------
static u32 temp_unsafe = 0;
static u32 gas_unsafe = 0;

// ---------- 10 second period ----------
static u32 period_start = 0;  // RTC second when the current 10 s period started


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


// call once at start (after RTC is set)
void EventLog_Init(void)
{
	ev_valid = 0;
	temp_unsafe = 0;
	gas_unsafe = 0;

	Init_timer0();                       // timer used by tdelay_s()
	period_start = get_rtc_seconds();
}

// call every loop : saves an event only when a sensor goes from SAFE to UNSAFE
void EventLog_Update(f32 tempc, f32 tempSetPoint, u32 gasLogic)
{
	// ---- temperature ----
	if(tempc > tempSetPoint)
	{
		if(temp_unsafe == 0)             // it was safe before -> this is a new crossing
		{
			temp_unsafe = 1;
			record_event(1, tempc);
		}
	}
	else if(tempc <= tempSetPoint - 2)   // came down 2 degC below set point -> ready for next event
	{
		temp_unsafe = 0;
	}

	// ---- gas (MQ2 pin gives 0 when gas is detected) ----
	if(gasLogic == 0)
	{
		if(gas_unsafe == 0)              // it was safe before -> this is a new crossing
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

// call every loop : every 10 s show the stored event for 3 s
// returns 1 if the event screen was shown in this pass, otherwise 0
u32 EventLog_DisplayTask(void)
{
	u32 now;

	now = get_rtc_seconds();

	// has 10 seconds passed ?
	// (+60 and %60 is used so it also works when seconds go 59 -> 0)
	if((now + 60 - period_start) % 60 >= EVENT_PERIOD_SEC)
	{
		period_start = now;

		if(ev_valid == 1)                // show only if an event exists
		{
			show_event_screen();
			tdelay_s(EVENT_SHOW_SEC);    // keep it on the LCD for 3 seconds (Timer0 delay)
			WRITE_LCD_CMD(CLEAR_LCD);    // main loop will draw the normal screen again
			return 1;
		}
	}

	return 0;
}
