#include "types.h"
void eint0_isr(void)__irq;
void eint0_enable(void);
void Edit_Menu(void);
void edit_rtc_Menu(void);
void edit_threshold(void);
extern volatile u32 edit_mode;
extern f32 temp_val;
void edit_time_Menu(void);
void edit_date_Menu(void);
void edit_hr(void);
void edit_min(void);
void edit_sec(void);
void edit_Hr_Min_Sec(void);
void edit_DOM(void);
void edit_Month(void);
void edit_Year(void);
void edit_Dom_Month_Year(void);
void invalid_input(void);
