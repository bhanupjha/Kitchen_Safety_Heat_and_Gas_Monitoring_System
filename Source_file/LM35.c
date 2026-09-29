#include "types.h"
#include "defines.h"
#include "LCD.h"
#include "sensor.h"
#include  "interrupt.h"
#include <lpc21xx.h>
#include "pin_define.h"

u32 buzzer_muted = 0;

//---------------------------------------------------Read_LM35temp()---------------------------------------------------------------------
f32 LM35tc(void)
{
	u32 dval;
	f32 eAR;
	Read_ADC(CH1, &dval, &eAR);
	return (eAR*100);
}

//----------------------------------------------------display_temp()----------------------------------------------------------------------
void display_temp(f32 tempc)
{
	  WRITE_LCD_CMD(0X88);
	  WRITE_LCD_DATA(' ');
		f32LCD(tempc, 2);
		WRITE_LCD_DATA(0XDF);
		WRITE_LCD_DATA('C');
	 
}

//---------------------------------------------------display_gas()--------------------------------------------------------------------
void display_gas(u32 gas_logic)
{
	WRITE_LCD_CMD(0XCA);
	WRITE_LCD_DATA(' ');
	strLCD("G: ");
	u32LCD(gas_logic);
	
}

//--------------------------------------------------LED_Buzzer_check-------------------------------------------------------------------------
void LED_Buzzer_check(f32 tempc, u32 gas_logic)
{
	IODIR1 &= ~(1 << SW2);                            

	if(tempc > temp_val || gas_logic == 0)      
	{
		LED_ON();                                     

		if((IOPIN1 &(1<<SW2))==0)
		{
			buzzer_muted = 1;
			temp_val = tempc;
			Buzzer_OFF();
		}
		if(buzzer_muted == 0)
		{
			Buzzer_ON();
		}
	}
	else                                             
	{
		Buzzer_OFF();
		LED_OFF();
		buzzer_muted = 0;                             
	}
}
