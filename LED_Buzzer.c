#include <lpc21xx.h>
void LED_ON(void)
{
	// set pin po.6 as o/p
	IODIR0 |= 1<<0;
	
	// Make high pin 6
	IOCLR0 = 1<<0;
}

void LED_OFF(void)
{
	// set pin po.6 as o/p
	IODIR0 |= 1<<0;
	
	// Make high pin 6
	IOSET0 = 1<<0;
}

void Buzzer_ON(void)
{
	// set pin po.6 as o/p
	IODIR0 |= 1<<1;
	
	// Make high pin 6
	IOSET0 = 1<<1;
}

void Buzzer_OFF(void)
{
	// set pin po.6 as o/p
	IODIR0 |= 1<<1;
	
	// Make high pin 6
	IOCLR0 = 1<<1;
}
