/*
*********************************************************************
* Copyright	(C), 2012-2013, CS&S. Co., Ltd.
* filename:	bsp_clock.h
* filepath:	f:\draven\�пذ�\zk_dravenv100\bsp 
* --------------------------------------------------------
* History:
* <author>	@ Draven
* <time>    2017/07/20
* <version> V-0.0.1   
* <desc>	-build this moudle  
*********************************************************************
*/
#ifndef _BSP_CLOCK_H
#define _BSP_CLOCK_H

typedef enum
{
	ID_IDLE = 0,
	ID_START,
	ID_DATA,
} ID_Card_State_t;

typedef struct
{
	uint8_t ID[50]; // 64???
	uint16_t bit;	// ??bit num
	uint8_t value;
	uint8_t count;
	ID_Card_State_t state;
	// uint8_t time[256];
	// uint8_t time_index;
} ID_Card_t;
extern volatile ID_Card_t ID_Card;

typedef struct
{
	/* data */
	uint8_t ID[6];
	uint8_t has_card;
} ID_Card_Info_t;
extern volatile ID_Card_Info_t ID_Card_Info;
extern volatile ID_Card_Info_t M1_Card_Info;

extern volatile unsigned long sysTime;
extern volatile unsigned long sstime;

void bsp_clock_init(void);
void bsp_idCardIO_init(void);
void delay_ms(uint16_t ms);


#endif
/* 
*********************************************************************
* -bsp_clock.h	<File end.>
* -f:\draven\�пذ�\zk_dravenv100\bsp
*********************************************************************
*/

