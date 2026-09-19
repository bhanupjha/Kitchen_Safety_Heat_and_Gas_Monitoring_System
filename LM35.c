#include "types.h"
#include "ADC.h"
#include "defines.h"
#include "LCD.h"

f32 LM35tc(void)
{
	u32 dval;
	f32 eAR;
	Read_ADC(CH0, &dval, &eAR);
	return (eAR*100);
}

/*f32 LM35tF(void)
{
	f32 tempc;
	tempc = LM35tc();
	return (tempc*(1.8)+32);
}*/

void display_temp(u32 tempc)
{
	  WRITE_LCD_CMD(0X8A);
		strLCD("T: ");
		f32LCD(tempc, 2);
		WRITE_LCD_DATA(0XDF);
		WRITE_LCD_DATA('C');
}
