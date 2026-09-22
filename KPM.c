#include <lpc21xx.h>
#include "types.h"
#include "pin_define.h"
#include "LCD.h"

u8 kpmLUT[4][4]={{'1','2','3','A'},
				{'4','5','6','B'},
				{'7','8','9','C'},
			    {'*','0','#','D'}};


void InitKPM(void)
{
	IODIR1 |=15<<ROW0; // cfp p1.16 to p1.19 as output
}


u32 colScan(void)
{
	if(((IOPIN1>>COL0)&15)<15)
		return 0;
	else
		return 1;
}


u32 Rowcheck(void)
{
	u32 rno;
	for(rno=0;rno<4;rno++)
	{
		IOPIN1=((IOPIN1&(~(15<<ROW0)))|(~(1<<rno)<<ROW0));
		if(colScan()==0)
			break;
	}
	IOCLR1=15<<ROW0;
	return rno;
}


u32 Colcheck(void)
{
	u32 cno;
	for(cno=0;cno<4;cno++)
	{
		if(((IOPIN1>>(COL0+cno))&1)==0)
			break;
	}
	return cno;
}


u32 keyscan(void)
{
	u32 key,rno,cno;
	// wait for switch press
	while(colScan());
	//find the rno
	rno=Rowcheck();
	//find the cno
	cno=Colcheck();
	//find the value from LUT
	key=kpmLUT[rno][cno];
	// wait for switch release
	while(!colScan());
	return key;
}


u32 ReadNum(void)
{
	u8 key;
	u32 sum=0;
	WRITE_LCD_CMD(0xC0);
	while(1)
	{
		key=keyscan();
		if(key>='0' && key<='9')
		{
			sum=(sum*10)+(key-48);
			
			WRITE_LCD_DATA('*');
		}
		else if(key == '#')
		{
			break;
		}
	}
	return sum;
}

u32 ReadNum1(void)
{
	u8 key;
	u32 sum=0;
	WRITE_LCD_CMD(0xC0);
	while(1)
	{
		key=keyscan();
		if(key>='0' && key<='9')
		{
		
			sum=(sum*10)+(key-48);
			
			WRITE_LCD_DATA(key);
		}
		else if(key == '#')
		{
			break;
		}
	}
	return sum;
}



