#include "types.h"
#include "ADC.h"
#include "defines.h"
#include "LCD.h"
#include "LM35.h"
#include  "eint0.h"
#include <lpc21xx.h>
#include "pin_define.h"

u32 buzzer_muted = 0;
f32 LM35tc(void)
{
	u32 dval;
	f32 eAR;
	Read_ADC(CH1, &dval, &eAR);
	return (eAR*100);
}

f32 LM35tF(void)
{
	f32 tempc;
	tempc = LM35tc();
	return (tempc*(1.8)+32);
}

void display_temp(f32 tempc)
{
	  WRITE_LCD_CMD(0X88);
	  WRITE_LCD_DATA(' ');
		f32LCD(tempc, 2);
		WRITE_LCD_DATA(0XDF);
		WRITE_LCD_DATA('C');
	 
}

void display_gas(u32 gas_logic)
{
	WRITE_LCD_CMD(0XCA);
	WRITE_LCD_DATA(' ');
	strLCD("G: ");
	u32LCD(gas_logic);
	
}

void LED_Buzzer_check(f32 tempc, u32 gas_logic)
{
	IODIR0 &= ~(1 << SW2);                            // SW2 as input

	if(tempc > temp_threshold || gas_logic == 0)      // unsafe
	{
		LED_ON();                                     // LED (fan) stays ON

		if((IOPIN0 &(1<<SW2))==0)
		{
			buzzer_muted = 1;
			//BUZZER OFF
			Buzzer_OFF();
		}
		if(buzzer_muted == 0)
		{
			Buzzer_ON();
		}
	}
	else                                              // safe
	{
		Buzzer_OFF();
		LED_OFF();
		buzzer_muted = 0;                             // ready for the next alert
	}
}
