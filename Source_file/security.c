#include "types.h"
#include "security.h"
#include "LCD.h"
#include "timer0.h"
#include "kpm.h"
#include "security.h"
#include "defines.h"

u32 Wrong_attempt=3;
u32 System_Password = 111;

//-------------------------------------------------------------Check_Password()-----------------------------------------------------------------------
u32 CheckPassword(void)
{
	u32 Password;
	WRITE_LCD_CMD(CLEAR_LCD);
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

//--------------------------------------------------------Access_Granted()---------------------------------------------
void Access_Granted(void)
{
	Wrong_attempt=3;
	WRITE_LCD_CMD(CLEAR_LCD);
	strLCD("Access Granted"); 
	tdelay_ms(1000);
	WRITE_LCD_CMD(CLEAR_LCD);
	strLCD("EDIT MODE");
	tdelay_ms(1000);
}

//----------------------------------------------------------Access_Denied-----------------------------------------------
void Access_Denied(void)
{
	WRITE_LCD_CMD(CLEAR_LCD);
	strLCD("ACCESS DENIED");
	Wrong_attempt--;
	if(Wrong_attempt>=1)
	{
	  WRITE_LCD_CMD(GOTO_LINE2_POS0);
	  strLCD("ATTEMPT LEFT ");
	  u32LCD(Wrong_attempt);
	}
			
	else
	{
		WRITE_LCD_CMD(CLEAR_LCD);
		strLCD("SYSTEM LOCKED");
		tdelay_ms(4000);
		Wrong_attempt=3;
	}
		tdelay_ms(2000);
}

//-----------------------------------------------------------change_password()-----------------------------------------
void change_password(void)
{
	u32 new_p1;
	u32 new_p2;
	u32 check;
	WRITE_LCD_CMD(CLEAR_LCD);
	strLCD("Security Check");
	WRITE_LCD_CMD(CLEAR_LCD);
	strLCD("Old Password:");
	check = ReadNum();
	if(check != System_Password)
	{
		WRITE_LCD_CMD(CLEAR_LCD);
		strLCD("Access Denied!");
		tdelay_ms(1000);
		return;
	}
	WRITE_LCD_CMD(CLEAR_LCD);
	strLCD("Authenticated");
    WRITE_LCD_CMD(CLEAR_LCD);
	strLCD("New Password:");
	new_p1 = ReadNum();
	  
	 WRITE_LCD_CMD(CLEAR_LCD);
	 strLCD("Confirm Pass");
	 WRITE_LCD_CMD(CLEAR_LCD);
	 strLCD("Repeat:");
	 new_p2 = ReadNum();
	
	 WRITE_LCD_CMD(CLEAR_LCD);
	if(new_p1==new_p2)
	{
		System_Password = new_p1;

		strLCD("Password change");
	}
	else
		strLCD("Mismatch Error!");
	    tdelay_ms(1000);
}
