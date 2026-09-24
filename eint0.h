#include "types.h"
void eint0_isr(void)__irq;
void eint0_enable(void);
void Edit_Menu(void);
void edit_rtc(void);
void edit_threshold(void);
extern volatile u32 edit_mode;
extern f32 temp_val;
