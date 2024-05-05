/*
*********************************************************************
* Copyright	(C), 2012-2013, CS&S. Co., Ltd.
* filename:	appValue.h
* filepath:	f:\draven\ÖÐ¿Ø°å\zk_dravenv100\app
* --------------------------------------------------------
* History:
* <author>	@ Draven
* <time>    2017/07/21
* <version> V-0.0.1
* <desc>	-build this moudle
*********************************************************************
*/
#ifndef _APPVALUE_H
#define _APPVALUE_H

#include "modbusSlaver.h"

/***************************************************************/
#define COIL_SWITCH		0
#define COIL_MODE		1
#define COIL_CARD       2
#define COIL_BELL       3

extern uint8_t coilState[4];		    	/* ÏßÈ¦ */
extern uint8_t coilStateLast[4];
/***************************************************************/
#define HREG_DELAY_TIME		0
#define HREG_START_ADDR		1
#define HREG_END_ADDR		2
#define HREG_COLOR_HOLD		3

#define HREG_TABLE_COLOR1		4
#define HREG_TABLE_COLOR2		5
#define HREG_TABLE_COLOR3		6
#define HREG_TABLE_COLOR4		7
#define HREG_TABLE_COLOR5		8
#define HREG_TABLE_COLOR6		9
#define HREG_TABLE_COLOR7		10
#define HREG_TABLE_COLOR8		11
#define HREG_TABLE_COLOR9		12
#define HREG_TABLE_COLOR10		13
#define HREG_TABLE_COLOR11		14
#define HREG_TABLE_COLOR12		15
#define HREG_TABLE_COLOR13		16
#define HREG_TABLE_COLOR14		17
#define HREG_TABLE_COLOR15		18
#define HREG_TABLE_COLOR16		19

#define HREG_MY_ADDR			20
#define HREG_MY_VERSION			21

#define HREG_RFID_ID1			22
#define HREG_RFID_ID2			23
#define HREG_RFID_ID3			24
#define HREG_RFID_ID4			25

#define HREG_BELL_NUM			26
#define HREG_BELL_DELAY			27

/***************************************************************/
#define MY_SELF_ADDR					100

extern uint16_t holdRegValue[28];		/* ±£³Ö¼Ä´æÆ÷ */
extern uint16_t holdRegValueLast[28];
/***************************************************************/
extern uint8_t	MBS_SelfAddr;

#endif
/*
*********************************************************************
* -appValue.h	<File end.>
* -f:\draven\ÖÐ¿Ø°å\zk_dravenv100\app
*********************************************************************
*/

