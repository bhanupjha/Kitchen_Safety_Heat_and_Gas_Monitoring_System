#include "types.h"

f32 LM35tc(void);
f32 LM35tf(void);
f32 LM35tF(void);
f32 LM35tc(void);
void display_temp(f32);
void display_gas(u32 gas_logic);

void LED_ON(void);
void LED_OFF(void);
void Buzzer_ON(void);
void Buzzer_OFF(void);
void LED_Buzzer_check(f32 tempc, u32 gas_logic);

