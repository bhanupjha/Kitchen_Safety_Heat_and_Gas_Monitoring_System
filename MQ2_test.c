#include <lpc21xx.h>
#include "types.h"
#include "LCD.h"
#include "MQ2.h"
#include "LED_Buzzer.h"
#include "pin_define.h"

int main()
{
	u32 gas_logic;
	u32 prev_gas_logic = 0;
	Init_LCD();
	strLCD("MQ2 TEST");
	WRITE_LCD_CMD(0XC0);
	strLCD("Gas_value:");
	while(1)
	{
		gas_logic = ((IOPIN0>>MQ2_Gas)&1);
		if(gas_logic != prev_gas_logic)
    {
        WRITE_LCD_CMD(0xCA);
        u32LCD(gas_logic);

        prev_gas_logic = gas_logic;
    }

		if(gas_logic == 1)
	{
		Buzzer_ON();
		LED_ON();
	}
	else
	{
		Buzzer_OFF();
		LED_OFF();
	}
	}
}
