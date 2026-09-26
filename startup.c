#include "defines.h"
#include "timer0.h"
#include "startup.h"
#include "LCD.h"

void startup()
{
		WRITE_LCD_CMD(MODE_8BIT_1LINE);
		strLCD("BHANU PRAKASH");
		WRITE_LCD_CMD(MODE_8BIT_2LINE);
		strLCD("KITCHEN SAFETY");
		tdelay_s(2);
}
