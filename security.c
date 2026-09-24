#include "types.h"
#include "security.h"
#include "LCD.h"
#include "timer0.h"
#include "kpm.h"
#include "security.h"
#include "flash.h"


u32 System_Password = 0;
u32 Wrong_attempt=3;

u32 CheckPassword(void)
{
	u32 Password;
	WRITE_LCD_CMD(0x01);
	strLCD("ENTER Password");
	
	tdelay_ms(500);
	Password = ReadNum();
	if(Password ==System_Password )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void Access_Granted(void)
{
	Wrong_attempt=3;
	WRITE_LCD_CMD(0x01);
	strLCD("Access Granted"); 
	tdelay_ms(1000);
	WRITE_LCD_CMD(0x01);
	strLCD("EDIT MODE");
	tdelay_ms(1000);
}
void Access_Denied(void)
{
	WRITE_LCD_CMD(0x01);
	strLCD("ACCESS DENIED");
	Wrong_attempt--;
	if(Wrong_attempt>=1)
	{
	  WRITE_LCD_CMD(0xC0);
	  strLCD("ATTEMPT LEFT ");
	  u32LCD(Wrong_attempt);
	}
			
	else
	{
		WRITE_LCD_CMD(0x01);
		strLCD("SYSTEM LOCKED");
		tdelay_ms(4000);
		Wrong_attempt=3;
	}
		tdelay_ms(2000);
}

void change_password(void)
{
	u32 new_p1;
	u32 new_p2;
	u32 check;
	WRITE_LCD_CMD(0x01);
	strLCD("Security Check");
	WRITE_LCD_CMD(0x01);
	strLCD("Old Password:");
	check = ReadNum1();
	if(check != System_Password)
	{
		WRITE_LCD_CMD(0x01);
		strLCD("Access Denied!");
		tdelay_ms(1000);
		return;
	}
	WRITE_LCD_CMD(0x01);
	strLCD("Authenticated");
    WRITE_LCD_CMD(0x01);
	strLCD("New Password:");
	new_p1 = ReadNum1();
	  
	 WRITE_LCD_CMD(0x01);
	 strLCD("Confirm Pass");
	 WRITE_LCD_CMD(0x01);
	 strLCD("Repeat:");
	 new_p2 = ReadNum();
	
	 WRITE_LCD_CMD(0x01);
	if(new_p1==new_p2)
	{
		System_Password = new_p1;
		//Flash_SaveConfig();
		strLCD("Password change");
	}
	else
		strLCD("Mismatch Error!");
	    tdelay_ms(1000);
}
