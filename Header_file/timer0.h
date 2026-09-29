#ifndef __TIMER0_H
#define __TIMER0_H

#include "types.h"

void Init_timer0(void);
void tdelay_us(u32 us);
void tdelay_ms(u32 ms);
void tdelay_s(u32 s);

#endif

