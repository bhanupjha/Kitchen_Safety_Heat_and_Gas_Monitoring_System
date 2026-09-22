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
u32 temp_threshold = THRSHOLD_VAL;
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

void Edit_Menu(void)
{
	u32 choice;
	WRITE_LCD_CMD(0x01);
	strLCD("1:RTC 2:Thresh");
	WRITE_LCD_CMD(0xC0);
	strLCD("3:Pass 4:Exit");
	tdelay_ms(1000);
	//choice = ReadNum1();
	WRITE_LCD_CMD(0x01);
	strLCD("CHOICE=");
	choice = ReadNum1();
	u32LCD(choice);
	switch(choice)
	{
		case 1: edit_rtc();
		          break;
		case 2: edit_threshold();
		           break;
		case 3: change_password();
		           break;
		case 4: WRITE_LCD_CMD(0x01);
            strLCD("Exiting...");
            tdelay_ms(1000);
            edit_mode = 0;
    default: break;
	}
}
	
void edit_rtc(void)	
{
		s32 temp_hr,temp_min,temp_sec;
		s32 temp_day,temp_mon,temp_yr;
		u32 input;
	  GET_RTC_Time_Info(&temp_hr, &temp_min, &temp_sec);
	  GET_RTC_Date_Info(&temp_day, &temp_mon, &temp_yr);
		WRITE_LCD_CMD(0x01);
		strLCD("Set TIME ");
		WRITE_LCD_CMD(0x01);
		strLCD("Enter Hour(24H):");
		input = ReadNum1();
	  u32LCD(input);
		if(input < 24)
			temp_hr = input;
		// Get minutes
		WRITE_LCD_CMD(0x01);
	//	strLCD("Set TIME ");
		WRITE_LCD_CMD(0x01);
		strLCD("Enter Min(60M):");
		input = ReadNum1();
		u32LCD(input);
		if(input < 60)
			temp_min = input;
		//GET second
		
		WRITE_LCD_CMD(0x01);
	//	strLCD("Set TIME ");
		WRITE_LCD_CMD(0x01);
		strLCD("Enter Sec(60S):");
		input = ReadNum1();
		u32LCD(input);
		if(input < 60)
			temp_sec = input;
		//commit time values directly to rtc register
		SET_RTC_Time_Info(temp_hr,temp_min,temp_sec);
		
		// Get Day(Date)
		WRITE_LCD_CMD(0x01);
		strLCD("Set Date");
		WRITE_LCD_CMD(0x01);
		strLCD("Enter Day(31D):");
		input = ReadNum1();
		u32LCD(input);
		if(input > 0 && input <= 31)
			temp_day = input;
		//GET Month
		WRITE_LCD_CMD(0x01);
	//	strLCD("Set Date");
		WRITE_LCD_CMD(0x01);
		strLCD("Enter Month(12M):");
		input = ReadNum1();
		u32LCD(input);
		if(input > 0 && input <= 12)
			temp_mon = input;
		
		//Get year
		WRITE_LCD_CMD(0x01);
	//	strLCD("Set Date");
		WRITE_LCD_CMD(0x01);
		strLCD("Enter year(20S):");
		input = ReadNum1();
		u32LCD(input);
		if(input >= 2000 && input <= 2099)
			temp_yr = input;
		
		//commit Date values directly to rtc register
		SET_RTC_Date_Info(temp_day,temp_mon,temp_yr);
		
		WRITE_LCD_CMD(0x01);
		strLCD("RTC Updated!");
		tdelay_ms(1000);
		
}
void edit_threshold(void)
{
//	u32 gas_in;
	u32 temp_in;
	  WRITE_LCD_CMD(0x01);
	strLCD("Set Temp Limit:");
		WRITE_LCD_CMD(0x01);
	strLCD("Max (T):");
		 temp_in= ReadNum1();
	u32LCD(temp_in);
	if(temp_in <=100)
	  temp_threshold = temp_in;
	
	 WRITE_LCD_CMD(0x01);
	strLCD("Limit Saved!");
	tdelay_ms(1000);
}
