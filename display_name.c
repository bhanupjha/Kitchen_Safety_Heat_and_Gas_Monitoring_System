#include "defines.h"
#include "timer0.h"
#include "display_name.h"
#include "LCD.h"

void startup()
{
		WRITE_LCD_CMD(GOTO_LINE1_POS0);
		strLCD("BHANU PRAKASH");
		WRITE_LCD_CMD(GOTO_LINE2_POS0);
		strLCD("KITCHEN SAFETY");
		tdelay_s(1);
}
