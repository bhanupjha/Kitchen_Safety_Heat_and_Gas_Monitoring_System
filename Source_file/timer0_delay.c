#include <lpc21xx.h>
#include "types.h"

void Init_timer0(void)
{
    // Reset Timer0
    T0TCR = 1 << 1;

    // Stop timer on MR0 match
    T0MCR = 1 << 2;
}


void tdelay_us(u32 us)
{
    // Set match value
    T0MR0 = us;

    // PCLK = 15 MHz
    // 15 PCLK cycles = 1 us
    T0PR = 14;

    // Reset timer counter
    T0TC = 0;

    // Reset prescaler counter
    T0PC = 0;

    // Start timer
    T0TCR = 1 << 0;

    // Wait until TC reaches MR0
    while(T0TC < T0MR0);

    // Stop timer
    T0TCR = 0;
}


void tdelay_ms(u32 ms)
{
    // Set match value
    T0MR0 = ms;

    // PCLK = 15 MHz
    // 15000 PCLK cycles = 1 ms
    T0PR = 14999;

    // Reset timer counter
    T0TC = 0;

    // Reset prescaler counter
    T0PC = 0;

    // Start timer
    T0TCR = 1 << 0;

    // Wait until TC reaches MR0
    while(T0TC < T0MR0);

    // Stop timer
    T0TCR = 0;
}


void tdelay_s(u32 s)
{
    // Set match value
    T0MR0 = s;

    // PCLK = 15 MHz
    // 15,000,000 PCLK cycles = 1 second
    T0PR = 14999999;

    // Reset timer counter
    T0TC = 0;

    // Reset prescaler counter
    T0PC = 0;

    // Start timer
    T0TCR = 1 << 0;

    // Wait until TC reaches MR0
    while(T0TC < T0MR0);

    // Stop timer
    T0TCR = 0;
}
