//ADC.c

#include<lpc21xx.h>
#include "defines.h"
#include "types.h"
#include "timer0.h"
#include "sensor.h"


void Init_ADC(void)
{
	// cfg p0.28 as AIN1
	PINSEL1 |=AIN1;
	
	// lpc2129 -> proteus
//	PINSEL1&=~(255<<((27-16)*2));
//	PINSEL1 |= AIN1p;
	 
	ADCR = (1<<PDN_BIT)|(CLK_DIV_VALUE<<CLKDIV);
}

void Read_ADC(u32 chno,u32 *dval,f32 *eAR)
{
	// clear previous channel value
    ADCR &=~(255<<0);
	//select channel & start conversion
	ADCR |=1<<chno |1<<START_CONV;
	// wait for 3 usec
	//delay_us(3);
	tdelay_us(3);
	// check the done bit status
	while(((ADDR>>DONE_BIT)&1)==0);
	// stop conversion
//	ADCR&=~(1<<START_CONV);   // lpc2129 -> proteus simulation
	// extract 10 digital op
	*dval=((ADDR>>RESULT)&1023);
	//find Ear value
	*eAR=(3.3/1023)*(*dval);

}
