#ifndef __EVENT_LOG_H
#define __EVENT_LOG_H

#include "types.h"

#define EVENT_PERIOD_SEC   10    // show the last event every 10 seconds
#define EVENT_SHOW_SEC     3     // keep it on the LCD for 3 seconds

void EventLog_Init(void);          // also calls Init_timer0()
void EventLog_Update(f32 tempc, f32 tempSetPoint, u32 gasLogic);
u32  EventLog_DisplayTask(void);   // returns 1 if the event screen was shown in this pass, otherwise 0

#endif
