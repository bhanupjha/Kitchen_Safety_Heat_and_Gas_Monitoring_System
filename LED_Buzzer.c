#include <lpc21xx.h>
#include "pin_define.h"
void LED_ON(void)
{
	// set pin po.6 as o/p
	IODIR0 |= 1<<4;
	
	// Make high pin 6
	IOCLR0 = 1<<4;
}

void LED_OFF(void)
{
	// set pin po.6 as o/p
	IODIR0 |= 1<<4;
	
	// Make high pin 6
	IOSET0 = 1<<4;
}

void Buzzer_ON(void)
{
	// set pin po.6 as o/p
	IODIR0 |= 1<<Buzzer_pin;
	
	// Make high pin 6
	IOSET0 = 1<<Buzzer_pin;
}

void Buzzer_OFF(void)
{
	// set pin po.6 as o/p
	IODIR0 |= 1<<Buzzer_pin;
	
	// Make high pin 6
	IOCLR0 = 1<<Buzzer_pin;
}
