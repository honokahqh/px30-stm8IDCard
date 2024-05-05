/*
*********************************************************************
* Copyright	(C), 2012-2013, CS&S. Co., Ltd.
* filename:	appValue.c
* filepath:	f:\draven\中控板\zk_dravenv100\app 
* --------------------------------------------------------
* History:
* <author>	@ Draven
* <time>    2017/07/21
* <version> V-0.0.1   
* <desc>	-build this moudle		定义系统全局重要参数
*********************************************************************
*/

#include "modbusSlaver.h"



uint8_t coilState[USER_COIL_NUM];				/* 线圈状态 */
uint8_t coilStateLast[USER_COIL_NUM];

uint16_t holdRegValue[USER_HOLDREG_NUM];		/* 保持寄存器状态 */
uint16_t holdRegValueLast[USER_HOLDREG_NUM];		

uint8_t	MBS_SelfAddr = MY_SELF_ADDR;			/* 本机地址 */


/* 
*********************************************************************
* -appValue.c	<File end.>
* -f:\draven\中控板\zk_dravenv100\app
*********************************************************************
*/

