#include <lpc21xx.h>
#include "types.h"
#include "KPM.h"
#include "LCD.h"
#include "RTC.h"
#include "ADC.h"
#include "security.h"
#include "pin_define.h"
#include "timer0.h"
#include "eint0.h"
#include "defines.h"
#include "types.h"

volatile u32 edit_mode=0;
f32 temp_val = THRSHOLD_VAL;

//----------------------------------------------------eint0_isr()-----------------------------------------------------
void eint0_isr(void)__irq
{
	if(((IOPIN0>>EINT0_SW1)&1)==0)
	{
		edit_mode =1;
	}
	//IOPIN0 ^=1<<EINT0_SW1;
	// delay_ms(1000);
	VICVectAddr = 0;
	EXTINT = 1<<0; //clear extint0 flag
	
}

//----------------------------------------------------eint0_enable()-------------------------------------------------
void eint0_enable(void)
{
	PINSEL0 &= ~(3<<2);
	//cfg p0.1 as EINT0
	PINSEL0 |= (3<<2);
	EXTPOLAR &= ~(1<<0);
	EXTINT = 1<<0;
	//select extint0 as irq
	VICIntSelect &= ~(0<<EINT0_CHNO);
	//enable extint0 source
	VICIntEnable |= 1<<EINT0_CHNO;
	//load isr address
	VICVectAddr0 =(u32)eint0_isr;
	//select slot for extint0
	VICVectCntl0 = 1<<5|EINT0_CHNO;
	//select edge triggering
	EXTMODE =1<<0;
}

//--------------------------------------------------------Edit_Menu()--------------------------------------------------
void Edit_Menu(void)
{
	u32 choice;
	WRITE_LCD_CMD(CLEAR_LCD);
	strLCD("1:RTC 2:Thresh");
	WRITE_LCD_CMD(GOTO_LINE2_POS0);
	strLCD("3:Pass 4:Exit");
	tdelay_ms(1000);
	//choice = ReadNum1();
	WRITE_LCD_CMD(CLEAR_LCD);
	strLCD("CHOICE=");
	choice = ReadNum1();
	u32LCD(choice);
	switch(choice)
	{
		case 1: edit_rtc_Menu();
		          break;
		case 2: edit_threshold();
		           break;
		case 3: change_password();
		           break;
		case 4: WRITE_LCD_CMD(CLEAR_LCD);
           	strLCD("Exiting...");
            tdelay_ms(1000);
            edit_mode = 0;
				    break;
    default: break;
	}
}

//---------------------------------------------------------edit_rtc_Menu()---------------------------------------------------
void edit_rtc_Menu()
{
	u32 choice;
	WRITE_LCD_CMD(CLEAR_LCD);
	strLCD("1:Time 2: Date");
	WRITE_LCD_CMD(GOTO_LINE2_POS0);
	strLCD("3:Exit");
	tdelay_ms(1000);
	//choice = ReadNum1();
	WRITE_LCD_CMD(CLEAR_LCD);
	strLCD("CHOICE=");
	choice = ReadNum1();
	u32LCD(choice);
	switch(choice)
	{
		case 1: edit_time_Menu();
		          break;
		case 2: edit_date_Menu();
		           break;
		case 3: WRITE_LCD_CMD(CLEAR_LCD);
           		strLCD("Exiting...");
            	tdelay_ms(1000);
            	edit_mode = 0;
				break;
    	default: break;
	}
}

//----------------------------------------------------------edit_time_Menu()-------------------------------------------------
void edit_time_Menu()
{
	u32 choice;
	WRITE_LCD_CMD(CLEAR_LCD);
	strLCD("1:Hour 2:Min");
	WRITE_LCD_CMD(GOTO_LINE2_POS0);
	strLCD("3:Sec 4:All");
	tdelay_ms(1000);
	//choice = ReadNum1();
	WRITE_LCD_CMD(CLEAR_LCD);
	strLCD("CHOICE=");
	choice = ReadNum1();
	u32LCD(choice);
	switch(choice)
	{
		case 1: edit_hr();
		        break;
		case 2: edit_min();
		        break;
		case 3: edit_sec();
		        break;
		case 4: edit_Hr_Min_Sec();
		        break;
		default: WRITE_LCD_CMD(CLEAR_LCD);
           		strLCD("Exiting...");
            	tdelay_ms(1000);
            	edit_mode = 0;
				break;
	}
}

//------------------------------------------------------------edit_hr()------------------------------------------------
void edit_hr()
{
  s32 temp_hr,temp_min,temp_sec;
	u32 input;
	GET_RTC_Time_Info(&temp_hr, &temp_min, &temp_sec);
	while(1)
	{
		WRITE_LCD_CMD(CLEAR_LCD);
	  strLCD("Enter HR(0-23):");
	  input = ReadNum1();
		if(input != 0xFFFFFFFF  && input < 24)
		{
			u32LCD(input);
			temp_hr = input;
			break;
		}
		else
		{
			invalid_input();
		}
	}
	
	//update time values directly to rtc register
	SET_RTC_Time_Info(temp_hr,temp_min,temp_sec);
	WRITE_LCD_CMD(CLEAR_LCD);
	strLCD("Hour Updated!");
	tdelay_ms(1000);
}

//-----------------------------------------------------------edit_min()-------------------------------------------------
void edit_min()
{
	s32 temp_hr,temp_min,temp_sec;
	u32 input;
	GET_RTC_Time_Info(&temp_hr, &temp_min, &temp_sec);
	while(1)
	{
		WRITE_LCD_CMD(CLEAR_LCD);
		strLCD("Enter Min(0-59):");
		input = ReadNum1();
		if(input != 0xFFFFFFFF && input < 60)
		{
      u32LCD(input);
			temp_min = input;
			break;
		}
		else
		{
			invalid_input();
		}
	}
	
	//update time values directly to rtc register
	SET_RTC_Time_Info(temp_hr,temp_min,temp_sec);
	WRITE_LCD_CMD(CLEAR_LCD);
	strLCD("Min Updated!");
	tdelay_ms(1000);
}

//------------------------------------------------------------edit_sec()------------------------------------------------
void edit_sec()
{
	s32 temp_hr,temp_min,temp_sec;
	u32 input;
	GET_RTC_Time_Info(&temp_hr, &temp_min, &temp_sec);
	while(1)
	{
		WRITE_LCD_CMD(CLEAR_LCD);
		strLCD("Enter Sec(0-59):");
		input = ReadNum1();
		if(input != 0xFFFFFFFF && input < 60)
		{
			u32LCD(input);
			temp_sec = input;
			break;
		}
		else
		{
			invalid_input();
		}
	}
	
	//update time values directly to rtc register
	SET_RTC_Time_Info(temp_hr,temp_min,temp_sec);
	WRITE_LCD_CMD(CLEAR_LCD);
	strLCD("Second Updated!");
	tdelay_ms(1000);
}

//------------------------------------------------------------edit_Hr_Min_Sec()-----------------------------------------
void edit_Hr_Min_Sec()
{
	s32 temp_hr,temp_min,temp_sec;
	u32 input;
	GET_RTC_Time_Info(&temp_hr, &temp_min, &temp_sec);
	
	// Get hour
	while(1)
	{
		WRITE_LCD_CMD(CLEAR_LCD);
		strLCD("Set TIME ");
		WRITE_LCD_CMD(CLEAR_LCD);
		strLCD("Enter HR(0-23):");
		input = ReadNum1();
		if(input != 0xFFFFFFFF  && input < 24)
		{
			u32LCD(input);
			temp_hr = input;
			break;
		}
		else
		{
			invalid_input();
		}
	}
	
	// Get minutes
	while(1)
	{
		WRITE_LCD_CMD(CLEAR_LCD);
		strLCD("Enter Min(0-59):");
		input = ReadNum1();
		if(input != 0xFFFFFFFF && input < 60)
		{
			u32LCD(input);
			temp_min = input;
			break;
		}
		else
		{
			invalid_input();
		}
	}
	
	//GET second
	while(1)
	{
		WRITE_LCD_CMD(CLEAR_LCD);
		strLCD("Enter Sec(0-59):");
		input = ReadNum1();
		if(input != 0xFFFFFFFF && input < 60)
		{
			u32LCD(input);
			temp_sec = input;
			break;
		}
	  else
		{
			invalid_input();
		}
	}
	
	//update time values directly to rtc register
	SET_RTC_Time_Info(temp_hr,temp_min,temp_sec);
	WRITE_LCD_CMD(CLEAR_LCD);
	strLCD("Time Updated!");
	tdelay_ms(1000);
		
}

//------------------------------------------------------------------edit_date_Menu()-----------------------------------------
void edit_date_Menu()
{
	u32 choice;
	WRITE_LCD_CMD(CLEAR_LCD);
	strLCD("1:DOM 2:Month");
	WRITE_LCD_CMD(GOTO_LINE2_POS0);
	strLCD("3:Year 4:All");
	tdelay_ms(1000);
	//choice = ReadNum1();
	WRITE_LCD_CMD(CLEAR_LCD);
	strLCD("CHOICE=");
	choice = ReadNum1();
	u32LCD(choice);
	switch(choice)
	{
		case 1: edit_DOM();
		        break;
		case 2: edit_Month();
		        break;
		case 3: edit_Year();
		        break;
		case 4: edit_Dom_Month_Year();
		        break;
		default: WRITE_LCD_CMD(CLEAR_LCD);
           		strLCD("Exiting...");
            	tdelay_ms(1000);
            	edit_mode = 0;
				break;
	}
}

//---------------------------------------------------------edit_DOM()---------------------------------------------------
void edit_DOM()
{
	s32 temp_day,temp_mon,temp_yr;
	u32 input;
	GET_RTC_Date_Info(&temp_day, &temp_mon, &temp_yr);
	while(1)
	{
		WRITE_LCD_CMD(CLEAR_LCD);
		strLCD("Enter DOM(0-31):");
		input = ReadNum1();
		if(input > 0 && input <= 31)
		{
			u32LCD(input);
			temp_day = input;
			break;
		}
		else
		{
			invalid_input();
		}
  }
	
	//update Date values directly to rtc register
	SET_RTC_Date_Info(temp_day,temp_mon,temp_yr);
	WRITE_LCD_CMD(CLEAR_LCD);
	strLCD("DOM Updated!");
	tdelay_ms(1000);
}

//----------------------------------------------------------edit_Month()-----------------------------------------------
void edit_Month()
{
	s32 temp_day,temp_mon,temp_yr;
	u32 input;
	GET_RTC_Date_Info(&temp_day, &temp_mon, &temp_yr);
	while(1)
	{
		WRITE_LCD_CMD(CLEAR_LCD);
		strLCD("Ent Month(1-12):");
		input = ReadNum1();
		if(input > 0 && input <= 12)
		{
			u32LCD(input);
			temp_mon = input;
			break;
		}
		else
		{
			invalid_input();
		}
	}	
	
	//update Date values directly to rtc register
	SET_RTC_Date_Info(temp_day,temp_mon,temp_yr);
	WRITE_LCD_CMD(CLEAR_LCD);
	strLCD("MONTH Updated!");
	tdelay_ms(1000);
}

//------------------------------------------------------------edit_Year()----------------------------------------------
void edit_Year()
{
	s32 temp_day,temp_mon,temp_yr;
	u32 input;
	GET_RTC_Date_Info(&temp_day, &temp_mon, &temp_yr);
	while(1)
	{
		WRITE_LCD_CMD(CLEAR_LCD);
		strLCD("Enter Year(20S):");
		input = ReadNum1();
		if(input >= 2000 && input <= 2099)
		{
			u32LCD(input);
			temp_yr = input;
			break;
		}
		else
		{
			invalid_input();
		}
	}
	
	//update Date values directly to rtc register
	SET_RTC_Date_Info(temp_day,temp_mon,temp_yr);
	WRITE_LCD_CMD(CLEAR_LCD);
	strLCD("YEAR Updated!");
	tdelay_ms(1000);
	
}

//---------------------------------------------------------edit_Dom_Month_Year()---------------------------------------
void edit_Dom_Month_Year()
{
	s32 temp_day,temp_mon,temp_yr;
	u32 input;
	GET_RTC_Date_Info(&temp_day, &temp_mon, &temp_yr);
	WRITE_LCD_CMD(CLEAR_LCD);
	strLCD("Set DATE ");
	
	// Set date of Month
	while(1)
	{
		WRITE_LCD_CMD(CLEAR_LCD);
		strLCD("Enter DOM(1-31):");
		input = ReadNum1();
		if(input > 0 && input <= 31)
		{
			u32LCD(input);
			temp_day = input;
			break;
		}
		else
		{
			invalid_input();
		}
	}
	
	//set month
	while(1)
	{
		WRITE_LCD_CMD(CLEAR_LCD);
		strLCD("Ent Month(1-12):");
		input = ReadNum1();
		if(input > 0 && input <= 12)
		{
			u32LCD(input);
			temp_mon = input;
			break;
		}
		else
		{
			invalid_input();
		}
	}
	
	//Set year
	while(1)
	{
		WRITE_LCD_CMD(CLEAR_LCD);
		strLCD("Enter Year(20S):");
		input = ReadNum1();
		if(input >= 2000 && input <= 2099)
		{
			u32LCD(input);
			temp_yr = input;
			break;
		}
		else
		{
			invalid_input();
		}
	}
	
	//Update Date values directly to rtc register
	SET_RTC_Date_Info(temp_day,temp_mon,temp_yr);

	WRITE_LCD_CMD(CLEAR_LCD);
	strLCD("DATE Updated!");
	tdelay_ms(1000);
}

//----------------------------------------------------------edit_threshold()-------------------------------------------
void edit_threshold(void)
{
	u32 temp_in;
	WRITE_LCD_CMD(CLEAR_LCD);
	strLCD("Set Temp Limit:");
	while(1)
	{
		WRITE_LCD_CMD(CLEAR_LCD);
		strLCD("Max (T):");
		temp_in= ReadNum1();
		if(temp_in <= 100)
		{
			u32LCD(temp_in);
			temp_val = temp_in;
			WRITE_LCD_CMD(CLEAR_LCD);
			strLCD("Limit Saved!");
			tdelay_ms(1000);
			break;
		}
		else
		{
			invalid_input();		
		}
	}
}

//---------------------------------------------------------invalid_input()---------------------------------------------
void invalid_input()
{
	WRITE_LCD_CMD(CLEAR_LCD);
	strLCD("Invalid Input!");
  tdelay_ms(1000);
}
