#ifndef FLASH_H
#define FLASH_H
#include "types.h"

typedef struct
{
    u8 hour;
    u8 minute;
    u8 second;

    u8 date;
    u8 month;
    u32 year;

    f32 temp_threshold;
    //u32 gas_threshold;
	u32 password;
    u32 valid;

}SYSTEM_CONFIG;

extern SYSTEM_CONFIG config;

void Flash_LoadConfig(void);
void Flash_SaveConfig(void);
void Flash_ClearConfig(void);


#define CONFIG_ADDR   ((SYSTEM_CONFIG *)0x0003F000)
#define CONFIG_VALID  0x5AA55AA5

#endif

