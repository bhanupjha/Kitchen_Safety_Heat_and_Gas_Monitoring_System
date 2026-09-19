//ADC.c

#include<lpc21xx.h>
#include "defines.h"
#include "delay.h"

void Init_ADC(void)
{
	//make P0.27 to P0.30 as GPIO
	//PINSEL1 &= (~(3<<((28-16)*2)));
	
	//cfg P0.27 as AIN0
	PINSEL1 |=(1<<((28-16)*2));// AIN1;
	//Cfg_portpin(0,27,1);
	//PINSEL1 |= 0x15400000; // P0.27 to P0.30 as AIN
	
	
	// select PDN_BIT and CLKDIV value
	ADCR = ((1<<PDN_BIT) | (CLK_DIV_VALUE<<CLKDIV));
}

void Read_ADC(u32 chno, u32 *dval, f32 *eAR)
{
	//clear previous channel values
	ADCR &= ~(255<<0);
	
	//select channel & start conversion
	ADCR |= 1<<chno | 1<<START_CONV;

	
	//wait for 3us
	delay_us(3);
	
	//check the done bit status
	while(((ADDR>>DONE_BIT)&1)==0);
	//ADCR &=(~(1<<START_CONV));
	
	//extract 10 digital o/p
	*dval = ((ADDR>>6)&1023);
	
	//find eAR value
	*eAR = (3.3/1023)*(*dval);
	//delay_ms(3000);
}
