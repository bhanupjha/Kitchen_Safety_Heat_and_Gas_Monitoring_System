#include "types.h"
void eint1_isr(void)__irq;
void eint1_enable(void);
void Edit_Menu(void);
void edit_rtc(void);
void edit_threshold(void);
extern volatile u32 edit_mode;
extern u32 temp_threshold;
