// defines.h -> Macros

#ifndef __DEFINES_H
#define __DEFINES_H

#define SETBIT(WORD, BITPOS) (WORD |= 1<<BITPOS)
#define SSETBIT(WORD, BITPOS) (WORD = 1<<BITPOS)
#define CLRBIT(WORD, BITPOS) (WORD &= (~(1<<BITPOS)))
#define SCLRBIT(WORD, BITPOS) SSETBIT(WORD, BITPOS)
#define CPLBIT(WORD, BITPOS) (WORD ^= 1<<BITPOS)
#define READBIT(WORD, BITPOS) ((WORD>>BITPOS)&1)

#define WRITEBYTE(WORD, SBITPOS, BYTE) (WORD = (WORD &~(255<<SBITPOS))| (BYTE<<SBITPOS))
#define WRITENIBBLE(WORD, SBITPOS, NIBBLE) (WORD = (WORD &~(15<<SBITPOS))| (NIBBLE<<SBITPOS))
#define WRITEBIT(WORD, BITPOS, BIT) = ((WORD = (WORD &~(1<<SBITPOS)))| (BIT<<SBITPOS))

#define READBYTE(WORD, SBITPOS) ((WORD>>SBITPOS)&255)
#define READNIBBLE(WORD, SBITPOS) ((WORD>>SBITPOS)&15)

#define READWRITEBIT(WORD, SBIT, DBIT) ((WORD = WORD &~(1<<DBIT)) | (((WORD>>SBIT)&1)<<DBIT))
#define READWRITEBIT2(SWORD, DWORD, SBIT, DBIT) (DWORD=(DWORD&~(1<<DBIT)) | (((SWORD>>SBIT)&1)<<DBIT))


//---------------------------LCD commands----------------------------------------------------------
#define CLEAR_LCD 0x01
#define RET_CUR_HOME 0x02
#define MODE_8BIT_1LINE 0x30
#define MODE_8BIT_2LINE 0x38
#define MODE_4BIT_1LINE 0x20
#define MODE_4BIT_2LINE 0x28
#define Disp_OFF 0x08
#define DISP_ON_CUR_OFF 0x0C
#define DISP_ON_CUR_ON 0x0E
#define DISP_ON_CUR_BLINK 0x0F
#define SHIFT_CUR_RIGHT 0x06
#define GOTO_LINE1_POS0 0x80
#define GOTO_LINE2_POS0 0xC0
#define GOTO_LINE3_POS0 0x94
#define GOTO_LINE4_POS0 0xD4
#define GOTO_CGRAM 0x40


//----------------------------RTC_defines---------------------------------------------------------------
#define FOSC 12000000
#define CCLK (5*FOSC)
#define PCLK (CCLK/4)

#define PREINT_VAL ((int)(PCLK/32768)-1)
#define PREFRAC_VAL (PCLK-((PREINT_VAL+1)*32768))

#define RTC_ENABLE (1<<0)
#define RTC_RESET (1<<1)

#define RTC_CLKSRC (1<<4)

#define CPU_LPC2148

#define SUN 0
#define MON 1
#define TUE 2
#define WED 3
#define THU 4
#define FRI 5
#define SAT 6

//---------------------------ADC_defines.h-------------------------------------------------------------------
//clk defines
#define FOSC 12000000
#define CCLK (5*FOSC)
#define PCLK (CCLK/4)
#define ADCLK 3000000
#define CLK_DIV_VALUE ((PCLK/ADCLK)-1)

//ADCR
#define CLKDIV 8
#define PDN_BIT 21
#define START_CONV 24

//channel NO
#define CH0 0
#define CH1 1
#define CH2 2
#define CH3 3

//ADGDR
#define RESULT 6
#define DONE_BIT 31

//AIN -> GPIO  -> please check for lpc2148 then use
#define AIN1 0x01400000
#define AIN2 0x04400000
#define AIN3 0x10400000


//-------------------------------------------threshold_value-------------------------------------------------
//#define THRSHOLD_VAL 20

#endif
