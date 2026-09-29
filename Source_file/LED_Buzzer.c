#include <lpc21xx.h>
#include "pin_define.h"

//-------------------------------------------------------------LED_ON()----------------------------------------------------------------------------
void LED_ON(void)
{
	// set LED_pin as o/p
	IODIR0 |= 1<<LED_pin;
	
	// Make high LED_pin
	IOCLR0 = 1<<LED_pin;
}

//--------------------------------------------------------------LED_OFF()------------------------------------------------------------------------------
void LED_OFF(void)
{
	// set LED_pin as o/p
	IODIR0 |= 1<<LED_pin;
	
	// Make high LED_pin
	IOSET0 = 1<<LED_pin;
}

//--------------------------------------------------------------Buzzer_ON()--------------------------------------------------------------------------
void Buzzer_ON(void)
{
	// set Buzzer_pin as o/p
	IODIR0 |= 1<<Buzzer_pin;
	
	// Make high Buzzer_pin
	IOSET0 = 1<<Buzzer_pin;
}

//-------------------------------------------------------------Buzzer_off()-------------------------------------------------------------------------
void Buzzer_OFF(void)
{
	// set Buzzer_pin as o/p
	IODIR0 |= 1<<Buzzer_pin;
	
	// Make high Buzzer_pin
	IOCLR0 = 1<<Buzzer_pin;
}
