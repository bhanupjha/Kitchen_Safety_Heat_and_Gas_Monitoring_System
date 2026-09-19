#include "types.h"
void RTC_Init(void);
void SET_RTC_Time_Info(u32 hour, u32 minute, u32 second);
void GET_RTC_Time_Info(s32 *hour, s32 *minute, s32 *second);
void Display_RTC_Time(u32 hour, u32 minute, u32 second);
void SET_RTC_Date_Info(u32 date, u32 month, u32 year);
void GET_RTC_Date_Info(s32 *date, s32 *month, s32 *year);
void Display_RTC_Date(u32 date, u32 month, u32 year);
void SET_RTC_DAY(u32 dow);
void GET_RTC_DAY(s32 *dow);
void Display_RTC_Day(u32 day);
