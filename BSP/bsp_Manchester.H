#ifndef _manchster_H_
#define _manchster_H_

#include "stm8s.h"


#define ManChesterIn GPIO_ReadInputPin(GPIOD, GPIO_PIN_3)

#define TRUE	1
#define FALSE	0

typedef union 
{
	u32 	Val;
	u8		Buf[4];
}_DEF_RFID;

typedef struct
{
	__IO u8 *PulseCnt;
	u8 (*Decode)(void);
	void  (*Result)(u8 buf[4]);
}_DEF_MANCHESTER;

extern _DEF_RFID SysRfid;
extern _DEF_MANCHESTER 	Manchester;

u8 rd_start_bit(void);
u8 rd_next_bit(void);
u8 rd_head_9bit(void);
u8 rd_data_55bit(void);
void rd_data_clr(void);
u8 rd_data_pair(void);
u8 chenk_pair(u8 c);
void rd_data_conver(u8 OutBuf[4]);
void Rfid_Init(void);
void RFID_Read(void);
#endif
